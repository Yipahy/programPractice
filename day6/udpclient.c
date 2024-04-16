#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>

int main()
{
	int fd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8888);
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr.s_addr);

	char buf[1500]="";

	while(1)
	{
		memset(buf,0,1500);
		int n=read(STDIN_FILENO,buf,1500);
		sendto(fd,buf,n,0,(struct sockaddr*)&addr,sizeof(addr));
		n=recvfrom(fd,buf,1500,0,NULL,NULL);
		printf("%s\n",buf);
	}
	close(fd);
	return 0;
}

