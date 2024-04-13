#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd=-1,ret=-1;
	pid_t pid=-1;
	void* addr=NULL;

	fd=open("1.txt",O_RDWR);

	addr=mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(addr==MAP_FAILED)
	{
		perror("mmap");
		return 1;
	}

	close(fd);
	
	pid=fork();
	if(pid==-1)
	{
		perror("fork");
		goto err;
	}

	if(pid==0)
	{
		memcpy(addr,"12345678",8);
	}

	wait(NULL);

err:
	munmap(addr,1024);
	return 0;
}
