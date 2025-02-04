#include <person_database.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

// Constructor
example::PersonDatabase::PersonDatabase(std::string file)
{
	std::ifstream fp(file);

	if (!fp.is_open())
	{
		throw std::runtime_error("Failed to open the file");
	}

	person_array = nullptr;
	person_array_size = 0;

	// data from the file
	int id;
	std::string fname, lname;
	float rate;
	unsigned int hours;

	std::cout << std::fixed << std::setprecision(2);

	while (true)
	{
		fp >> id >> fname >> lname >> rate >> hours;
		if (fp.eof())
			break;
		else if (fp.fail())
			std::cout << "Error reading in data\n";

		example::Person new_person(id, fname, lname);
		new_person.set_hourly_rate(rate);
		new_person.set_hours_worked(hours);

		add_person(new_person);
	}

	fp.close();

	// If the file was empty, initialize the array properly
	if (person_array_size == 0) {
		person_array = new example::Person[0];
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

	if (person_array == nullptr)
	{
		person_array = new example::Person[1];
		person_array[0] = new_person;
		person_array_size = 1;
	}
	else
	{
		for (int i = 0; i < person_array_size; i++)
		{
			if (person_array[i].get_id() == new_person.get_id())
			{
				std::cout << "\nDuplicate ID Entered!\n";
				return;
			}
		}

		example::Person* temp_array = new example::Person[person_array_size + 1];

		for (int i = 0; i < person_array_size; i++)
		{
			temp_array[i] = person_array[i];
		}

		temp_array[person_array_size] = new_person;

		delete[] person_array;

		person_array = temp_array;

		person_array_size++;
	}
}

bool example::PersonDatabase::remove_person(unsigned int id_to_remove)
{
	int index = -1;
	bool found = false;

	for (unsigned int i = 0; i < person_array_size; i++) {
		if (person_array[i].get_id() == id_to_remove) {
			found = true;

		}
	}

	if (found)
	{
		example::Person* temp_array = new example::Person[person_array_size - 1];

		for (int i = 0, j = 0; i < person_array_size; i++)
		{
			if (i != index)	// If i does not equal the person to remove... This will skip the person being removed.
			{
				temp_array[j] = person_array[i];	// copy data to temp array and increment j
				j++;
			}
		}

		delete[] person_array;

		person_array = temp_array;

		person_array_size--;

		std::cout << "\nPerson with ID: " << std::to_string(id_to_remove) << " removed\n";
		return true;
	}
	else
	{
		std::cout << "\nNo Person found with ID: " << std::to_string(id_to_remove) << "\n";
		return false;
	}
}


std::string example::PersonDatabase::to_string(std::string file)
{
	std::stringstream ss;
	std::cout << std::fixed << std::setprecision(2);

	ss << "\nPerson\t\t" << "ID\t" << "Hours\t" << "Rate\t" << "Monthly Salary\n"
		<< "======\t\t" << "===\t" << "=====\t" << "====\t" << "==============\n";
	std::string header = ss.str();
	ss.str("");

	ss << "===================================================\n";
	std::string footer = ss.str();
	ss.str("");

	std::cout << std::fixed << std::setprecision(2);

	for (int i = 0; i < person_array_size; i++)
	{
		ss << person_array[i].get_first_name() << " " << person_array[i].get_last_name() << "\t"
			<< person_array[i].get_id() << "\t"
			<< person_array[i].get_hours_worked() << "\t$"
			<< person_array[i].get_hourly_rate() << "\t$"
			<< person_array[i].calculate_pay() << "\n";
	}
}

// Destructor
example::PersonDatabase::~PersonDatabase()
{
	std::ofstream fp("..\\..\\media\\person_database.txt");

	if (!fp.is_open())
	{
		throw std::runtime_error("Failed to open the file");
	}

	std::cout << std::fixed << std::setprecision(2);

	// Writing into fp, maintaining format
	for (int i = 0; i < person_array_size; i++)
	{
		fp << person_array[i].get_id() << " "
			<< person_array[i].get_first_name() << " "
			<< person_array[i].get_last_name() << " "
			<< person_array[i].get_hourly_rate() << " "
			<< person_array[i].get_hours_worked() << "\n";
	}

	fp.close();

	delete[] person_array;
}