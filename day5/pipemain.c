#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int ret=-1;
	int fds[2];
	pid_t pid=-1;
	char buf[128];

	ret=pipe(fds);

	pid =fork();

	if(pid==0)
	{
		close(fds[1]);
		memset(buf,0,128);
		ret=fcntl(fds[0],F_GETFL);
		ret |= O_NONBLOCK;
		fcntl(fds[0],F_SETFL,ret);

		read(fds[0],buf,128);
		write(STDOUT_FILENO,buf,128);
		close(fds[0]);
	}
	close(fds[0]);
	read(STDOUT_FILENO,buf,128);
	write(fds[1],buf,128);
	close(fds[1]);
	return 0;
}
