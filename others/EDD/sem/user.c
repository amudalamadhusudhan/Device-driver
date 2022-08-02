#include<stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include <sys/stat.h>
#include <unistd.h>



int main()
{

int fp;

char kbuff[100];
 pid_t num;

fp = open("/dev/SEM", O_RDWR, 0777);
if(fp<0)
{
    printf("\n ERROR in the Opening device");
    exit(1);  
}
num = fork();
if(0==num)
{
    while(1){
    char ubuff[] = "123";
write(fp,ubuff,sizeof(ubuff)); // writing to kernel
sleep(20);
// read(fp,kbuff,sizeof(kbuff)); 
// printf("string : %s \n",kbuff);
}
}
else
{
// char ubuff[] = "ashutosh";
//  write(fp,ubuff,sizeof(ubuff)); // writing to kernel
while(1){
read(fp,kbuff,sizeof(kbuff)); 
printf("string : %s \n",kbuff);
sleep(10);
}
 }
close(fp);
}

// this file include read write and syn by spinlocks and completion