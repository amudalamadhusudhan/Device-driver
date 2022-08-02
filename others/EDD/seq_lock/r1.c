
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main()
{
    int fd;
    char kbuff[40];
    fd=open("/dev/AUS",O_RDWR,0777);
    if(fd<0)
    {
        printf("ERROR IN OPENING.\n");
        exit(1);
    }
    read(fd,kbuff,sizeof(kbuff));
    printf("OUTPUT OF R2 ..%s\n",kbuff);
    close(fd);
}
