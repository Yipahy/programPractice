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

typedef struct _poolTask
{
	int tasknum;
	int fd;
	int epfd;
	struct epoll_event* evs;
	void* arg;
	void (*taskfunc)(void* arg);
}poolTask;

typedef struct _threadPool
{
	int maxjobnum;
	int jobnum;
	int jobpush;
	int jobpop;
	int threadnum;
	int shutdown;
	pthread_t* threads;
	poolTask* tasks;
	pthread_mutex_t poolmutex;
	pthread_cond_t fullqueue;
	pthread_cond_t taskready;
}threadPool;

void* thrRun(void* arg);
void createThreadPool(int thrnum,int maxtasknum);
void taskRun(void* arg);
void addtask(threadPool* pool,int fd,struct epoll_event* evs);
void destroythreadpool(threadPool* pool);
