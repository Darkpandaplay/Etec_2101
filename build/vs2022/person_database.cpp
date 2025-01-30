#include <fstream>     // access to FILE input/output
#include <iostream>
#include <string>
#include <person_database.h>

example::PersonDatabase::PersonDatabase(std::string fname)
{
	std::fstream fp(fname);
	person_array = nullptr; // Indicates that the array is empty
	while (true)
	{
		if (fp.eof())
			break;
		example::Person p();
		add_person(p);
	}
}
void example::PersonDatabase::add_person(Person new_person)
{

}