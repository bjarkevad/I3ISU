template<typename T> 
class SmartPointer {
	public:
		SmartPointer(T t_);
		SmartPointer(const SmartPointer& other);
		~SmartPointer();
		void operator=(const SmartPointer& other);
		T* operator->();
		T& operator*();
		T* get();
		unsigned int count();
	private:
		T* t;
		unsigned int* counter_;
};

template<typename T> SmartPointer<T>::SmartPointer(T t_) {

	counter_ = new unsigned int(1);
	t = new T(t_);
}

template<typename T> SmartPointer<T>::SmartPointer(const SmartPointer& other) {

	counter_ = other.counter_;
	t = other.t;

	(*counter_)++;
}

template<typename T> SmartPointer<T>::~SmartPointer() {

	if((*counter_) == 1) {
		delete t;
		delete counter_;
	}
	else
		(*counter_)--;
}

template<typename T> void SmartPointer<T>::operator=(const SmartPointer& other) {
	
	if(this!= &other) {
		(*counter_)--;
			if((*counter_) == 0)
				delete str_;
	}

	counter_ = other.counter_;
	t = other.t;

	(*counter_)++;
}
	
template<typename T> T* SmartPointer<T>::operator->() {

	return t;
}

template<typename T> T& SmartPointer<T>::operator*() {

	return *t;
}

template<typename T> T* SmartPointer<T>::get() {

	return t;
}

template<typename T> unsigned int SmartPointer<T>::count() {

	return (*counter_);
}

