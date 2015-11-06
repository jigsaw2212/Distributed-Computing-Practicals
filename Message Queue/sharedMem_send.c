/*
Shared is the fastest medium of IPC communication. It's doesn't require any intermediate structures to communicate.
Shared memory segments exist in the kernel's address space only.

shmget() system call is used to create a new shared memory. 
Returns the shared memory segment identifier on success, and -1 on error.
First argument - key value
Second argument - requested segment size
Third argument shmflag which can be used to set the creating control flags like IPC_CREAT

shmat() is used to attach a shared memory to a process address space.
It returns a pointer 'shmaddr' to the head of the shared segment.
First argument -> shmid
Second argument -> shmaddr, usually kept 0. ) means that the system will select the starting address for the caller.
Third argument -> shmflg

shmdt() detaches the shared memory segment located at the address indicated by shmaddr.
This doesn't remove the segment from the kernel!

*/ 

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
    s = shm;

    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;

    /*
     * Finally, we wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    while (*shm != '*')
        sleep(1);

    exit(0);
}