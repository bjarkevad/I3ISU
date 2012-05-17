#include <iostream>
#include <pthread.h>

using namespace std;

class ScopedLocker
{
public:
	ScopedLocker(pthread_mutex_t* mutex): myMutex(mutex) {
	pthread_mutex_lock(myMutex);
};

	~ScopedLocker() {pthread_mutex_unlock(myMutex);};
private:
	pthread_mutex_t * myMutex;
};
