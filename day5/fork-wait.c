#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int main()
{
	int* status=NULL;
	int ret=-1;
	pid_t pid=-1;
	pid=fork();
	if(-1==pid)
	{
		perror("fork");
		return 1;
	}
	if(pid==0)
	{
		for(int i=0;i<3;++i)
		{
			printf("child process %d\n",i+1);
			sleep(1);
		}
		exit(10);
	}
	ret=wait(status);
	if(ret==-1)
	{
		perror("wait");
		return 1;
	}
	return 0;
}
