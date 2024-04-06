#ifndef _CPPCONCEPT_H_
#define _CPPCONCEPT_H_
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
void func(int a,int b=0,int c=0);
class Function
{
	public:
		int operator()(int v1,int v2);
};
class Student
{
	public:
		Student();
	    Student(const Student& s);
		friend void printStudent(Student& s);
		void printData()const;
		Student(char* n,int s,char* d,int a,int g);
		Student& operator=(const Student& s);
        Student& operator+(const Student& s);
		Student& operator++();
        Student operator++(int);
		friend std::ostream& operator<<(std::ostream& out,const Student& s);
		~Student();
	private:
		char* name;
		int age;
		char* department;
		int stdno;
		int grade;
		mutable int printcount;
};

#endif
