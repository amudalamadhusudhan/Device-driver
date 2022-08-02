#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>


int main()
{
	int fd ;
	char Ubuff[]="This is the user buffer......Sending data to kernel\n";
	char kbuff[100];
	fd= open("/dev/desd",O_RDWR,0777);

	if(fd<0)
	{
		perror("open %s \n");
		exit(-1);
	}

	return 0;
}



// init module to isnttalll the module 
// del to del 
//  mknod /de/"drivername" c major minor


