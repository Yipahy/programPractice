#ifndef _CALLBACKTEST_HPP
#define _CALLBACKTEST_HPP
#include "callback.h"

void test()
{
	int a=10086;
	myprint(&a,printInt);
}
#endif
