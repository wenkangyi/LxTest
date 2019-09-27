//#ifndef _MYQUEUE_H_
//#define _MYQUEUE_H_
#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define QueueMaxSize (65536)

#pragma pack (4)
template<class T> class MyQueue
{
public:
	MyQueue();
	~MyQueue();
	//进队
	void InQueue(T *t);
	//出队，用完后，需要delete T
	T *OutQueue();
	//返回队列长度
	int QueueSize();
	//判断是否为空，为空，即返回1，非空，即返回0
	int IsEmpty();
	//获取队列有效元素数
	int GetEffectiveElements();

private:
	volatile unsigned short _writeIndex;
	volatile unsigned short _readIndex;
	//是否需要加volatile关键字
	T *_queue[QueueMaxSize];
	volatile unsigned char _useFlag[QueueMaxSize];
};


template<class T>
MyQueue<T>::MyQueue()
{
	for (int i = 0; i < QueueMaxSize; i++)
	{
		this->_queue[i] = NULL;
		this->_useFlag[i] = 0;
	}
	this->_writeIndex = 0;
	this->_readIndex = 0;
}


template<class T>
MyQueue<T>::~MyQueue()
{
	if (this->_queue) {
		delete[] this->_queue;
		this->_queue = NULL;
	}
}

template<class T>
void MyQueue<T>::InQueue(T * t)
{
	this->_queue[this->_writeIndex] = t;
	this->_useFlag[this->_writeIndex] = 1;
	this->_writeIndex++;
}

template<class T>
T * MyQueue<T>::OutQueue()
{
	if (this->_useFlag[this->_readIndex] != 1) {
		/*std::cout << "this->_readIndex=" << this->_readIndex << std::endl;
		std::cout << "返回NULL!" << std::endl;*/
		return NULL;
	}

	T *t = this->_queue[this->_readIndex];
	this->_queue[this->_readIndex] = NULL;
	this->_useFlag[this->_readIndex] = 0;
	this->_readIndex++;
	return t;
}

template<class T>
int MyQueue<T>::QueueSize()
{
	return QueueMaxSize;
}

template<class T>
int MyQueue<T>::IsEmpty()
{
	if ((this->_readIndex == this->_writeIndex)
		&& (this->_useFlag[this->_readIndex] == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

template<class T>
int MyQueue<T>::GetEffectiveElements()
{
	int num = 0;
	for (int index = 0; index < QueueMaxSize; index++) {
		if (this->_useFlag[index] == 1) num++;
	}
	return num;
}



//#endif
