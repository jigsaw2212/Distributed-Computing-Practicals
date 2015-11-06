/*
msgget() system call is used in order to create a new message queue,
or access an existing queue. The first argument to msgget() is the kemsgget() return -1 on errory value which 
we use to identify the message queue and IPC_CREAT to creat the queue
msgget() return -1 on error, else the message queue identifier

msgsnd() -> returns 0 on success and -1 on error.
First argument is the queue identifier, second argument is the pointer to the message buffer.
Third argument gives us the size of the message. The last argument is the msglfg.
msgflg is usually set to 0 or IPC_NOWAIT

msgrcv() -> returns no of bytes copied into message buffer and -1 on error
First argument is the queue identifier. Second argument stores the address of the message buffer  
where we have to store the incoming messages at. Third argument stores size of message buffer as usual.
Fourth argument is mtype, which specifies the type of message to be retrieved from the queue.
If mtype = 0, the oldest message is retrieved regardless of anything.
The fifth argument is the msgflg.



*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<string.h>
#define KEY 500
struct msg
{
 long int type;
 char a[1024];
 int pid;
}p;
int main()
{
 int m,n,fd,m1;
 m=msgget(KEY,0666|IPC_CREAT);
 while(1)
 {
 msgrcv(m,&p,sizeof(p),1,0);
 printf("Message from Client: %s\n",p.a);
 fd=open(p.a,O_RDONLY);
 n=read(fd,p.a,1024);
 p.type=p.pid;
 p.pid=getpid();
 //msgsnd(m,&p,sizeof(p),0);
 
 }

 return 0;
}