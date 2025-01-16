#pragma once
// person.h
// #pragma once       // does the same compiler guard as below
#ifndef _PERSON_H_    // "compiler guard" -- makes sure this
#define _PERSON_H_    //   header file (and the stuff within it...our
                      //   class declaration) is only seen once by the
                      //   compiler
#include <string>

class Person
{
    // These are ATTRIBUTES -- variables that each instance of the class
    // gets a copy of.
    // By default all members of a class are PRIVATE (we can only
    //   access them in a method).  Normally we make our attributes private
    //   but methods public.
private:
    int id;
    std::string first_name;
    std::string last_name;
    float hourly_rate;
    unsigned int hours_worked;

public:
    // This is a METHOD -- a function that all instances of the class can
    // use.  This is a DECLARATION.  
    float calculate_pay();
};

#endif