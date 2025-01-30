#include <fstream>     // access to FILE input/output
#include <iostream>
#include <string>
#include <person_database.h>

example::PersonDatabase::PersonDatabase(std::string fname)
{
	std::fstream fp(fname);
	person_array = nullptr; // Indicates that the array is empty
	person_array_size = 0;
	while (true)
	{
		if (fp.eof())
			break;
		example::Person p;
		add_person(p);
	}
}
void example::PersonDatabase::add_person(Person new_person)
{
	//Checks for Duplicate Id's
	for (int i = 0; i < person_array_size; i++)
	{
		if (person_array[i].get_id() == new_person.get_id()) {
			std::string err_msg = "Duplicate id" + std::to_string(new_person.get_id());
			throw std::runtime_error(err_msg);
		}
	}

}

bool example::PersonDatabase::remove_person(unsigned int id_to_remove)
{
	
	for (int i = 0; i < person_array_size; i++) {
		bool found = false;
		if (person_array[i].get_id() == id_to_remove) {
			found = true;

		}
	}
	return false;
}