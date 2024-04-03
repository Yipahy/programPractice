#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getFileLines(FILE* fd);
void readFileData(FILE* fd,char** pArray,int lines);
void printFileData(char** pArray,int lines);
void freeMemory(char** pArray,int lines);

int main()
{
	FILE* fd=fopen("1.txt","r");
	if(fd==NULL)
	{
		perror("fopen");
		return 1;
	}

	int len=getFileLines(fd);
	char** pArray=malloc(sizeof(char*)*len);
	readFileData(fd,pArray,len);
	printFileData(pArray,len);
	freeMemory(pArray,len);
	fclose(fd);
	return 0;
}

int getFileLines(FILE* fd)
{
	char buf[1024];
	int lines=0;
	while(fgets(buf,1024,fd)!=NULL) ++lines;

	fseek(fd,0,SEEK_SET);
	return lines;
}

void readFileData(FILE* fd,char** pArray,int lines)
{
	if(lines<=0||pArray==NULL) return;

	char buf[1024];
	int index=0;
	while(NULL!=fgets(buf,1024,fd))
	{
		int curlen=strlen(buf)+1;
		buf[strlen(buf)-1]='\0';
		char* curptr=malloc(sizeof(char*)*curlen);
		strcpy(curptr,buf);
		pArray[index++]=curptr;
		memset(buf,0,1024);
	}
}

void printFileData(char** pArray,int lines)
{
	for(int i=0;i<lines;++i)
	{
		printf("第%d行数据:%s\n",i+1,pArray[i]);
	}
}

void freeMemory(char** pArray,int lines)
{
	for(int i=0;i<lines;++i)
	{
		free(pArray[i]);
		pArray[i]=NULL;
	}
	free(pArray);
	pArray=NULL;
}
