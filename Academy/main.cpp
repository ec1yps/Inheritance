#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n--------------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	static const int TYPE_WIDTH = 12;
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 5;
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//		Constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor\t" << this << endl;
	}


	//		Methods:
	virtual std::ostream& print(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age;
	}
	virtual std::ofstream& print(std::ofstream & ofs) const
	{
		ofs.width(TYPE_WIDTH);
		ofs << std::left;
		ofs << std::string(strchr(typeid(*this).name(), ' ') + 1) + ":";

		ofs.width(LAST_NAME_WIDTH);
		ofs << last_name;
		ofs.width(FIRST_NAME_WIDTH);
		ofs << first_name;
		ofs.width(AGE_WIDTH);
		ofs << age;

		return ofs;
	}
};
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	return obj.print(ofs);
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student : public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 8;
	static const int ATTANDANCE_WIDTH = 8;
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attandance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//		Constructors:
	Student (HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	Student(const Human& human, STUDENT_TAKE_PARAMETERS) :Human(human)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//		Methods:
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);

		ofs.width(SPECIALITY_WIDTH);
		ofs << speciality;
		ofs.width(GROUP_WIDTH);
		ofs << group;
		ofs.width(RATING_WIDTH);
		ofs << rating;
		ofs.width(ATTANDANCE_WIDTH);
		ofs << attendance;

		return ofs;
	}
};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher : public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int EXPERIENCE_WIDTH = 5;
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}

	//		Constructors:
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) : Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//		Methods:
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os) << " " << speciality << " " << experience;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(SPECIALITY_WIDTH);
		ofs<< speciality;
		ofs.width(EXPERIENCE_WIDTH);
		ofs << experience;

		return ofs;
	}
};

#define GRADUATE_TAKE_PARAMETERS const std::string& theme
#define GRADUATE_GIVE_PARAMETERS theme

class Graduate : public Student
{
	static const int THEME_WIDTH = 25;
	std::string theme;
public:
	const std::string& get_theme()const
	{
		return theme;
	}
	void set_theme(const std::string& theme)
	{
		this->theme = theme;
	}

	//		Constructors:
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS) :Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_theme(theme);
		cout << "GConstructor:\t" << this << endl;
	}
	Graduate(const Student& student, GRADUATE_TAKE_PARAMETERS) :Student(student)
	{
		set_theme(theme);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//		Methods:
	std::ostream& print(std::ostream& os)const override
	{
		return Student::print(os) << " " << theme;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Student::print(ofs);
		ofs.width(THEME_WIDTH);
		ofs << theme;

		return ofs;
	}
};


void Print(Human* group[], const int n)
{
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
	{
		//group[i]->print();
		cout << *group[i] << endl;
		cout << delimiter << endl;
	}
}
void Clear(Human* group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
}

void Save(Human* group[], const int n, const std::string filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();
}
Human** Load(const std::string& filename, int& n)
{
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		//1) Вычисление размера файла (количество записей в файле):
		n = 0;
		while (!fin.eof())
		{
			std::string buffer;
			std::getline(fin, buffer);
			if (
				buffer.find("Human:") == std::string::npos &&
				buffer.find("Student:") == std::string::npos &&
				buffer.find("Teacher:") == std::string::npos &&
				buffer.find("Graduate:") == std::string::npos
				)continue;
			n++;
		}
		cout << "Количество записей в файле: " << n << endl;

		//2) Выделяем память для группы:
		group = new Human * [n] {};

		//3) Возвращаемся в начало файла для того чтобы прочитать содержимое в этом файле:
		cout << "Позиция курсора на чтение: " << fin.tellg() << endl;
		fin.clear();
		fin.seekg(0);
		cout << "Позиция курсора на чтение: " << fin.tellg() << endl;

		//4) Читаем файл:
		for (int i = 0; !fin.eof(); i++)
		{
			std::string type;
			fin >> type;
			std::string buffer;
			std::getline(fin, buffer);

		}

		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	return group;
}

//#define INHERITANCE_1
//#define INHERITANCE_2
#define SAVE_CHECK
//#define LOAD_CHECK

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

#ifdef SAVE_CHECK
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 95, 90),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Mercer", "Alex", 45, "Biology", "AA_123", 90, 90, "Biomutation"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 95, 98),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};

	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
	Clear(group, sizeof(group) / sizeof(group[0]));
#endif // SAVE_CHECK

#ifdef LOAD_CHECK
	int n = 0;
	Human** group = Load("group.txt", n);
#endif // LOAD_CHECK

}