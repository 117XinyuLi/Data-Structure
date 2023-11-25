#pragma once
#include<iostream>

//ѭ������
template<class T>
class SqQueue
{
public:
	SqQueue(int initSize = 10);
	SqQueue(const SqQueue& rhs);
	~SqQueue();
	bool isEmpty() const { return front == rear; };
	bool isFull()const { return (rear + 1) % maxSize == front; };
	void Clear() { front = rear = 0; };
	int Length() const { return (rear - front + maxSize) % maxSize; };
	void enQueue(const T& x);
	T deQueue();
	T getHead() const;
	SqQueue<T>& operator=(const SqQueue<T>& r);
private:
	T* data;
	int front;//��ͷָ�룬ָ���ͷ
	int rear;//��βָ�룬ָ���β��һ��
	int maxSize;//�����С�����д�СΪmaxSize-1
	void doubleSpace();
};

template<class T>
SqQueue<T>::SqQueue(int initSize)
{
	maxSize = initSize+1;
	data = new T[initSize];
	front = rear = 0;
}
template<class T>
SqQueue<T>::SqQueue(const SqQueue& rhs)
{
	maxSize = rhs.maxSize;
	front = rhs.front;
	rear = rhs.rear;
	data = new T[maxSize];
	for (int i = 0; i < maxSize; i++)
		data[i] = rhs.data[i];
}
template<class T>
SqQueue<T>::~SqQueue()
{
	delete[] data;
}
template<class T>
void SqQueue<T>::enQueue(const T& x)
{
	if (isFull())
		doubleSpace();
	data[rear] = x;
	rear = (rear + 1) % maxSize;
}
template<class T>
T SqQueue<T>::deQueue()
{
	if (isEmpty())
	{
		std::cout << "����Ϊ��" << std::endl;
		return 0;
	}
	T e = data[front];
	front = (front + 1) % maxSize;
	return e;
}
template<class T>
T SqQueue<T>::getHead() const
{
	if (isEmpty())
	{
		std::cout << "����Ϊ��" << std::endl;
		return 0;
	}
	return data[front];
}
template<class T>
SqQueue<T>& SqQueue<T>::operator=(const SqQueue<T>& r)
{
	if (this == &r)
		return *this;
	delete[] data;
	maxSize = r.maxSize;
	front = r.front;
	rear = r.rear;
	data = new T[maxSize];
	for (int i = 0; i <maxSize; i++)
		data[i] = r.data[i];
	return *this;
}
template<class T>
void SqQueue<T>::doubleSpace()
{
	T* tmp = data;
	data = new T[2 * maxSize];
	for (int i = 0; i < maxSize-1; i++)
		data[i] = tmp[(front + i) % maxSize];
	front = 0;
	rear = maxSize - 1;
	maxSize *= 2;
	delete[] tmp;
}
