#include "MyQueue.h"
#include <unistd.h>


//template<class T> 
//MyQueue<T>::MyQueue()
//{
//	for (int i = 0; i < QueueMaxSize; i++)
//	{
//		this->_queue[i] = NULL;
//		this->_useFlag[i] = 0;
//	}
//	this->_writeIndex = 0;
//	this->_readIndex = 0;
//}
//
//
//template<class T> 
//MyQueue<T>::~MyQueue()
//{
//	if (this->_queue) {
//		delete[] this->_queue;
//		this->_queue = NULL;
//	}
//}
//
//template<class T> 
//void MyQueue<T>::InQueue(T * t)
//{
//	this->_queue[this->_writeIndex] = t;
//	this->_useFlag[this->_writeIndex] = 1;
//	this->_writeIndex++;
//}
//
//template<class T> 
//T * MyQueue<T>::OutQueue()
//{
//	if (this->_useFlag[this->_readIndex] != 1) {
//		std::cout << "this->_readIndex=" << this->_readIndex << std::endl;
//		std::cout << "·µ»ØNULL!" << std::endl;
//		return NULL;
//	}
//
//	T *t = this->_queue[this->_readIndex];
//	this->_queue[this->_readIndex] = NULL;
//	this->_useFlag[this->_readIndex] = 0;
//	this->_readIndex++;
//	return t;
//}
//
//template<class T> 
//int MyQueue<T>::QueueSize()
//{
//	return QueueMaxSize;
//}
//
//template<class T> 
//int MyQueue<T>::IsEmpty()
//{
//	if ((this->_readIndex == this->_writeIndex)
//		&& (this->_useFlag[this->_readIndex] == 0)) {
//		return 1;
//	}
//	else {
//		return 0;
//	}
//}
//
//template<class T> 
//int MyQueue<T>::GetEffectiveElements()
//{
//	int num = 0;
//	for (int index = 0; index < QueueMaxSize; index++) {
//		if (this->_useFlag[index] == 1) num++;
//	}
//	return num;
//}

/*class  A
{
public:
	A();
	~A();

private:

};


int main() {
	MyQueue<A> *mq = new MyQueue<A>();
	return 0;
}*/
