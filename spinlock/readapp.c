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
    int op_result;
    printf("welcome to the readapp \n\n enter the two numbers\n");

    fd = open("/dev/readspin", O_RDWR, 0777);

    if (fd < 0)
    {
        printf("cannot open the file \n");
        return 0;
    }
    printf("sususs in opening file\n");
    int result = read(fd, &op_result, sizeof(op_result));
    if (result < 0)
    {
        printf("error reading into the user to kernal\n");
    }
    printf("success in reading data from user to kernal %d \n", op_result);

    close(fd);
    return 0;
}