#include <stdio.h>
#include <string.h>

int main()
{
	FILE* fd=fopen("1.txt","w+");
	if(fd==NULL)
	{
		perror("fopen");
		return 1;
	}
	int ret=fputc('d',fd);
	if(ret==EOF)
	{
		perror("fputc");
	}
	rewind(fd);
	ret=fgetc(fd);
	printf("fgetc=%c\n",ret);
	ret=fputs("\nniubi plus\n",fd);
	if(ret==EOF)
	{
		perror("fputs");
	}

	rewind(fd);
	char str[1024];
	fgets(str,1024,fd);//读到\n停止
	printf("str=%s\n",str);//d

	int year,month,day;
	fprintf(fd,"%d-%02d-%02d\n",2024,4,3);
	fseek(fd,0,SEEK_SET);
	fscanf(fd,"%d-%d-%d",&year,&month,&day);
	printf("year=%d month=%d day=%d\n",year,month,day);
	
	char buf[1024];
	memset(buf,0,sizeof(buf));
	strcpy(buf,"hello world\n");
	fwrite(buf,sizeof(char),12,fd);

	rewind(fd);
	fread(buf,1,1024,fd);
	printf("buf=%s\n",buf);
	fclose(fd);
	return 0;
}
