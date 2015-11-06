#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd; int status;
    char * myfifo = "/tmp/myfifo";
    //defines the file name of the fifo we want to create

    
    status = mkfifo(myfifo, 0666);
    //0666 is the mode of the fifo, which defines the permissions


    /*status = 0 means failure
    if(status==-1)
    {
        printf("Error\n");
        return 0;
    }*/


    char str[100];

    printf("Enter message to send: ");
    gets(str);

    fd = open(myfifo, O_WRONLY);
    write(fd, str, sizeof(str));
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);

    return 0;
}

/*
Difference b/w mknod and mkfifo:-
1. mknod is more portable. Not all machines supprt mkfifo.
2. mode is handled differently among the two. mknod specifies both the 
premission to create and the type of file to be created.

mknod syntax:-
int mknod(const char *pathname, mode_t mode, dev_t dev)

mkfifo syntax:-
int mkfifo(const char *pathname, mode_t mode)

 Since the pipe resides in the kernel and not on a physical filesystem

Blocking occurs on a FIFO. If the FIFO is opened for writing, the process 
will block untill some other process opens it up for reading.
O_NONBLOCK flag can be used in an open() call to disable the default blocking action.
*/