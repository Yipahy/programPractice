#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	srand((unsigned int)time(NULL));
	printf("随机数为%d\n",rand()%100);
	return 0;
}
