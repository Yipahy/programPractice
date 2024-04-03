#include <stdio.h>
#include <string.h>

int main(){
	char p[16];
	char* pp=NULL;
	strcpy(p,"1111");
	printf("%s\n",p);
	printf("pp的地址:%d\n",pp);
	printf("pp的地址:%d\n",pp+1);
	printf("pp的值:%s\n",pp);
	char buf[1024];
	int a=666;
	memcpy(buf,&a,sizeof(int));
	printf("buf的值:%d\n",*(int *)buf);//转为int*的原因，要取4B
	return 0;
}
