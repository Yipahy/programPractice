#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void func(int signo,siginfo_t* info,void* context)
{
	printf("capture signal:%d\n",signo);
}
int main()
{
	int ret=-1;
	struct sigaction act;
	act.sa_sigaction=func;
	act.sa_flags=SA_SIGINFO;
	ret=sigaction(SIGINT,&act,NULL);
	if(ret==-1)
	{
		perror("perror");
		return 1;
	}
	sleep(30);
	return 0;
}
