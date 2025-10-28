#include <iostream>
#include "starter.h"

using namespace std;

int main()
{
	cout << "i hope this works" << endl;

	Starter_Object obj1;
	Starter_Object obj2;

	obj1.val1(1);
	obj1.val2(2);
	obj2.val1(3);
	obj2.val2(4);

	cout << "object 1 val1 = " << obj1.val1() << endl;
	cout << "object 1 val2 = " << obj1.val2() << endl;
	cout << "object 2 val1 = " << obj2.val1() << endl;
	cout << "object 2 val2 = " << obj2.val2() << endl;

	return 0;
	//create a few starter objects
	//add some values to test out your values methods
	//print out all the values for each object to validate your code
}