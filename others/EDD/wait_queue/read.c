
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,const char *argv[])
{
    int fd;
    char kbuff[60];
    
    fd=open("/dev/RSA",O_RDWR,0777);
    if(fd<0)
    {
        printf("ERROR IN OPENING..\n");
        exit(1);
    }
    read(fd,kbuff,sizeof(kbuff));
    printf("KERNEL OUTPUT ..%s",kbuff);
   

    
    close(fd);
    return 0;
}