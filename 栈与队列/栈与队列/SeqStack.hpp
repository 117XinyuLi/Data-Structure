#pragma once
#include<iostream>
//À≥–Ú’ª
template<class T>
class SeqStack
{
public:
	SeqStack(int initSize = 10);
	SeqStack(const SeqStack& rhs);
	~SeqStack();
	bool isEmpty() const;
	void push(const T& x);
	T pop();
	T getTop() const;
	SeqStack<T>& operator=(const SeqStack<T>& r);
private:
	T* data;
	int top;//’ª∂•÷∏’Î£¨’ªø’Œ™-1
	int maxSize;
	void doubleSpace();
};

template<class T>
SeqStack<T>::SeqStack(int initSize)
{
	data = new T[initSize];
	maxSize = initSize;
	top = -1;
}
template<class T>
SeqStack<T>::SeqStack(const SeqStack& rhs)
{
	maxSize = rhs.maxSize;
	top = rhs.top;
	data = new T[maxSize];
	for (int i = 0; i <= top; i++)
		data[i] = rhs.data[i];
}
template<class T>
SeqStack<T>::~SeqStack()
{
	delete[] data;
}
template<class T>
bool SeqStack<T>::isEmpty() const
{
	return top == -1;
}
template<class T>
void SeqStack<T>::push(const T& x)
{
	if (top == maxSize - 1)
	{
		doubleSpace();
	}
	data[++top] = x;
}
template<class T>
T SeqStack<T>::pop()
{
	if (top == -1)
	{
		std::cout << "’ªø’" << std::endl;
		return 0;
	}
	return data[top--];
}
template<class T>
T SeqStack<T>::getTop() const
{
	if (isEmpty == true)
	{
		std::cout << "’ªø’" << std::endl;
		return 0;
	}
	return data[top];
}
template<class T>
void SeqStack<T>::doubleSpace()
{
	T* tmp = data;
	maxSize *= 2;
	data = new T[maxSize];
	for (int i = 0; i <= top; i++)
		data[i] = tmp[i];
	delete[] tmp;
}
template<class T>
SeqStack<T>& SeqStack<T>::operator=(const SeqStack<T>& r)
{
	if (this == &r)
		return *this;
	delete[] data;
	maxSize = r.maxSize;
	top = r.top;
	data = new T[maxSize];
	for (int i = 0; i <= top; i++)
		data[i] = r.data[i];
	return *this;
}
