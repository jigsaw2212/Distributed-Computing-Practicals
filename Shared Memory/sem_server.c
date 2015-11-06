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
 int semid,count=0,fd;
 struct sembuf put,get;
 union semun u;
 unsigned a[2]={1,0};
 semid=semget(KEY,2,IPC_CREAT|IPC_EXCL|0666);
 u.array=a;
 semctl(semid,0,SETALL,u);
 fd=open("buff",O_CREAT|O_RDWR,0666);
 write(fd,&count,sizeof(int));
 while(1)
 {
 put.sem_num=0;
 put.sem_op=-1;
 put.sem_flg=0;
 semop(semid,&put,1);
 lseek(fd,0,0);
 read(fd,&count,sizeof(int));
 count++;
 lseek(fd,0,0); 
 write(fd,&count,sizeof(int));
 printf("Produced item: %d\n",count);
 get.sem_num=1;
 get.sem_op=1;
 get.sem_flg=0;
 semop(semid,&get,1);
 sleep(5); 
 }
 close(fd);
}