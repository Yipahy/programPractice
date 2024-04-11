#include "plus.h"
#include "sub.h"
#include "multi.h"
#include "div.h"

int main()
{
	int a=23,b=34;
	std::cout<<plus(a,b)<<std::endl;
	std::cout<<sub(a,b)<<std::endl;
	std::cout<<multi(a,b)<<std::endl;
	std::cout<<div1(a,b)<<std::endl;
	return 0;
}
