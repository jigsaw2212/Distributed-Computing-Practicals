#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main()
{
	int status,pid;
	int pipes[2];

	char name[100];
	cout<<"Enter message to send: ";
		gets(name);

	char str[100];

	status = pipe(pipes);

	if(status== -1)
	{
		cout<<"Error";
		return 0;
	}	

	pid = fork();

	if(pid == -1)
	{
		cout<<"Error";
		return 0;
	}

	//1 - write descriptor
	//0 - read descriptor

	else if(pid== 0)
	{

		close(pipes[0]);

		cout<<"\nSending message...\n";

		

		write(pipes[1], name, 80 );

		close(pipes[1]);
	}
	else
	{
		close(pipes[1]);

		read(pipes[0], str, 100);
		cout<<"\nRecieved\n";
		cout<<str<<endl;

		close(pipes[0]);

	}


	return 0;
}

