#include "stdafx.h"
#include "Constants.h"
#include "Human.h"
#include "Student.h"
#include "Teacher.h"
#include "Graduate.h"
#include "Functions.h"

//#define INHERITANCE_1
//#define INHERITANCE_2

void main()
{
	setlocale(LC_ALL, "");
	cout << "HelloAcademy" << endl;

#ifdef INHERITANCE_1
	Human human("Richter", "Jeffrey", 40);
	human.print();
	cout << delimiter << endl;

	Student student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 95, 90);
	student.print();
	cout << delimiter << endl;

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.print();
	cout << delimiter << endl;

	Graduate graduate("Mercer", "Alex", 45, "Biology", "AA_123", 90, 90, "Biomutation");
	graduate.print();
	cout << delimiter << endl;
#endif // INHERITANCE_1

#ifdef INHERITANCE_2
	Human human("Vercetty", "Tommy", 30);
	human.print();
	cout << delimiter << endl;

	Student student(human, "Theft", "Vice", 95, 98);
	student.print();
	cout << delimiter << endl;

	Graduate graduate(student, "How to make money");
	graduate.print();
#endif // INHERITANCE_2

	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 95, 90),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Mercer", "Alex", 45, "Biology", "AA_123", 90, 90, "Biomutation"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 95, 98),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};

	std::ofstream fout;
	fout.open("File.txt", std::ios_base::app);
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();

	Print(group, sizeof(group) / sizeof(group[0]));
	Clear(group, sizeof(group) / sizeof(group[0]));

	cout << delimiter << endl;
	
	std::ifstream fin("File.txt");
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			const int SIZE = 1024;
			char buffer[SIZE]{};
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
}