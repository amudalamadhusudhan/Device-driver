#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "control.h"

struct default_data
{
    int baud_rate;
    int stop_bits;
    int parity;
};

int main()
{
    int fd,result,BAUD_RATE =9600,STP_BITS=8;
    struct default_data ToSend={9600,1,0};
    char ubuff[60]="THIS IS USER BUFFER ..SENDING DATA TO KERNEL..\n";
    char kbuff[60];
    fd=open("/dev/IOCTL_0",O_RDWR,0777);
    if(fd<0)
    {
        printf("\n ERROR IN OPENING.\n");
        exit(1);
    }
   result=ioctl(fd,SET_BAUD_RATE , &BAUD_RATE);
    if(result<0)
    {
        printf("\n IOCTL ERROR..\n");
        return(-1);
    }
   // printf("THE BAUD CONFIRMATION :%d..\n",BAUD_RATE);
    
    ioctl(fd,SET_NO_STOP_BITS,&STP_BITS);
    ioctl(fd,SET_DIRECTION_WRITE,NULL);
    ioctl(fd,DEFAULT_DATA,&ToSend);

    write(fd,ubuff,sizeof(ubuff));
    read(fd,kbuff,sizeof(kbuff));
    printf("DATA READ FROM KERNEL..\n >>> %s <<<..\n",kbuff);
    close(fd);
}
