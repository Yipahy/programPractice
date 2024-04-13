#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int num=0;

void* fun_write(void* arg)
{
	long index=(long)arg;
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock);
		++num;
		printf("tid:%ld modifiednum:%d\n",index,num);
		sleep(1);
		pthread_rwlock_unlock(&rwlock);
	}
	return NULL;
}

void* fun_read(void* arg)
{
	long index=(long)arg;
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock);
		printf("tid:%ld readnum:%d\n",index,num);
		sleep(2);
		pthread_rwlock_unlock(&rwlock);
	}
	return NULL;
}

int main()
{
	long i=0;
	pthread_t tid[8];

	pthread_rwlock_init(&rwlock,NULL);

	for(i=0;i<3;++i)
	{
		if(i==0)
		{
			pthread_create(&tid[i],NULL,fun_read,(void*)i);
		}else{
			pthread_create(&tid[i],NULL,fun_write,(void*)i);
		}
	}

	for(i=0;i<8;++i)
	{
		pthread_join(tid[i],NULL);
	}

	pthread_rwlock_destroy(&rwlock);
	return 0;
}
