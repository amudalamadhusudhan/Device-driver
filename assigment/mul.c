#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, const char *argv[])
{
    int fd, fd1;
    int num1, num2, r;
    printf("welcome to the writeapp1 \n\n enter the two numbers\n");
    scanf("%d%d", &num1, &num2);
    int mul[2] = {num1, num2};

    fd = open("/dev/mulDev", O_RDWR, 0777);

    if (fd < 0)
    {
        printf("cannot open the file \n");
        return 0;
    }
    printf("sususs in opening file\n");
    int result = write(fd, &mul, sizeof(mul));
    if (result < 0)
    {
        printf("error writing into the user to kernal\n");
    }
    printf("success in writing mul data from user to kernal\n");
    printf("..................read section.....................\n");
    fd1 = open("/dev/mulDev", O_RDWR, 0777);

    if (fd1 < 0)
    {
        printf("cannot open the file \n");
        return 0;
    }
    int res = read(fd1, &r, sizeof(r));
    if (res < 0)
    {
        printf("error reading into the user to kernal\n");
    }
    printf("success in reading data mul from user to kernal %d \n", r);

    close(fd);
    return 0;
}