#include <osapi/Semaphore.hpp>

namespace osapi {
	const unsigned int MAX_COUNT=1024;

	Semaphore::Semaphore(unsigned int initCount) {
			if(sem_init(&sem_, initCount, MAX_COUNT) != 0)
				throw SemaphoreError();
		}

	void Semaphore::wait() {
		if(sem_wait(&sem_) != 0)
			throw SemaphoreError();
	}

	void Semaphore::signal() {
		if(sem_post(&sem_) != 0)
			throw SemaphoreError();
	}

	Semaphore::~Semaphore() {
		sem_destroy(&sem_);
	}
}
