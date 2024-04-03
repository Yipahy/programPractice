#include <stdio.h>

int main()
{
	char str[]="hello";//自动后面补0
	char str1[]={'h','e','l','l','o'};//不会自动补0
	char str2[]="hello\0world";//\0终止
	char str3[100]={'h','e','l','l','o'};//自动补0
	printf("str=%s\n",str);
	printf("str1=%s\n",str1);
	printf("str2=%s\n",str2);
	printf("str3=%s\n",str3);
	return 0;
}

