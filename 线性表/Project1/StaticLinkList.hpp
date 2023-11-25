#pragma once
#include<iostream>
//using namespace std;

//��̬����0λ��Ϊ������ͷ��㣬MAX-1(�������)λ��Ϊ������ͷ���
#define MAXSIZE 100
template<class T>
class Component
{
public:
	T data;
	int cur;//�α�
};
template<class T>
class StaticLinkList
{
public:
	StaticLinkList() { init(); };
	~StaticLinkList() { removeall(); };
	void Insert(const T& item);//��curr��һ��λ�ý��в���
	void Remove(const T& item);//ɾ��curr��һ��λ�õ�Ԫ��
	void Print();//��ӡ����
	void clear() { removeall(); init(); };//�������
	bool IsEmpty() { return (space[MAXSIZE-1] == 0); };//�ж������Ƿ�Ϊ��
	bool IsFull() { return (space[0] == 0); };//�ж������Ƿ�����
	bool setPos(int pos); //���õ�ǰλ�ã���1��ʼ������ͷ���λ��Ϊ0
	bool getVal(T& item); //��ȡ��ǰλ�õ�ֵ
	bool CreateListHead();//������������������ͷ�巨��curr��Ϊhead
	bool CreateListTail();//������������������β�巨��curr��Ϊhead
	int getPos();//��ȡ��ǰλ��
	int Length();//����������
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
		std::cout << "�ռ��������޷�����" << std::endl;
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
		std::cout << "�±�Խ��" << std::endl;
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
		std::cout << "�±�Խ��" << std::endl;
		return false;
	}
	return true;
}
template<class T>
bool StaticLinkList<T>::getVal(T& item)
{
	if (curr ==head)
	{
		std::cout << "ͷ�����ֵ" << std::endl;
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
	std::cout << "�����������ȣ�";
	std::cin >> n;
	if (n > MAXSIZE - 2)
	{
		std::cout << "���ݹ���" << std::endl;
		return false;
	}
	for (int i = 0; i < n; i++)
	{
		T item;
		std::cout << "�������" << i + 1 << "��Ԫ�أ�";
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
	std::cout << "�����������ȣ�";
	std::cin >> n;
	if (n > MAXSIZE - 2)
	{
		std::cout << "���ݹ���" << std::endl;
		return false;
	}
	for (int i = 0; i < n; i++)
	{
		T item;
		std::cout << "�������" << i + 1 << "��Ԫ�أ�";
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