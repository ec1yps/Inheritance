#pragma once
#include "stdafx.h"
#include "Constants.h"

class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name()const;
	const std::string& get_first_name()const;
	int get_age()const;
	void set_last_name(const std::string& last_name);
	void set_first_name(const std::string& first_name);
	void set_age(int age);

	Human(HUMAN_TAKE_PARAMETERS);
	virtual ~Human();

	virtual std::ostream& print(std::ostream& os)const;
};
