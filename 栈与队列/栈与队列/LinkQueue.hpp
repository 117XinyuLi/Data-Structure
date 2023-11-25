#pragma once
#include<iostream>

//链队列
template<class T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node(const T& x, Node<T>* n = NULL)
	{
		data = x;
		next = n;
	}
	Node() :next(NULL) {}
	~Node() {}
};

template<class T>
class LinkQueue
{
public:
	LinkQueue();
	LinkQueue(const LinkQueue& rhs);
	~LinkQueue() { removeall(); };
	bool isEmpty() const;
	void Clear() { removeall(); front = rear = NULL; };
	int Length();
	void enQueue(const T& x);
	T deQueue();
	T getHead() const;
	LinkQueue<T>& operator=(const LinkQueue<T>& r);
private:
	Node<T>* front;
	Node<T>* rear;
	void removeall()
	{
		Node<T>* p = front;
		while (p != NULL)
		{
			Node<T>* tmp = p;
			p = p->next;
			delete tmp;
		}
	}
};

template<class T>
LinkQueue<T>::LinkQueue()
{
	front = rear = NULL;
}
template<class T>
LinkQueue<T>::LinkQueue(const LinkQueue& rhs)
{
	Node<T>* p = rhs.front;
	front = rear = NULL;
	while (p != NULL)
	{
		enQueue(p->data);
		p = p->next;
	}
}
template<class T>
bool LinkQueue<T>::isEmpty() const
{
	return front == NULL;
}
template<class T>
void LinkQueue<T>::enQueue(const T& x)
{
	if (isEmpty())
	{
		front = rear = new Node<T>(x);
	}
	else
	{
		rear->next = new Node<T>(x);
		rear = rear->next;
	}
}
template<class T>
T LinkQueue<T>::deQueue()
{
	if (isEmpty())
	{
		std::cout << "队列为空" << std::endl;
		return 0;
	}
	Node<T>* tmp = front;
	T value = front->data;
	front = front->next;
	if (front == NULL)
	{
		rear = NULL;
	}
	delete tmp;
	return value;
}
template<class T>
T LinkQueue<T>::getHead() const
{
	if (isEmpty())
	{
		std::cout << "队列为空" << std::endl;
		return 0;
	}
	return front->data;
}
template<class T>
LinkQueue<T>& LinkQueue<T>::operator=(const LinkQueue<T>& r)
{
	if (this == &r)
		return *this;
	removeall();
	Node<T>* p = r.front;
	front = rear = NULL;
	while (p != NULL)
	{
		enQueue(p->data);
		p = p->next;
	}
	return *this;
}
template<class T>
int LinkQueue<T>::Length()
{
	int count = 0;
	Node<T>* p = front;
	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}

