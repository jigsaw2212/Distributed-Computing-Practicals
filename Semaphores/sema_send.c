/*
Semaphores are used as locking mechanisms used to control access to shared 
resources by multiple processes. They are mostly used as locking mechanisms.

They can also act as resource counters along with the locking mechanism

The kernel maintains a special internal data structure for each semaphore set in its address space.

semget() system call is used to create a new semaphore set.
returns semaphore set IPC identifier on success
returns -1 on error
First argument-> key value
Second argument-> nsems; specifies the no of semaphores that should be created in the new set
Third argument-> semflg argument which is generally IPC_CREAT referring to creating the semaphore

semop() is used to perform operations on a semaphore set. 
returns 0 on success
First argument-> semaphore id recieved earlier
Second argument-> sops; pointer to the array of operations to be performed on the semaphore set
Third argument-> no of operations in that array

sops argument points to an array of type sembuf
 /* semop system call takes an array of these 
        struct sembuf {
                ushort  sem_num;        // number of semaphore
                short   sem_op;         // semaphore operations to perform
                short   sem_flg;        // operation flags 
        };

NOWAIT flag returns control to the caller, when instead the process must have bee blocking
*/