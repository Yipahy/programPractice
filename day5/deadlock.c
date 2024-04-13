#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex1,mutex2;

void* fun1(void* arg)
{
	pthread_mutex_lock(&mutex1);
	printf("thread1 lock1");
	pthread_mutex_lock(&mutex2);
	printf("thread1 lock2");

	pthread_mutex_unlock(&mutex1);
	pthread_mutex_unlock(&mutex2);
	return NULL;
}

void* fun2(void* arg)
{
	pthread_mutex_lock(&mutex2);
	printf("thread2 lock2");
	pthread_mutex_lock(&mutex1);
	printf("thread2 lock1");

	pthread_mutex_unlock(&mutex1);
	pthread_mutex_unlock(&mutex2);
	return NULL;
}

int main()
{
	pthread_t tid1,tid2;
	pthread_mutex_init(&mutex1,NULL);
	pthread_mutex_init(&mutex2,NULL);

	pthread_create(&tid1,NULL,fun1,NULL);
	pthread_create(&tid2,NULL,fun2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
	return 0;
}
