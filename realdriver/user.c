#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define size 1024
int8_t write_buf[size];
int8_t read_buf[size];
int main()
{
    int fd;
    int options;
    fd = open("/dev/realdriver", O_RDWR);
    if (fd < 0)
    {
        printf("cannot open the file \n");
        return 0;
    }
    while (1)
    {
        printf(".....enter the device file .....");
        printf("1 write 2 read 3 exit\n");
        scanf("%d", &options);
        printf("your option is %d\n", options);

        switch (options)
        {
        case 1:
            printf("enter the string write into driver \n");
            scanf("%s", write_buf);
            write(fd, write_buf, strlen(write_buf) + 1);
            printf("done\n");
            break;
        case 2:
            printf("reading data \n");
            read(fd, write_buf, size);
            printf("done\n");
            printf("data = %s\n\n", write_buf);
            break;
        case 3:
            close(fd);
            exit(1);
            break;
        default:
            printf("wrong chioce");
            break;
        }
    }
    close(fd);
    return 0;
}