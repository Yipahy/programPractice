#ifndef __INHERIT_H__
#define __INHERIT_H__a

#include <iostream>
class Grandpa
{
	public:
		int a;
};

class Father1:virtual public Grandpa
{
	public:
		int b;
};

class Father2:virtual public Grandpa
{
	public:
		int c;
};

class Son:public Father1,public Father2
{
	public:
		int d;
};

class Animal
{
	public:
		virtual void speak();
		virtual ~Animal();
};

class Dog:public Animal
{
	public:
		void speak() override;
};

class Bird
{
	public:
		virtual void func()=0;
};

class Eagle:public Bird
{
	public:
		void func() override;
};
#endif
