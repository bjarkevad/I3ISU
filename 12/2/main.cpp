#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <pthread.h>

#include <iostream>

using namespace std;

const unsigned int SHM_KEY(5678);

//POD struct with shared items
struct SharedData {
	pthread_mutex_t m_;
	pthread_cond_t cond_;
	int shared_int;
	bool stopped_;
	bool dataRdy_;
};

void input_func(SharedData* shmem)
{
	while(!shmem->stopped_)
	{
		pthread_mutex_lock(&shmem->m_);

		while(shmem->dataRdy_) {
			cout << "Input waiting for data to be read.." << endl;
			pthread_cond_wait(&shmem->cond_, &shmem->m_);
		}

		cout << "Input Int:" << endl;
		cin >> shmem->shared_int;
		shmem->dataRdy_ = true;
		
		if(shmem->shared_int == 0) {
			cout << "Stop command send.." << endl;	
			shmem->stopped_ = true;
		}

		pthread_cond_signal(&shmem->cond_);
		pthread_mutex_unlock(&shmem->m_);
		
	}
	cout << "Input exiting.." << endl;
	_exit(1);
}

void output_func(SharedData* shmem)
{
	while(!shmem->stopped_)
	{
		pthread_mutex_lock(&shmem->m_);

		while(!shmem->dataRdy_) {
			cout << "Output waiting for data to be written.." << endl;
			pthread_cond_wait(&shmem->cond_, &shmem->m_);
		}

		cout << "Received Int: " << shmem->shared_int << endl;
		shmem->dataRdy_ = false;
		pthread_cond_signal(&shmem->cond_);
		pthread_mutex_unlock(&shmem->m_);
	}
	cout << "Output exiting.." << endl;
	_exit(1);
}

int main()
{
	int shmID = shmget(SHM_KEY, sizeof(SharedData), IPC_CREAT | 0666);
	SharedData* shm = (SharedData*)shmat(shmID, (void*)0, 0);

	shm->shared_int = 1;
	shm->stopped_ = false;
	shm->dataRdy_ = false;

	pthread_mutexattr_t m_att_;
	pthread_mutexattr_init(&m_att_);
	pthread_mutexattr_setpshared(&m_att_, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&shm->m_, &m_att_);

	pthread_condattr_t c_att_;
	pthread_condattr_init(&c_att_);
	pthread_condattr_setpshared(&c_att_, PTHREAD_PROCESS_SHARED);
	pthread_cond_init(&shm->cond_, &c_att_);

	
	pid_t inputPID, outputPID;

	outputPID = fork();

	if(outputPID == 0)
		output_func(shm);

	else {
		inputPID = fork();
	}

	if(inputPID == 0)
		input_func(shm);

	else {
		wait(NULL);
		wait(NULL);
	}

	shmdt(shm);
    shmctl(shmID, IPC_RMID, 0);
	cout << "Main exiting.." << endl;
	return 0;
}
