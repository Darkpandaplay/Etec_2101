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
		/// <param name="fname"></param>
		PersonDatabase(std::string fname);
	};
}