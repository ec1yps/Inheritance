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
			cout << "������� ������: " << get_area() << endl;
			cout << "�������� ������: " << get_perimeter() << endl;
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
			cout << "����� �������: " << get_side() << endl;
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
			//1) �������� ���� �������:
			//HWND hwnd = GetConsoleWindow(); //������� GetConsoleWindow() �������� ���� �������
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");

			//2) ��� ���� ����� ��������, ����� �������� ���������� (Device Context), ������� ���� � ������� ����:
				//�������� ���������� ����� �������� � ������� ������� GetDC()
			HDC hdc = GetDC(hwnd); //�������� �������� ���� �������

			//3) ������ ����� ��, ��� ����� ��������:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);	//hPen - ������ ������ ������
			HBRUSH hBrush = CreateSolidBrush(color);	//hBrush - ������ ������� ������

			//4) ��������, ��� � �� ��� �� ����� ��������:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) ������ ������:
			::Rectangle(hdc, 500, 100, 900, 300);

			//6) ����������� ������:
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������ ��������������: " << get_width() << endl;
			cout << "������ ��������������: " << get_height() << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);

	Geometry::Square square(5, Geometry::Color::CONSOLE_RED);
	/*cout << "����� �������: " << square.get_side() << endl;
	cout << "������� ��������: " << square.get_area() << endl;
	cout << "�������� ��������: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(100, 50, Geometry::Color::CONSOLE_BLUE);
	rect.info();
}