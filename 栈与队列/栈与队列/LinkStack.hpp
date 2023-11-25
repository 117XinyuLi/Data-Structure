#pragma once
#include<iostream>

//Á´Õ»
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
class LinkStack
{
public:
	LinkStack();
	LinkStack(const LinkStack& rhs);
	~LinkStack() { removeall(); };
	bool isEmpty() const;
	void push(const T& x);
	void clear() { removeall(); top = NULL; };
	T pop();
	T getTop() const;
	int Length();
	LinkStack<T>& operator=(const LinkStack<T>& r);
private:

	Node<T>* top;
	void removeall()
	{
		Node<T>* p = top;
		while (p != NULL)
		{
			Node<T>* tmp = p;
			p = p->next;
			delete tmp;
		}
	}
};

template<class T>
LinkStack<T>::LinkStack()
{
	top = NULL;
}
template<class T>
LinkStack<T>::LinkStack(const LinkStack& rhs)
{
	Node<T>* p = rhs.top;
	top = NULL;
	while (p != NULL)
	{
		push(p->data);
		p = p->next;
	}
}
template<class T>
bool LinkStack<T>::isEmpty() const
{
	return top == NULL;
}
template<class T>
void LinkStack<T>::push(const T& x)
{
	Node<T>* tmp = new Node<T>(x, top);
	top = tmp;
}
template<class T>
T LinkStack<T>::pop()
{
	if (top == NULL)
	{
		std::cout << "Õ»Îª¿Õ" << std::endl;
		return 0;
	}
	Node<T>* tmp = top;
	top = top->next;
	T x = tmp->data;
	delete tmp;
	return x;
}
template<class T>
T LinkStack<T>::getTop() const
{
	if (isEmpty == true)
	{
		std::cout << "Õ»¿Õ" << std::endl;
		return 0;
	}
	return top->data;
}
template<class T>
LinkStack<T>& LinkStack<T>::operator=(const LinkStack<T>& r)
{
	if (this == &r)
		return *this;
	removeall();
	top = NULL;
	Node<T>* p = r.top;
	while (p != NULL)
	{
		push(p->data);
		p = p->next;
	}

	return *this;
}
template<class T>
int LinkStack<T>::Length()
{
	Node<T>* p = top;
	int i = 0;
	while (p!=NULL)
	{
		p = p->next;
		i++;
	}
	return i;
}

