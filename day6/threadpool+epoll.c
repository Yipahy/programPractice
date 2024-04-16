#include "threadpool.h"

threadPool* thrpool=NULL;
int beginnum=1000;

void* thrRun(void* arg)
{
	threadPool* thrpool=(threadPool*)arg;
	int taskpos=0;
	poolTask* task=(poolTask*)malloc(sizeof(poolTask));

	while(1)
	{
		pthread_mutex_lock(&thrpool->poolmutex);
		while(thrpool->jobnum<=0&&(thrpool->shutdown==0))
		{
			pthread_cond_wait(&thrpool->taskready,&thrpool->poolmutex);
		}
		if(thrpool->jobnum)
		{
			taskpos=(thrpool->jobpop++)%thrpool->maxjobnum;
			memcpy(task,&thrpool->tasks[taskpos],sizeof(poolTask));
			task->arg=task;
			thrpool->jobnum--;
			pthread_cond_signal(&thrpool->fullqueue);
		}
		if(thrpool->shutdown)
		{
			pthread_mutex_unlock(&thrpool->poolmutex);
			free(task);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&thrpool->poolmutex);
		task->taskfunc(task->arg);
	}
}

void createThreadPool(int thrnum,int maxtasknum)
{
	thrpool=(threadPool*)malloc(sizeof(threadPool));
	thrpool->threadnum=thrnum;
	thrpool->maxjobnum=maxtasknum;
	thrpool->shutdown=0;
	thrpool->jobnum=0;
	thrpool->jobpush=thrpool->jobpop=0;
	thrpool->tasks=(poolTask*)malloc(sizeof(poolTask)*maxtasknum);
	thrpool->threads=(pthread_t*)malloc(sizeof(pthread_t)*thrnum);

	pthread_mutex_init(&thrpool->poolmutex,NULL);
	pthread_cond_init(&thrpool->fullqueue,NULL);
	pthread_cond_init(&thrpool->taskready,NULL);

	for(int i=0;i<thrnum;++i)
	{
		pthread_create(&thrpool->threads[i],NULL,thrRun,(void*)thrpool);
	}
}

void taskRun(void* arg)
{
	poolTask* task=(poolTask*)arg;
	char buf[1500]="";
	int n=read(task->fd,buf,sizeof(buf));
	if(n==0)
	{
		close(task->fd);
		epoll_ctl(task->epfd,EPOLL_CTL_DEL,task->fd,task->evs);
		printf("client close\n");
	}else if(n>0)
	{
		printf("%s\n",buf);
		write(task->fd,buf,n);
	}
}

void addtask(threadPool* pool,int fd,struct epoll_event* evs)
{
	pthread_mutex_lock(&pool->poolmutex);
	while(pool->maxjobnum<=pool->jobnum)
	{
		pthread_cond_wait(&pool->fullqueue,&pool->poolmutex);
	}
	int taskpos=(pool->jobpush++)%pool->maxjobnum;
	pool->tasks[taskpos].tasknum=beginnum++;
	pool->tasks[taskpos].arg=(void*)&pool->tasks[taskpos];
	pool->tasks[taskpos].taskfunc=taskRun;
	pool->jobnum++;
	pool->tasks[taskpos].fd=fd;
	pool->tasks[taskpos].evs=evs;
	pthread_mutex_unlock(&pool->poolmutex);
	pthread_cond_signal(&pool->taskready);
}

void destroythreadpool(threadPool* pool)
{
	pool->shutdown=1;
	pthread_cond_broadcast(&pool->taskready);
	for(int i=0;i<pool->threadnum;++i)
	{
		pthread_join(pool->threads[i],NULL);
	}
	pthread_cond_destroy(&pool->taskready);
	pthread_cond_destroy(&pool->fullqueue);
	pthread_mutex_destroy(&pool->poolmutex);
	free(pool->tasks);
	free(pool->threads);
	free(pool);
}

int main()
{
	int lfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8000);
	inet_pton(AF_INET,"192.168.1.105",&addr.sin_addr.s_addr);

	bind(lfd,(struct sockaddr*)&addr,sizeof(addr));
	listen(lfd,128);
	
	int epfd=epoll_create(1);
	struct epoll_event ev,evs[1024];
	ev.data.fd=lfd;
	ev.events=EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);

	createThreadPool(3,20);

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
					addtask(thrpool,evs[i].data.fd,&evs[i]);
				}
			}
		}
	}
	close(lfd);
	destroythreadpool(thrpool);
	return 0;
}

