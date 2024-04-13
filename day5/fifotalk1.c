#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fdr=-1,fdw=-1;
	char buf[1024];

	fdr=open("fifo1",O_RDONLY);

	fdw=open("fifo2",O_WRONLY);

	while(1)
	{
		memset(buf,0,1024);
		read(fdr,buf,1024);
		printf("talk2:%s\n",buf);
		memset(buf,0,1024);
		fgets(buf,1024,stdin);
		if(buf[strlen(buf)-1]=='\n')
			buf[strlen(buf)-1]='\0';

		write(fdw,buf,strlen(buf));
	}

	close(fdw);
	close(fdr);
	return 0;
}
