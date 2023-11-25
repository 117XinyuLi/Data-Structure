#pragma once
#include<iostream>
//using namespace std;

//单链表
template<class T>
class Node
{
public:
	Node(const T& item, Node* nextval = NULL)
	{
		data = item;
		next = nextval;
	};
	Node(Node* nextval = NULL)
	{
		next = nextval;
	};
	T data;
	Node* next;
};

template<class T>class LinkList;
template<class T>
LinkList<T> operator+(const LinkList<T>& L1, const LinkList<T>& L2)
{
	LinkList<T>temp = L1;
	Node<T>* p = L2.head;
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
class LinkList
{
	friend LinkList<T> operator+<>(const LinkList<T>& L1, const LinkList<T>& L2);//链表合并L2接在L1后面
public:
	LinkList() { init(); };
	~LinkList() { removeall(); };
	LinkList(const LinkList<T>& L);//拷贝构造函数，curr置为head
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
	int getPos();//返回curr的位置
	LinkList& operator=(const LinkList<T>& L);//赋值运算符重载，curr置为head

	Node<T>* head;
	Node<T>* tail;
	Node<T>* curr;
	void init()
	{
		curr = tail = head = new Node<T>;
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
void LinkList<T>::Insert(const T& item)
{
	Node<T>* s = new Node<T>;
	if (!s)
	{
		std::cout << "内存分配失败" << std::endl;
		return;
	}
	s->data = item;
	s->next = curr->next;
	curr->next = s;
	if (tail == curr)
		tail = s;
}
template<class T>
void LinkList<T>::Remove(const T& item)
{
	if (curr->next == NULL)
	{
		return false;
	}
	Node<T>* p = curr->next;
	curr->next = p->next;
	item = p->data;
	if (tail == p)
	{
		tail = curr;
	}
	delete p;
	return true;
}
template<class T>
void LinkList<T>::Print()
{
	Node<T>* temp = head->next;
	while (temp != NULL)
	{
		std::cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}
template<class T>
bool LinkList<T>::setPos(int pos)
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
bool LinkList<T>::getVal(T& item)
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
bool LinkList<T>::CreateListHead()
{
	this->clear();
	T item;
	std::cout << "请输入要插入的元素(输入-1为终止):" << std::endl;
	std::cin >> item;
	while (item != -1)
	{
		Node<T>* s = new Node<T>;
		if (!s)
		{
			std::cout << "内存分配失败" << std::endl;
			return false;
		}
		s->data = item;
		s->next = head->next;
		head->next = s;
		if (tail == head)
		{
			tail = s;
		}
		std::cin >> item;
	}
	curr = head;
	return true;
}
template<class T>
bool LinkList<T>::CreateListTail()
{
	this->clear();
	T item;
	std::cout << "请输入要插入的元素 (输入-1为终止):" << std::endl;
	std::cin >> item;
	while (item != -1)
	{
		Node<T>* s = new Node<T>;
		if (!s)
		{
			std::cout << "内存分配失败" << std::endl;
			return false;
		}
		s->data = item;
		tail->next = s;
		tail = s;
		std::cin >> item;
	}
	curr = head;
	return true;
}
template<class T>
void LinkList<T>::Prev()
{
	if (curr == head)
	{
		std::cout << "当前位置为head，无前驱" << std::endl;
		return;
	}
	Node<T>* temp = head;
	while (temp->next != curr)
	{
		temp = temp->next;
	}
	curr = temp;
}
template<class T>
void LinkList<T>::Next()
{
	if (curr == tail)
	{
		std::cout << "当前位置为tail，无后继" << std::endl;
		return;
	}
	curr = curr->next;
}
template<class T>
LinkList<T>::LinkList(const LinkList<T>& L)
{
	this->init();
	Node<T>* temp = L.head->next;
	while (temp != NULL)
	{
		this->Insert(temp->data);
		curr = curr->next;
		temp = temp->next;
	}
	curr = head;
}
template<class T>
LinkList<T>& LinkList<T>::operator=(const LinkList<T>& L)
{
	if (this == &L)
	{
		return *this;
	}
	this->clear();
	Node<T>* temp = L.head->next;
	while (temp != NULL)
	{
		this->Insert(temp->data);
		curr = curr->next;
		temp = temp->next;
	}
	curr = head;
	return *this;
}
template<class T>
int LinkList<T>::getPos()
{
	int i = 0;
	Node<T>* temp = head;
	while (temp != curr)
	{
		temp = temp->next;
		i++;
	}
	return i;
}

//int main()
//{
//	LinkList<int> list;
//	LinkList<int> list1;
//	list.CreateListTail();
//	list1.CreateListTail();
//	list = list + list1;
//	list.Print();
//	
//	
//	return 0;
//}
