#pragma once
#include<iostream>

//Á½Õ»¹²Ïí¿Õ¼ä
template<class T>
class SeqDoubleStack
{
public:
	SeqDoubleStack(int initSize = 10);
	SeqDoubleStack(const SeqDoubleStack& rhs);
	~SeqDoubleStack();
	bool isEmpty(int i) const;
	void push(const T& x, int i);
	T pop(int i);
	T getTop(int i) const;
	SeqDoubleStack<T>& operator=(const SeqDoubleStack<T>& r);
private:
	T* data;
	int top1;//Õ»1Õ»¶¥Ö¸Õë£¬Õ»¿ÕÎª-1
	int top2;//Õ»2Õ»¶¥Ö¸Õë£¬Õ»¿ÕÎªmaxSize
	int maxSize;
	void doubleSpace();
};

template<class T>
SeqDoubleStack<T>::SeqDoubleStack(int initSize)
{
	data = new T[initSize];
	maxSize = initSize;
	top1 = -1;
	top2 = maxSize;
}
template<class T>
SeqDoubleStack<T>::SeqDoubleStack(const SeqDoubleStack& rhs)
{
	maxSize = rhs.maxSize;
	top1 = rhs.top1;
	top2 = rhs.top2;
	data = new T[maxSize];
	for (int i = 0; i <= top1; i++)
		data[i] = rhs.data[i];
	for (int i = maxSize - 1; i >= top2; i--)
		data[i] = rhs.data[i];
}
template<class T>
SeqDoubleStack<T>::~SeqDoubleStack()
{
	delete[] data;
}
template<class T>
bool SeqDoubleStack<T>::isEmpty(int i) const
{
	if (i == 1)
		return top1 == -1;
	else
		return top2 == maxSize;
}
template<class T>
void SeqDoubleStack<T>::push(const T& x, int i)
{
	if (top1 + 1 == top2)
	{
		doubleSpace();
	}
	if (i == 1)
		data[++top1] = x;
	else
		data[--top2] = x;
}
template<class T>
T SeqDoubleStack<T>::pop(int i)
{
	if (i == 1)
	{
		if (top1==-1)
		{
			std::cout << "Õ»1¿Õ" << std::endl;
			return 0;
		}
		return data[top1--];
	}
	else 
	{
		if (top2 == maxSize)
		{
			std::cout << "Õ»2¿Õ" << std::endl;
			return 0;
		}
		return data[top2++];
	}
		
}
template<class T>
T SeqDoubleStack<T>::getTop(int i) const
{
	if (isEmpty == true)
	{
		std::cout << "Õ»¿Õ" << std::endl;
		return 0;
	}
	if (i == 1)
		return data[top1];
	else
		return data[top2];
}
template<class T>
SeqDoubleStack<T>& SeqDoubleStack<T>::operator=(const SeqDoubleStack<T>& r)
{
	if (this == &r)
		return *this;
	delete[] data;
	maxSize = r.maxSize;
	top1 = r.top1;
	top2 = r.top2;
	data = new T[maxSize];
	for (int i = 0; i <= top1; i++)
		data[i] = r.data[i];
	for (int i = maxSize - 1; i >= top2; i--)
		data[i] = r.data[i];
	return *this;
}
template<class T>
void SeqDoubleStack<T>::doubleSpace()
{
	T* tmp = data;
	data = new T[2 * maxSize];
	for (int i = 0; i <= top1; i++)
		data[i] = tmp[i];
	for (int i = maxSize - 1; i >= top2; i--)
		data[i + maxSize] = tmp[i];
	top2 += maxSize;
	maxSize *= 2;
	delete[] tmp;
}


