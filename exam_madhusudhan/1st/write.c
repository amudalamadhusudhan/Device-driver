
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, const char *argv[])
{
    int fd;
    int num1,num2;
    printf("welcome to the writeapp1 \n\n enter the two numbers\n");
    scanf("%d%d",&num1,&num2);
    int numbers[2]={num1,num2};

    fd = open("/dev/write_app1", O_RDWR,0777);

    if (fd < 0)
    {
        printf("cannot open the file \n");
        return 0;
    }
   printf("sususs in opening file\n");
   int result =write(fd,&numbers,sizeof(numbers));
   if(result<0)
   {
          printf("error writing into the user to kernal\n");

    }
     printf("success in writing data from user to kernal\n");
        
    close(fd);
    return 0;
}