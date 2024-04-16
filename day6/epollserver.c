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
	int lfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8080);
	inet_pton(AF_INET,"192.168.1.105",&addr.sin_addr.s_addr);

	bind(lfd,(struct sockaddr*)&addr,sizeof(addr));
	listen(lfd,128);
	
	int epfd=epoll_create(1);
	struct epoll_event ev,evs[1024];
	ev.data.fd=lfd;
	ev.events=EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);

	while(1)
	{
		int nready=epoll_wait(epfd,evs,1024,-1);
		if(nready==0)
		{
			continue;
		}else{
			for(int i=0;i<nready;++i)
			{
				if(evs[i].data.fd==lfd && (evs[i].events&EPOLLIN))
				{
					struct sockaddr_in cliaddr;
					char ip[16]="";
					socklen_t len=sizeof(cliaddr);

					int cfd=accept(lfd,(struct sockaddr*)&cliaddr,&len);

					int flags=fcntl(cfd,F_GETFL);
					flags |= O_NONBLOCK;
					fcntl(cfd,F_SETFL,flags);

					ev.data.fd=cfd;
					ev.events=EPOLLIN|EPOLLET;
					epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);
				}
				else if(evs[i].events & EPOLLIN)
				{
					while(1)
					{
						char buf[4]="";
						int n=read(evs[i].data.fd,buf,4);
						if(n<0)
						{
							if(errno==EAGAIN) break;
							perror("read");
							close(evs[i].data.fd);
							epoll_ctl(epfd,EPOLL_CTL_DEL,evs[i].data.fd,&evs[i]);
							break;
						}else if(n==0){
							printf("client close\n");
							close(evs[i].data.fd);
							epoll_ctl(epfd,EPOLL_CTL_DEL,evs[i].data.fd,&evs[i]);
						}else{
							write(STDOUT_FILENO,buf,4);
							write(evs[i].data.fd,buf,n);
						}
					}
				}
			}
		}
	}
	close(lfd);
	return 0;
}

