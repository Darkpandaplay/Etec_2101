#include <fstream>     // access to FILE input/output
#include <iostream>
#include <string>
#include <person_database.h>

example::personDatabase::PersonDatabase(std::string fname)
{
	person_array = nullptr; // Indicates that the array is empty
	while (true)
	{
		if (fp.eof())
			break;
		example::Person p()
		add_person(p);
	}
}