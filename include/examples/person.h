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
    Person();
    //This CONSTRUCTOR -- method that has no return type must have same name as class.This is a OVERLOAD (Alternate Constuctor)
    Person(int start_id, std::string start_fname, std::string start_lname);
    // This is a METHOD -- a function that all instances of the class can
    // use.  This is a DECLARATION.  
    float calculate_pay();
    //This CONSTRUCTOR -- method that has no return type must have same name as class.This is a DEFAULT CONSTRUCTOR (NO PARAMETERS)
    // This is a METHOD -- a function that all instances of the class can
    // use.  This is a DECLARATION.

    int get_id();
    void set_hourly_rate(float new_rate);
    void set_hours_worked(unsigned int new_hours);
};

#endif