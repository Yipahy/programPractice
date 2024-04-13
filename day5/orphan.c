#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main()
{
	pid_t pid=fork();
	if(pid>0)
	{
		printf("parent process over");
		exit(0);
	}
	while(1)
	{
		printf("parent process of child process ppid:%d\n",getppid());
		sleep(1);
	}
	return 0;
}
