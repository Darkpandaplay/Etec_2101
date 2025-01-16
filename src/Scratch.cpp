//Person.cpp BODIES
#include <person.h>

//General Structure:	ReturnType ClassName::MethodName(PARAMETERS){.....}

float Person::calculate_pay()
{
	//We have acess to all attributes since we're part of the class
	return hourly_rate * hours_worked;
}

int Person::get_id()
{
	return id;
}

void Person::set_hourly_rate(float new_rate)
{
	hourly_rate = new_rate;
}
void Person::set_hours_worked(unsigned int new_hours)
{
	hours_worked = new_hours;
}
Person::Person()
{
	id = -1;
	first_name = "?";
	last_name = "?";
	hours_worked = 0;
	hourly_rate = 0.0f;
}

Person::Person(int start_id,std::string start_fname, std::string start_lname)
{
	id = start_id;
	first_name = start_fname;
	last_name = start_lname;
	hours_worked = 0;
	hourly_rate = 0.0f;
}