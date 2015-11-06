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

/*
** shmdemo.c -- read and write to a shared memory segment
*/

/*
** shmdemo.c -- read and write to a shared memory segment
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

int main()
{
	key_t key;
	int shmid;
	char *data;
	int mode;


	/* make the key: */
	if ((key = ftok("sharedMem.c", 'R')) == -1) {
		perror("ftok");
		exit(1);
	}

	/* connect to (and possibly create) the segment: */
	if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
		perror("shmget");
		exit(1);
	}

	char buff[100];

	/* attach to the segment to get a pointer to it: */
	data = shmat(shmid, (void *)0, 0);
	if (data == (char *)(-1)) {
		perror("shmat");
		exit(1);
	}


	char ch = 'y';

		while(ch == 'y' || ch=='Y')
		{	
			printf("Enter message: ");
			scanf("%s",buff);
			printf("writing to segment...\n");
		
			strncpy(data, buff, SHM_SIZE);

			printf("Wish to enter more?(y/n): ");
			fflush(stdin);
			scanf("%s",&ch);
		}

	/* detach from the segment: */
	if (shmdt(data) == -1) {
		perror("shmdt");
		exit(1);
	}

	return 0;
}