#pragma once
#include<iostream>
//using namespace std;

//���Ա��˳��洢
template<class T>class Sqlist;
template<class T>
Sqlist<T> operator+(const Sqlist<T>& list1, const Sqlist<T>& list2)
{
	Sqlist<T> temp(list1.length + list2.length);
	for (int i = 0; i < list1.length; i++)
	{
		temp.data[i] = list1.data[i];
	}
	for (int i = 0; i < list2.length; i++)
	{
		temp.data[list1.length + i] = list2.data[i];
	}
	temp.length = list1.length + list2.length;
	return temp;
}
template<class T>
class Sqlist
{
	friend Sqlist<T> operator+<>(const Sqlist<T>& list1, const Sqlist<T>& list2);//�ӷ�����

public:
	Sqlist(int Maxsize);//����
	Sqlist(const Sqlist<T>& list);//��������
	~Sqlist();//����
	bool GetElem(int i, T& e);//��ȡ��i��Ԫ�أ�����e�У�Ԫ���±��1��length
	bool ListInsert(int i, T e);//ʹ��i��Ԫ��Ϊe
	bool ListDelete(int i, T& e);//ɾ����i��Ԫ��,���ظ�e
	bool ListDelete(int i);//ɾ����i��Ԫ��
	Sqlist<T>& operator=(const Sqlist<T>& list)
	{
		//������� ��ֵ�������Ҫ����
		if (data!=NULL)
		{
			delete[]data;
			data = NULL;
		}
		data = new T[list.length];
		Maxsize = list.Maxsize;
		length = list.length;
		for (int i = 0; i < length; i++)
		{
			data[i] = list.data[i];
		}
		return *this;
	}
private:
	T* data;
	int length;
	int Maxsize;
};
template<class T>
Sqlist<T>::Sqlist(int maxsize)
{
	data = new T[maxsize];
	length = 0;
	Maxsize = maxsize;
	for (int i = 0; i < maxsize; i++)
	{
		data[i] = 0;
	}
}
template<class T>
Sqlist<T>::Sqlist(const Sqlist<T>&list)
{
	data = new T[list.Maxsize];
	length = list.length;
	Maxsize = list.Maxsize;
	for (int i = 0; i < Maxsize; i++)
	{
		data[i] = list.data[i];
	}
}
template<class T>
Sqlist<T>::~Sqlist()
{
	delete[]data;
}
template<class T>
bool Sqlist<T>::GetElem(int i, T& e)
{
	if (length == 0 || i<1 || i>length)
	{
		std::cout << "�±�Խ����Ϊ0" << std::endl;
		return false;
	}
	e = data[i - 1];
	return true;
}
template<class T>
bool Sqlist<T>::ListInsert(int i, T e)
{
	if (length == Maxsize || i<1 || i>length + 1)
	{
		std::cout << "�±�Խ��������" << std::endl;
		return false;
	}
	if (i<=length)
	{
		for (int j = length-1; j >=i-1; j--)
		{
			data[j + 1] = data[j];
		}
	}
	data[i - 1] = e;
	length++;
	return true;
}
template<class T>
bool Sqlist<T>::ListDelete(int i, T& e)
{
	if (i<1 || length == 0 || i>length)
	{
		std::cout << "�±�Խ����Ϊ0" << std::endl;
		return false;
	}
	e = data[i - 1];
	for (int j = i-1; j < length; j++)
	{
		data[j] = data[j + 1];
	}
	length--;
	return true;
}
template<class T>
bool Sqlist<T>::ListDelete(int i)
{
	T temp;
	bool output=this->ListDelete(i, temp);
	return output;
}


//int main()
//{
//	Sqlist<int> sql(10);
//	Sqlist<int> sql2(10);
//	for (int i = 1; i <= 10; i++)
//	{
//		sql.ListInsert(i, i);
//		sql2.ListInsert(i, i);
//	}
//
//	sql = sql + sql2;
//	for (int i = 1; i <= 20; i++)
//	{
//		int e;
//		sql.GetElem(i, e);
//		cout << e << endl;
//	}
//	return 0;
//}