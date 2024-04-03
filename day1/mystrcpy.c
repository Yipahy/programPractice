#include <stdio.h>

void mystrcpy(char* dest,char* src)
{
	while(*dest++=*src++);
}
int main()
{
	char* str="hello world";
	char buf[1024];
	mystrcpy(buf,str);
	printf("buf=%s\n",buf);
	return 0;
}
