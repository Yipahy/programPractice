#include <stdio.h>
int c=255;
extern test();
int main()
{
	int a=0x11223344;
	char* p=&a;
	int b=22;
	char* pp="hello";
	printf("%x\n",*p);//44
	printf("%x\n",*(p+1));//33
	printf("%x\n",*(p+2));//22
	printf("%x\n",*(p+3));//11
	printf("%u\n",pp);//710393860
	printf("%u\n",&"hello");//710393860
	printf("%u\n",&a);//3618536248
	printf("%u\n",&b);//3618536252
	test();
	return 0;
}
