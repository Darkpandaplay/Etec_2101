#include <person.h>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	//Making two object instances of the Person class
	Person p;
	Person q;


	std::cout << "The pay for p is " << p.calculate_pay() << "\n";
	std::cout << "The pay for q is " << q.calculate_pay() << "\n";
	return 0;
}