#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ioctl.h"
#include <sys/ioctl.h>

int main(int argc, const char *argv[])
{
    int fd;
    fd = open("/dev/MADHU", O_RDWR);
    if (fd < 0)
    {
        printf("cannot open the file \n");
        return 0;
    }
    printf("fd = %d\n", fd);
    ioctl(fd, CMD_1);
    ioctl(fd, CMD_2, 8);
    close(fd);
    return 0;
}