#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("hello\n");
	execlp("ls","ll","/home/yys",NULL);
	printf("bye/n");
	return 0;
}
