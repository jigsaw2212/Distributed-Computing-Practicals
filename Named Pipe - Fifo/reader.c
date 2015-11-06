#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define MAX 100

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    char str[MAX];

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, str, MAX);
    printf("Received: %s\n", str);
    close(fd);

    return 0;
}