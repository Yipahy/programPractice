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

	int ret=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret<0)
	{
		perror("bind");
		return 1;
	}

	char buf[1500]="";
	struct sockaddr_in cliaddr;
	socklen_t len=sizeof(cliaddr);

	while(1)
	{
		memset(buf,0,1500);
		int n=recvfrom(fd,buf,1500,0,(struct sockaddr*)&cliaddr,&len);
		printf("%s\n",buf);
		sendto(fd,buf,n,0,(struct sockaddr*)&cliaddr,&len);
	}
	close(fd);
	return 0;
}

