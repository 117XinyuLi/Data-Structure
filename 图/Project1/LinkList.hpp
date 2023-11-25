#pragma once
#include<iostream>
//using namespace std;

//������
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
	friend LinkList<T> operator+<>(const LinkList<T>& L1, const LinkList<T>& L2);//����ϲ�L2����L1����
public:
	LinkList() { init(); };
	~LinkList() { removeall(); };
	LinkList(const LinkList<T>& L);//�������캯����curr��Ϊhead
	void Insert(const T& item);//��curr��һ��λ�ý��в���
	void Remove(const T& item);//ɾ��curr��һ��λ�õ�Ԫ��
	void Print();//��ӡ����
	void clear() { removeall(); init(); };//�������
	bool IsEmpty() { return (head->next == NULL); };//�ж������Ƿ�Ϊ��
	bool setPos(int pos); //���õ�ǰλ�ã���1��ʼ��ͷ���λ��Ϊ0
	bool getVal(T& item); //��ȡ��ǰλ�õ�ֵ
	bool CreateListHead();//������������������ͷ�巨��curr��Ϊhead
	bool CreateListTail();//������������������β�巨��curr��Ϊhead
	void Prev();//currָ��ǰһ���ڵ�
	void Next();//currָ���һ���ڵ�
	int getPos();//����curr��λ��
	LinkList& operator=(const LinkList<T>& L);//��ֵ��������أ�curr��Ϊhead

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
		std::cout << "�ڴ����ʧ��" << std::endl;
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
		std::cout << "λ��Ӧ�����ڵ���0" << std::endl;
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
		std::cout << "λ�ó�����Χ��curr��Ϊhead" << std::endl;
		return false;
	}
	return true;
}
template<class T>
bool LinkList<T>::getVal(T& item)
{
	if (curr == head)
	{
		std::cout << "��ǰλ��Ϊhead����ֵ " << std::endl;
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
	std::cout << "������Ҫ�����Ԫ��(����-1Ϊ��ֹ):" << std::endl;
	std::cin >> item;
	while (item != -1)
	{
		Node<T>* s = new Node<T>;
		if (!s)
		{
			std::cout << "�ڴ����ʧ��" << std::endl;
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
	std::cout << "������Ҫ�����Ԫ�� (����-1Ϊ��ֹ):" << std::endl;
	std::cin >> item;
	while (item != -1)
	{
		Node<T>* s = new Node<T>;
		if (!s)
		{
			std::cout << "�ڴ����ʧ��" << std::endl;
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
		std::cout << "��ǰλ��Ϊhead����ǰ��" << std::endl;
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
		std::cout << "��ǰλ��Ϊtail���޺��" << std::endl;
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
