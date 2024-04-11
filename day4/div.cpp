#include "div.h"

int div1(int a,int b)
{
	if(b==0)
	{ 
		std::cout<<"除数不能为0"<<std::endl;
		return 0;
	}
	else return a/b;
}
