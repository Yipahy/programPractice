#include "inherit.h"

void Animal::speak()
{
	std::cout<<"Animal"<<std::endl;
}
Animal::~Animal(){}

void Dog::speak()
{
	std::cout<<"Dog"<<std::endl;
}

void Eagle::func()
{
	std::cout<<"Eagle can fly"<<std::endl;
}
