#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int flag=0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* producer(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		++flag;
		pthread_mutex_unlock(&mutex);
		sleep(1);
		pthread_cond_signal(&cond);//唤醒条件变量并申请锁
	}
	return NULL;
}

void* consumer(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);//阻塞条件变量并释放锁
		if(flag%2==0)
		{
			printf("flag:%d\n",flag);
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main()
{
	pthread_t tid1,tid2;

	pthread_cond_init(&cond,NULL);
	pthread_mutex_init(&mutex,NULL);

	pthread_create(&tid1,NULL,producer,NULL);
	pthread_create(&tid2,NULL,consumer,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	return 0;
}
