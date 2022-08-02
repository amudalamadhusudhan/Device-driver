#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "timer.h"

int main()
{
    int fd;
    fd=open("/dev/timer",O_RDWR);
    if(fd<0)
    {
        perror("error");
        exit(EXIT_FAILURE);
    }
    printf("enter the amount of time to delay..\n");
    int delay;
    scanf("%d",&delay);
    printf("DELAY TIME : %d\n",delay);
    ioctl(fd,set_periodicity,&delay);

    close(fd);

    return 0;
}