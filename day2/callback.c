#include "callback.h"

void myprint(void* data,void (*func)(void*))
{
	func(data);
}

void printInt(void* data)
{
	int tmp=*(int*)data;
	printf("%d\n",tmp);
}

void printDouble(void* data)
{
	double tmp=*(double*)data;
	printf("%lf\n",tmp);
}

void printChar(void* data)
{
	char tmp=*(char*)data;
	printf("%c\n",tmp);
}

void printString(void* data)
{
	char* tmp=(char*)data;
	printf("%s\n",tmp);
}
