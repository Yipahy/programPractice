#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char buf[1024];
	memset(buf,0,sizeof(buf));
	sprintf(buf,"today is %d-%02d-%02d",2024,4,3);
	printf("buf=%s\n",buf);
	int year,month,day;
	year=month=day=0;
	sscanf(buf,"%*[^0-9]%d-%d-%d",&year,&month,&day);
	printf("year=%d month=%d day=%d\n",year,month,day);
	char* netaddr="http://www.baidu.com/2.html";
	char company[64];
	char file22[64];
	sscanf(netaddr,"%*[^.].%[a-z]%*[^/]/%[0-9.a-z]",company,file22);
	printf("company=%s file=%s\n",company,file22);
	char* email="yipahylee@gmail.com";
	char username[64],emailcom[64];
	sscanf(email,"%[^@]@%s",username,emailcom);
	printf("user=%s emailcom=%s\n",username,emailcom);
	return 0;
}
