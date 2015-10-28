#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    char str[100];

    printf("Enter message to send: ");
    gets(str);

    /* write "Hi" to the FIFO */
    fd = open(myfifo, O_WRONLY);
    write(fd, str, sizeof(str));
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);

    return 0;
}