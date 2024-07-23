#include <Windows.h>
#include <iostream>
using namespace std;

namespace Geometry
{
	enum Color
	{
		CONSOLE_RED = 0xCC,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_BLUE = 0x99,
		CONSOLE_DEFAULT = 0x07
	};

	class Shape
	{
	protected:
		Color color;
	public:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}

		void set_side(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}

		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << get_side() << endl;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, Color color) :Shape(color)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}

		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}

		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			//1) Поулчаем окно консоли:
			//HWND hwnd = GetConsoleWindow(); //Функция GetConsoleWindow() получает окно консоли
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");

			//2) Для того чтобы рисовать, нужен контекст устройства (Device Context), который есть у каждого окна:
				//Контекст устройства можно получить с помощью функции GetDC()
			HDC hdc = GetDC(hwnd); //получаем контекст окна консоли

			//3) Теперь нужно то, чем будем рисовать:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);	//hPen - рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);	//hBrush - рисует заливку фигуры

			//4) Выбираем, чем и на чем мы будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) Рисуем фигуру:
			::Rectangle(hdc, 500, 100, 900, 300);

			//6) Освобождаем память:
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина прямоугольника: " << get_width() << endl;
			cout << "Высота прямоугольника: " << get_height() << endl;
			Shape::info();
		}
	};

	class Triangle :public Shape
	{
		double aSide;
		double bSide;
		double cSide;
	public:
		Triangle(double aSide, double bSide, double cSide, Color color) :Shape(color)
		{
			set_aSide(aSide);
			set_bSide(bSide);
			set_cSide(cSide);
		}
		~Triangle() {}

		void set_aSide(double aSide)
		{
			this->aSide = aSide;
		}
		void set_bSide(double bSide)
		{
			this->bSide = bSide;
		}
		void set_cSide(double cSide)
		{
			this->cSide = cSide;
		}
		double get_aSide()const
		{
			return aSide;
		}
		double get_bSide()const
		{
			return bSide;
		}
		double get_cSide()const
		{
			return cSide;
		}

		double get_area()const override
		{
			double p = get_perimeter() / 2;
			
			return sqrt(p * (p - aSide) * (p - bSide) * (p - cSide));
		}
		double get_perimeter()const override
		{
			return aSide + bSide + cSide;
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");

			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			const POINT poligon[6]{ 500, 600, 600, 400, 900, 600 };

			::Polygon(hdc, poligon, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Первая сторона треугольника: " << aSide << endl;
			cout << "Вторая сторона треугольника: " << bSide << endl;
			cout << "Третья сторона треугольника: " << cSide << endl;
			Shape::info();
		}
	};

	class Circle :public Shape
	{
		double radius;
	public:
		Circle(double radius, Color color) :Shape(color)
		{
			set_radius(radius);
		}
		~Circle() {}

		void set_radius(double radius)
		{
			this->radius = radius;
		}
		double get_radius()const
		{
			return radius;
		}

		double get_area()const override
		{
			return 3.14 * radius * radius;
		}
		double get_perimeter()const override
		{
			return 2 * 3.14 * radius;
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");

			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, 1000, 100, 1200, 300);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << radius << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);

	Geometry::Square square(5, Geometry::Color::CONSOLE_RED);
	/*cout << "Длина стороны: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(100, 50, Geometry::Color::CONSOLE_BLUE);
	rect.info();

	Geometry::Triangle tr(5, 4, 3, Geometry::Color::CONSOLE_GREEN);
	tr.info();

	Geometry::Circle circ(50, Geometry::Color::CONSOLE_RED);
	circ.info();
}