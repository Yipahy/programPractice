#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int main()
{
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
		exit(0);
	}
	sleep(100);
	return 0;
}
