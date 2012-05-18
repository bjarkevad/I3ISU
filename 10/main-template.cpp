#include    "smartpointer.hpp"
#include		<iostream>

using namespace std;

int main(void) {

	SmartPointer<double>* doublePtr = new SmartPointer<double>(13.37);
	cout << "doublePtr: " << **doublePtr << " Count: " << doublePtr->count() << endl;

	SmartPointer<double> doublePtr2(*doublePtr);
	SmartPointer<double> doublePtr3(42);

	cout << "doublePtr2: " << *doublePtr2 << " Count: " << doublePtr2.count() << endl;
	
	cout << "doublePtr3: " << *doublePtr3 << " Count: " << doublePtr3.count() << endl;

	delete doublePtr;
	cout << "doublePtr2: " << *doublePtr2 << " Count: " << doublePtr2.count() << endl;
	doublePtr2 = doublePtr3;
	cout << "doublePtr2: " << *doublePtr2 << " Count: " << doublePtr2.count() << endl;
	cout << "deleted doublePtr count: " << doublePtr->count() << endl;


}
