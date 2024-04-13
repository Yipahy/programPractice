#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fdr=-1,fdw=-1;
	char buf[1024];

	fdw=open("fifo1",O_WRONLY);

	fdr=open("fifo2",O_RDONLY);

	while(1)
	{
		memset(buf,0,1024);
		fgets(buf,1024,stdin);
		if(buf[strlen(buf)-1]=='\n')
			buf[strlen(buf)-1]='\0';

		write(fdw,buf,strlen(buf));
		memset(buf,0,1024);
		read(fdr,buf,1024);
		printf("talk1:%s\n",buf);
	}

	close(fdw);
	close(fdr);
	return 0;
}
