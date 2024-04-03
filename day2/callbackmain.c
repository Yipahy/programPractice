#include "callback.h"

int main()
{
	int a=10;
	double b=3.14;
	char c='e';
	char* str="hello world";
	myprint(&a,printInt);
	myprint(&b,printDouble);
	myprint(&c,printChar);
	myprint(str,printString);
	printf("%s\n",__FILE__);
	printf("%s\n",__DATE__);
	printf("%s\n",__TIME__);
	printf("%d\n",__LINE__);
	return 0;
}

