#ifndef __TEMPLATE_HPP__
#define __TEMPLATE_HPP__

#include <iostream>
#include <string>
template<class NameType,class AgeType=int>
class TemplateTest
{
	public:
		TemplateTest(NameType name,AgeType age)
		{
			this->name=name;
			this->age=age;
		}
		void print()
		{
			std::cout<<name<<" "<<age<<std::endl;
		}
	private:
		NameType name;
		AgeType age;
};

#endif
