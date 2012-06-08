#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

int main(void)
{
	pid_t pid;
	pid = fork();

	if(pid == 0)
	  cout << "This is the child process, my PID is: " 
			<< getpid() << " and fork() returned: " << pid << endl;

	else
	  cout << "This is the parent process, my PID is:" 
			<< getpid() << " and fork() returned: " << pid << endl;

	return 0;
}
