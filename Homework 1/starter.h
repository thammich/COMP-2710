#ifndef STARTER_OBJECT_H
#define STARTER_OBJECT_H

#include <iostream>

class Starter_Object
{
	private:
		int val1_;
		int val2_;

	public:
		Starter_Object();
		~Starter_Object();

		int val1();
		void val1(int value);
		int val2();
		void val2(int value);
};

#endif