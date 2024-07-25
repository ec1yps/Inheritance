﻿#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>
using namespace std;

namespace Geometry
{
	enum Color
	{
		RED = 0x000000FF,
		GREEN = 0x0000FF00,
		BLUE = 0x00FF0000,
		YELLOW = 0x0000FFFF,
		CONSOLE_RED = 0xCC,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_BLUE = 0x99,
		CONSOLE_DEFAULT = 0x07
	};

#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int liner_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, liner_width, color

	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
	public:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Shape(SHAPE_TAKE_PARAMETERS) :color(color) 
		{
			if (start_x > 1000) start_x = 1000;
			set_start_x(start_x);
			if (start_y > 700) start_y = 700;
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		//	Encapsulation:
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			this->line_width = line_width;
		}

		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square :public Shape
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
	};*/

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
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
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);

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

	class Square : public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) : Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
	};

	class Triangle :public Shape
	{
		double aSide;
		double bSide;
		double cSide;
	public:
		Triangle(double aSide, double bSide, double cSide, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
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

		double get_max_side()const
		{
			if (aSide > bSide && aSide > cSide) return aSide;
			if (bSide > aSide && bSide > cSide) return bSide;
			if (cSide > aSide && cSide > bSide) return cSide;
		}
		double get_mid_side()const
		{
			if (aSide < bSide && aSide > cSide) return aSide;
			if (bSide < aSide && bSide > cSide) return bSide;
			if (cSide < aSide && cSide > bSide) return cSide;
		}
		double get_short_side()const
		{
			if (aSide < bSide && aSide < cSide) return aSide;
			if (bSide < aSide && bSide < cSide) return bSide;
			if (cSide < aSide && cSide < bSide) return cSide;
		}
		double get_height()const
		{
			if (get_max_side()) return 2 * get_area() / aSide;
			if (get_max_side()) return 2 * get_area() / bSide;
			if (get_max_side()) return 2 * get_area() / cSide;
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

			const POINT poligon[6]{ start_x, start_y, start_x + sqrt(pow(get_short_side(), 2) + pow(get_height(), 2)), start_y + get_height(), start_x + get_max_side(), start_y };

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
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			if (radius > 600) radius = 600;
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
		double get_diameter()const
		{
			return 2 * radius;
		}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return M_PI * get_diameter();
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");

			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << get_radius() << endl;
			cout << "Диаметр круга: " << get_diameter() << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);

	Geometry::Square square(120, 100, 100, 5, Geometry::Color::RED);
	square.info();
	/*cout << "Длина стороны: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/

	Geometry::Rectangle rect(100, 50, 300, 100, 10, Geometry::Color::BLUE);
	rect.info();
	
	Geometry::Circle circ(600, 700, 100, 5, Geometry::Color::YELLOW);
	circ.info();

	Geometry::Triangle tr(500, 400, 300, 100, 500, 5, Geometry::Color::GREEN);
	tr.info();
}