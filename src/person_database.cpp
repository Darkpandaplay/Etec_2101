#include <fstream>     // access to FILE input/output
#include <iostream>
#include <string>
#include <person_database.h>

void example::PersonDatabase::add_person(Person new_person)
{
	person_array_size += 1;
	unsigned int n = person_array_size;
	Person* person_array = new Person[n]; // Allocate the array (n is an integer defined previously).
	// Re-allocate the array to be one bigger
	Person* temp_array = new Person[n + 1]; // ... 1. make a new array capable of holding the larger array.
	for (int i = 0; i < n; i++) // ... 2. copy the data from the old (size-n) array to
		temp_array[i] = person_array[i]; // the new (size n+1) array. Better than memcpy in C++?
	n++; // ... 3. make n (the array size) one bigger
	delete[] person_array; // ... 4. now free the old array since it's no longer
	person_array = temp_array;

}

example::PersonDatabase::PersonDatabase(std::string fname)
{
	person_array_size = 0;
	person_array = nullptr; // Indicates that the array is empty
	while (true)
	{
		std::ifstream fp(fname);
		if (fp.eof())
			break;
		Person p();
		add_person(p);
	}
}