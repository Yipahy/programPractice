#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main()
{
	int ret=-1;
	pid_t pid=-1;
	time_t t=-1;
	struct tm* pt=NULL;
	char filename[256];

	pid=fork();
	if(pid>0)
	{
		exit(0);
	}

	setsid();

	chdir("/");
	umask(0);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(1)
	{
		t=time(NULL);
		pt=localtime(&t);

		memset(filename,0,256);
		sprintf(filename,"%s %d %d %d %d %d %d","touch /tmp/log",
				pt->tm_year+1900,pt->tm_mon+1,pt->tm_mday,pt->tm_hour,
				pt->tm_min,pt->tm_sec);
		system(filename);
		sleep(1);
	}
	return 0;
}
