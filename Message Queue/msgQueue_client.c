#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define KEY 500
struct msg
{
 long int type;
 char a[1024];
 int pid;
}p,p1;
int main()
{
 int m;
 m=msgget(KEY,0);
 p.type=1;

 	int t;

 	cout<<"Enter number of messages: ";
 	cin>>t;

 	while(t--)
 	{
	 printf("\nEnter message: ");
	 gets(p.a);
	 pid_t pid;
	 p.pid=getpid();
	 msgsnd(m,&p,sizeof(p),0);
	}
 //msgrcv(m,&p1,sizeof(p),p.pid,0);
 //printf("File Content:\n%s\n",p1.a);

 return 0;
}