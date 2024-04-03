#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	char* p=(char *)malloc(64);
	memset(p,0,64);
	strncpy(p,"hello world",64);
	printf("%s\n",p);
	p=(char *)realloc(p,128);//不会清空原来内容
	printf("%s\n",p);
	p=(char *)calloc(64,sizeof(char));//会自动对分配空间赋0
	printf("%s\n",p);
	return 0;
}
