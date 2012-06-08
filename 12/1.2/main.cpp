#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using std::cout;
using std::endl;

int main(void)
{
	pid_t pid2, pid3;
	int status;

	pid2 = fork();

	if(pid2 == 0){
	  for(int i = 0; i < 5; ++i){
		cout << "tick" << endl;
		sleep(1);
	  }
		cout << "Program 2 has finished." << endl;
		_exit(-1);
	}

	else {
	  pid3 = fork();

	  if(pid3 == 0) {
		for(int i = 0; i < 8; ++i){
			cout << "tock" << endl;
			sleep(1);
	  	}
			cout << "Program 3 has finished." << endl;
		  _exit(-1);
	  }

	  else{
		waitpid(pid2, &status, 0);
		cout << status << endl;
		
		waitpid(pid3, &status, 0);
		cout << status << endl;

		cout << "Done!" << endl;
		}
	}
	return 0;

}
