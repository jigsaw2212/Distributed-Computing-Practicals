#include<stdio.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<fcntl.h>
#define KEY 1010
 union semun {
               int              val;
               struct semid_ds *buf;
               unsigned short  *array;
               struct seminfo  *__buf;
           };

void main()
{
 int semid,count,fd;
 struct sembuf put,get;
 semid=semget(KEY,0,0);
 fd=open("buff",O_RDONLY);
 while(1)
 {
 get.sem_num=1;
 get.sem_op=-1;
 get.sem_flg=0;
 semop(semid,&put,1);
 lseek(fd,0,0);
 read(fd,&count,sizeof(int));
 printf("Consumed item: %d\n",count);
 put.sem_num=0;
 put.sem_op=1;
 put.sem_flg=0;
 semop(semid,&put,1);
 sleep(5); 
 }
 close(fd);
}