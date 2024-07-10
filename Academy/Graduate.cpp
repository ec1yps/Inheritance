#include "Graduate.h"

const std::string& Graduate::get_theme()const
{
	return theme;
}
void Graduate::set_theme(const std::string& theme)
{
	this->theme = theme;
}

Graduate::Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS) :Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
{
	set_theme(theme);
	cout << "GConstructor:\t" << this << endl;
}
Graduate::Graduate(const Student& student, GRADUATE_TAKE_PARAMETERS) :Student(student)
{
	set_theme(theme);
	cout << "GConstructor:\t" << this << endl;
}
Graduate::~Graduate()
{
	cout << "GDestructor:\t" << this << endl;
}

std::ostream& Graduate::print(std::ostream& os)const
{
	return Student::print(os) << " " << theme;
}