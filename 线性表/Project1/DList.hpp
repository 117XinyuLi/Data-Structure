#pragma once
#include<iostream>
//using namespace std;

//双向链表，有头结点
template<class T>
class DLink
{
public:
	DLink(const T& item, DLink* prevval = NULL, DLink* nextval = NULL)
	{
		data = item;
		prev = prevval;
		next = nextval;
	};
	DLink(DLink* prevval = NULL, DLink* nextval = NULL)
	{
		prev = prevval;
		next = nextval;
	};
	T data;
	DLink* prev;
	DLink* next;
};

template<class T>class DList;
template<class T>
DList<T> operator+(const DList<T>& L1, const DList<T>& L2)
{
	DList<T>temp = L1;
	DLink<T>* p = L2.head;
	temp.curr = temp.tail;
	while (p->next != NULL)
	{
		temp.Insert(p->next->data);
		p = p->next;
		temp.curr = temp.curr->next;
	}
	return temp;
}

template<class T>
class DList
{
	friend DList<T> operator+<>(const DList<T>& L1, const DList<T>& L2);//链表合并L2接在L1后面
public:
	DList() { init(); };
	~DList() { removeall(); };
	DList(const DList<T>& L);//拷贝构造函数，curr置为head
	void Insert(const T& item);//对curr下一个位置进行插入
	void Remove(const T& item);//删除curr下一个位置的元素
	void Print();//打印链表
	void clear() { removeall(); init(); };//清空链表
	bool IsEmpty() { return (head->next == NULL); };//判断链表是否为空
	bool setPos(int pos); //设置当前位置，从1开始，头结点位置为0
	bool getVal(T& item); //获取当前位置的值
	bool CreateListHead();//清空链表而后，整表创建，头插法，curr置为head
	bool CreateListTail();//清空链表而后，整表创建，尾插法，curr置为head
	void Prev();//curr指向前一个节点
	void Next();//curr指向后一个节点
	int getPos();//获取当前位置
	DList& operator=(const DList<T>& L);//赋值运算符重载，curr置为head
private:
	DLink<T>* head;
	DLink<T>* tail;
	DLink<T>* curr;
	void init()
	{
		curr = tail = head = new DLink<T>;
	}
	void removeall()
	{
		while (head != NULL)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}
};
template<class T>
DList<T>::DList(const DList<T>& L)
{
	this->init();
	DLink<T>* temp = L.head->next;
	while (temp != NULL)
	{
		this->Insert(temp->data);
		curr = curr->next;
		temp = temp->next;
	}
	curr = head;
}
template<class T>
void DList<T>::Insert(const T& item)
{
	DLink<T>* newlink = new DLink<T>(item, curr, curr->next);
	if (curr->next == NULL)
	{
		tail = newlink;
	}
	else
	{
		curr->next->prev = newlink;
	}
	curr->next = newlink;
}
template<class T>
void DList<T>::Remove(const T& item)
{
	if (curr->next == NULL)
	{
		return;
	}
	DLink<T>* temp = curr->next;
	item = temp->data;
	if (temp->next == NULL)
	{
		tail = curr;
	}
	else
	{
		temp->next->prev = curr;
	}
	curr->next = temp->next;
	delete temp;
}
template<class T>
void DList<T>::Print()
{
	DLink<T>* temp = head->next;
	while (temp != NULL)
	{
		std::cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}
template<class T>
bool DList<T>::setPos(int pos)
{
	if (pos < 0)
	{
		std::cout << "位置应当大于等于0" << std::endl;
		return false;
	}
	curr = head;
	int i = 0;
	for (i = 0; (i < pos && curr->next); i++)
	{
		curr = curr->next;
	}
	if (i != pos)
	{
		curr = head;
		std::cout << "位置超出范围，curr置为head" << std::endl;
		return false;
	}
	return true;
}
template<class T>
bool DList<T>::getVal(T& item)
{
	if (curr == head)
	{
		std::cout << "当前位置为head，无值 " << std::endl;
		return false;
	}
	item = curr->data;
	return true;
}
template<class T>
bool DList<T>::CreateListHead()
{
	T item;
	clear();
	std::cout << "输入数据，以-1结束" << std::endl;
	std::cin >> item;
	while (item != -1)
	{
		DLink<T>* newlink = new DLink<T>(item, head, head->next);
		if (head->next == NULL)
		{
			tail = newlink;
		}
		else
		{
			head->next->prev = newlink;
		}
		head->next = newlink;
		std::cin >> item;
	}
	return true;
}
template<class T>
bool DList<T>::CreateListTail()
{
	T item;
	clear();
	std::cout << "输入数据，以-1结束" << std::endl;
	std::cin >> item;
	while (item != -1)
	{
		DLink<T>* newlink = new DLink<T>(item, tail, NULL);
		tail->next = newlink;
		tail = newlink;
		std::cin >> item;
	}
	return true;
}
template<class T>
void DList<T>::Prev()
{
	if (curr != head)
		curr = curr->prev;
}
template<class T>
void DList<T>::Next()
{
	if (curr != tail)
		curr = curr->next;
}
template<class T>
DList<T>& DList<T>::operator=(const DList<T>& L)
{
	if (this == &L)
	{
		return *this;
	}
	clear();
	DLink<T>* temp = L.head->next;
	while (temp != NULL)
	{
		Insert(temp->data);
		curr = curr->next;
		temp = temp->next;
	}
	curr = head;
	return *this;
}
template<class T>
int DList<T>::getPos()
{
	int i = 0;
	DLink<T>* temp = head;
	while (temp != curr)
	{
		temp = temp->next;
		i++;
	}
	return i;
}

//int main()
//{
//	DList<int> list;
//	DList<int> list1;
//	list.CreateListTail();
//	list1.CreateListTail();
//	list = list + list1;
//	list.Print();
//	
//
//	return 0;
//}