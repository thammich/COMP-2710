#include <iostream>
#include "starter.h"

Starter_Object::Starter_Object()
{
	//initialize all data members
	val1_ = 0;
	val2_ = 0;
}

Starter_Object::~Starter_Object()
{
	//release all pointers from the heap in destructor
}

//define the rest of the methods from starter.h
void Starter_Object::val1(int value)
{
	val1_ = value;
}

int Starter_Object::val1() {return val1_; }

void Starter_Object::val2(int value)
{
	val2_ = value;
}

int Starter_Object::val2() { return val2_; }

