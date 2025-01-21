#include <person.h>
#include <iostream>
#include <string>

void func()
{
	Person a(45, "kelly", "Smith");
}

int main(int argc, char** argv)
{
	//Making two object instances of the Person class
	Person p(42,"Mike","Jackson");
	Person q;
	p.set_hourly_rate(10.5);
	p.set_hours_worked(15.7);
	std::cout << "The pay for p is " << p.calculate_pay() << "\n";
	std::cout << "The pay for q is " << q.calculate_pay() << "\n";

	func();
	Person* pptr;
	pptr = NULL;
	int x = NULL;
	pptr = nullptr;

	//pptr->set_hourly_rate(11.3);
	//(*pptr).set_hourly_rate(11.3); //Same line of code
	std::cout << "Doing some more with the Person pointed to by pptr\n";
	//Fee up Person object
	delete pptr;

	pptr = nullptr;
	//Make a new person using pptr
	pptr = new Person(47, "Mac", "Lil");
	pptr->set_hourly_rate(14.5);
	delete pptr;

	return 0;
}