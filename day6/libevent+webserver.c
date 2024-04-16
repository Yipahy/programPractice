#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <event.h>
#include <event2/event.h>
#include <sys/epoll.h>

void readcb(struct bufferevent* bev,void* ctx);
void beventcb(struct bufferevent* bev,short what,void* ctx);
int http_request(struct bufferevent* bev,char* path);
int copyheader(struct bufferevent* bev,int op,char* msg,char* filetype,long filesize);
int copyfile(struct bufferevent* bev,char * strfile);

void _listencb(struct evconnlistener* listener,int cfd,void* ctx)
{
	struct event_base* base=(struct event_base*)ctx;
	struct bufferevent* bev=bufferevent_socket_new
			(base,cfd,BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev,readcb,NULL,beventcb,base);
	bufferevent_enable(bev,EV_READ|EV_WRITE);
}

int main(int argc,char* argv[])
{
	char workdir[256]="";
	strcpy(workdir,getenv("PWD"));
	printf("%s\n",workdir);
	chdir(workdir);

	struct event_base* base=event_base_new();
	struct sockaddr_in servaddr;
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(9999);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	struct evconnlistener* listener=evconnlistener_new_bind
		(base,_listencb,base,BEV_OPT_CLOSE_ON_FREE,-1,(struct sockaddr*)&servaddr,sizeof(servaddr));

	event_base_dispatch(base);
	evconnlistener_free(listener);
	return 0;
}

void readcb(struct bufferevent* bev,void* ctx)
{
	char buf[256]="";
	char method[10],path[256],protocol[10];
	int ret=bufferevent_read(bev,buf,sizeof(buf));
	if(ret>0)
	{
		sscanf(buf,"%[^ ] %[^ ] %[^ \r\n]",method,path,protocol);
		if(strcasecmp(method,"get")==0)
		{
			char bufline[256]="";
			write(STDOUT_FILENO,buf,ret);
			while((ret=bufferevent_read(bev,bufline,sizeof(bufline)))>0)
			{
				write(STDOUT_FILENO,bufline,ret);
			}
			http_request(bev,path);
		}
	}
}

void beventcb(struct bufferevent* bev,short what,void* ctx)
{
	if(what&BEV_EVENT_EOF)
	{
		printf("client close\n");
		bufferevent_free(bev);
	}else if(what&BEV_EVENT_ERROR){
		printf("error or client closed\n");
		bufferevent_free(bev);
	}else if(what&BEV_EVENT_CONNECTED){
		printf("client connecting\n");
	}
}

int http_request(struct bufferevent* bev,char* path)
{
	strdecode(path,path);
	char* strpath=path;
	if(strcmp(strpath,"/")==0||strcmp(strpath,"/.")==0)
	{
		strpath="./";
	}else{
		strpath=path+1;
	}
	struct stat st;
	if(stat(strpath,&st)<0)
	{
		copyheader(bev,404,"Not Found","error.html",-1);
		copyfile(bev,"error.html");
		return -1;
	}

	if(S_ISREG(st.st_mode))
	{
		copyheader(bev,200,"ok","txt",st.st_size);
		copyfile(bev,strpath);
	}

	return 0;
}

int copyheader(struct bufferevent* bev,int op,char* msg,char* filetype,long filesize)
{
	char buf[4096]="";
	sprintf(buf,"HTTP/1.1 %d %s\r\n",op,msg);
	sprintf(buf,"%s Content-Type:%s\r\n",buf,filetype);
	if(filesize>=0)
	{
		sprintf(buf,"%s Content-Length:%ld\r\n",buf,filesize);
	}
	strcat(buf,"\r\n");
	bufferevent_write(bev,buf,strlen(buf));
	return 0;
}

int copyfile(struct bufferevent* bev,char * strfile)
{
	int fd=open(strfile,O_RDONLY);
	char buf[1024]="";
	int ret=-1;
	while((ret=read(fd,buf,sizeof(buf)))>0)
	{
		bufferevent_write(bev,buf,ret);
	}
	close(fd);
	return 0;
}
/*
int senddir(struct bufferevent* bev,char* strpath)
{
	copyfile(bev,_DIR_PREFIX_FILE_);
	DIR* dir=opendir(strpath);
	if(dir==NULL)
	{
		perror("opendir");
		return -1;
	}
	char bufline[1024]="";
	struct dirent* dent=NULL;
	while(dent=readdir(dir))
	{
		struct stat st;
		stat(dent->d_name,&st);
		bufferevent_write(bev,bufline,strlen(bufline));
		close(dir);
		copyfile(bev,_DIR_TAIL_FILE_);
		return 0;
	}
}
*/
