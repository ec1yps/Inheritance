#pragma once
#include "stdafx.h"
#include "Constants.h"
#include "Student.h"

class Graduate : public Student
{
	std::string theme;
public:
	const std::string& get_theme()const;
	void set_theme(const std::string& theme);

	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS);
	Graduate(const Student& student, GRADUATE_TAKE_PARAMETERS);
	~Graduate();

	std::ostream& print(std::ostream& os)const override;
};