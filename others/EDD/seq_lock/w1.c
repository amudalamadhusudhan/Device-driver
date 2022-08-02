
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main()
{
    int fd;
    char ubuff[40]="ashutosh here";
    fd=open("/dev/AUS",O_RDWR,0777);
    if(fd<0)
    {
        printf("ERROR IN OPENING.\n");
        exit(1);
    }
    write(fd,ubuff,sizeof(ubuff));
    printf("WRITING DONE\n");
    close(fd);
}
