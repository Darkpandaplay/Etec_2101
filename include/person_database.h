#ifndef _PERSON_DATABASE_H_    // "compiler guard" -- makes sure this
#define _PERSON_DATABASE_H_
#include <fstream>     // access to FILE input/output
#include <iostream>
#include <string>
#include <person.h>

namespace example
{
	/// <summary>
	/// 
	/// </summary>
	class PersonDatabase
	{
		/// <summary>
		/// 
		/// </summary>
		Person* person_array;
		/// <summary>
		/// 
		/// </summary>
		/// <param name="fname">First name of a person</param>
		PersonDatabase(std::string fname);
		/// <summary>
		/// Will give the current size of the person array
		/// </summary>
		unsigned int person_array_size;    // like "n" on slide 16
		/// <summary>
		/// Should add the new Person object to the array
		/// </summary>
		/// <param name="new_person">new Person object</param>
		void add_person(Person new_person);
		bool remove_person(unsigned int id_to_remove)
	};
};
#endif