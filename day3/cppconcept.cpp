#include "cppconcept.h"

void func(int a,int b,int c)
{
		printf("%d\n",a+b+c);
}
int Function::operator()(int v1,int v2)
{
        return v1+v2;
}
void printStudent(Student& s)
{
		std::cout<<s.name<<" "<<s.age<<" "<<s.department<<" "<<s.stdno<<std::endl;
}
Student::Student()
{
		name=new char[64];
		strcpy(name,"anonymous");
		department=new char[64];
		strcpy(department,"anonymous");
		age=stdno=grade=printcount=0;
}
Student::Student(const Student& s)
{
		name=new char[64];
		strcpy(name,s.name);
		department=new char[64];
		strcpy(department,s.department);
		age=s.age;
		stdno=s.stdno;
		grade=s.grade;
		printcount=0;
}
Student::Student(char* n,int s,char* d,int a,int g)
{
		name=new char[64];
		strcpy(name,n);
		department=new char[64];
		strcpy(department,d);
		age=a;
		stdno=s;
		grade=g;
		printcount=0;
}
Student& Student::operator=(const Student& s)
{
		if(this->name)
		{
			delete[] this->name;
			this->name=nullptr;
		}
		this->name=new char[strlen(s.name)+1];
		strcpy(this->name,s.name);

		if(this->department)
		{
			delete[] this->department;
			this->department=nullptr;
		}
		this->department=new char[strlen(s.department)+1];
		strcpy(this->department,s.department);

		age=s.age,stdno=s.stdno,grade=s.grade;
		return *this;
}
std::ostream& operator<<(std::ostream& out,const Student &s)
{
		std::cout<<s.name<<" "<<s.grade;
		return out;
}
Student& Student::operator+(const Student& s)
{
		grade+=s.grade;
		return *this;
}
Student& Student::operator++()
{
		++this->grade;
		return *this;
}
Student Student::operator++(int)
{
		Student tmp(*this);
		++this->grade;
		return tmp;
}
void Student::printData()const
{
		std::cout<<name<<" "<<age<<" "<<department<<" "<<stdno<<" "<<grade<<" "<<printcount<<std::endl;
		++printcount;
}

Student::~Student()
{
		delete[] name;
		delete[] department;
}

