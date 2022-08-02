#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
#include <unistd.h>

int main()
{
    int fd;
    char kbuff[40];
    char ubuff[40]="THIS IS TO KERNEL DUDE...\n";
    fd=open("/dev/mydevice2",O_RDWR,0777);
    if(fd<0)
    {
        printf("ERROR IN OPENING\n");
    }
    write(fd,ubuff,sizeof(ubuff));
    read(fd,kbuff,40);
    printf("OUTPUT .....%s...\n",kbuff);
    close(fd);
}
