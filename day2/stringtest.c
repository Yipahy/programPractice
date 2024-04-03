#include <stdio.h>
#include <string.h>

int main()
{
	char* str="dkjehbn.efqef";
	char* pos=strchr(str,'e');
	if(pos!=NULL)
	{
		printf("e的正向下标为%ld\n",pos-str);
	}
	char* pos2=strrchr(str,'e');
	if(pos2!=NULL)
	{
		printf("e的反向下标为%ld\n",pos2-str);
	}
	char* str1="jehb";
	char* pos3=strstr(str,str1);
	if(pos3!=NULL)
	{
		printf("str的子串str1首字母下标为%ld\n",pos3-str);
	}
	return 0;
}
