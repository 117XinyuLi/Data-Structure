#pragma once
#include<iostream>
//using namespace std;

//˫��������ͷ���
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
	friend DList<T> operator+<>(const DList<T>& L1, const DList<T>& L2);//����ϲ�L2����L1����
public:
	DList() { init(); };
	~DList() { removeall(); };
	DList(const DList<T>& L);//�������캯����curr��Ϊhead
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
	int getPos();//��ȡ��ǰλ��
	DList& operator=(const DList<T>& L);//��ֵ��������أ�curr��Ϊhead
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
bool DList<T>::getVal(T& item)
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
bool DList<T>::CreateListHead()
{
	T item;
	clear();
	std::cout << "�������ݣ���-1����" << std::endl;
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
	std::cout << "�������ݣ���-1����" << std::endl;
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