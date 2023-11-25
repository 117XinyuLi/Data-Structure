#pragma once
#include<iostream>
//using namespace std;

//静态链表，0位置为空闲区头结点，MAX-1(数组最后)位置为数据区头结点
#define MAXSIZE 100
template<class T>
class Component
{
public:
	T data;
	int cur;//游标
};
template<class T>
class StaticLinkList
{
public:
	StaticLinkList() { init(); };
	~StaticLinkList() { removeall(); };
	void Insert(const T& item);//对curr下一个位置进行插入
	void Remove(const T& item);//删除curr下一个位置的元素
	void Print();//打印链表
	void clear() { removeall(); init(); };//清空链表
	bool IsEmpty() { return (space[MAXSIZE-1] == 0); };//判断链表是否为空
	bool IsFull() { return (space[0] == 0); };//判断链表是非已满
	bool setPos(int pos); //设置当前位置，从1开始，数据头结点位置为0
	bool getVal(T& item); //获取当前位置的值
	bool CreateListHead();//清空链表而后，整表创建，头插法，curr置为head
	bool CreateListTail();//清空链表而后，整表创建，尾插法，curr置为head
	int getPos();//获取当前位置
	int Length();//返回链表长度
private:
	Component<T> space[MAXSIZE];
	int head;
	int tail;
	int curr;
	void init()
	{
		curr = tail = head = MAXSIZE-1;
		for (int i = 0; i < MAXSIZE - 2; i++)
		{
			space[i].cur = i + 1;
		}
		space[MAXSIZE - 2].cur = 0;
		space[MAXSIZE - 1].cur = 0;
	}
	void removeall()
	{
		for (int i = 0; i < MAXSIZE; i++)
		{
			space[i].data = 0;
			space[i].cur = 0;
		}
	}
	int Malloc()
	{
		int i = space[0].cur;
		if (space[0].cur)
		{
			space[0].cur = space[i].cur;
		}
		return i;
	}
	void Free(int k)
	{ 
		space[k].data = 0;
		space[k].cur = space[0].cur;
		space[0].cur = k;
	}
};
template<class T>
void StaticLinkList<T>::Insert(const T& item)
{
	int i = Malloc();
	if (i)
	{
		space[i].data = item;
		space[i].cur = space[curr].cur;
		space[curr].cur = i;
		if (curr == tail)
		{
			tail = i;
		}
	}
	else
	{
		std::cout << "空间已满，无法插入" << std::endl;
		return;
	}
}
template<class T>
void StaticLinkList<T>::Remove(const T& item)
{
	int i = space[curr].cur;
	if (i)
	{
		space[curr].cur = space[i].cur;
		item = space[i].data;
		Free(i);
		if (i == tail)
		{
			tail = curr;
		}
	}
}
template<class T>
void StaticLinkList<T>::Print()
{
	int i = space[head].cur;
	while (i)
	{
		std::cout << space[i].data << " ";
		i = space[i].cur;
	}
	std::cout << std::endl;
}
template<class T>
bool StaticLinkList<T>::setPos(int pos)
{
	if (pos < 0 || pos > MAXSIZE-2)
	{
		std::cout << "下标越界" << std::endl;
		return false;
	}
	curr = head;
	int i = 0;
	for (i = 0; (i < pos&&space[curr].cur); i++)
	{
		curr = space[curr].cur;
	}
	if (pos!=i)
	{
		std::cout << "下标越界" << std::endl;
		return false;
	}
	return true;
}
template<class T>
bool StaticLinkList<T>::getVal(T& item)
{
	if (curr ==head)
	{
		std::cout << "头结点无值" << std::endl;
		return false;
	}
	item = space[curr].data;
	return true;
}
template<class T>
bool StaticLinkList<T>::CreateListHead()
{
	clear();
	int n;
	std::cout << "请输入链表长度：";
	std::cin >> n;
	if (n > MAXSIZE - 2)
	{
		std::cout << "数据过多" << std::endl;
		return false;
	}
	for (int i = 0; i < n; i++)
	{
		T item;
		std::cout << "请输入第" << i + 1 << "个元素：";
		std::cin >> item;
		curr = head;
		Insert(item);
	}
	curr = head;
	return true;
}
template<class T>
bool StaticLinkList<T>::CreateListTail()
{
	clear();
	int n;
	std::cout << "请输入链表长度：";
	std::cin >> n;
	if (n > MAXSIZE - 2)
	{
		std::cout << "数据过多" << std::endl;
		return false;
	}
	for (int i = 0; i < n; i++)
	{
		T item;
		std::cout << "请输入第" << i + 1 << "个元素：";
		std::cin >> item;
		Insert(item);
		curr = tail;
	}
	return true;
}
template<class T>
int StaticLinkList<T>::Length()
{
	int i = space[head].cur;
	int len = 0;
	while (i)
	{
		len++;
		i = space[i].cur;
	}
	return len;
}
template<class T>
int StaticLinkList<T>::getPos()
{
	int i = head;
	int pos = 0;
	while (i!=curr)
	{
		pos++;
		i = space[i].cur;
	}
	return pos;
}

//int main()
//{
//	StaticLinkList<int>sll;
//	sll.CreateListTail();
//	sll.setPos(1);
//	std::cout << sll.getPos() << std::endl;
//	
//	return 0;
//}