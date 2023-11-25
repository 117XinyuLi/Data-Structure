#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstring>

class String
{
	friend std::ostream& operator<<(std::ostream& os, const String& str);
public:
	String(const char* str = NULL); // ��ͨ���캯��
	String(const String& other); // �������캯��
	~String(); // ��������
	int Length() const { return size; };//�ַ������ȣ�������\0��
	String operator()(int pos, int len); // ȡ�Ӵ�,pos��Χ0~size-1,len>=0,��pos��ʼȡlen���ַ�(����pos),pos���len���ַ����ܵ�\0,��Χ���󷵻ؿ��ַ���
	String& operator=(const String& other); // ��ֵ����
	String& operator=(const char* str); // ��ֵ����
	bool operator==(const String& other) const { return strcmp(m_data,other.m_data)==0; }; // �ж����
	bool operator!=(const String& other) const { return strcmp(m_data, other.m_data) != 0; }; // �жϲ���
	bool operator>(const String& other) const { return strcmp(m_data, other.m_data) > 0; }; // �жϴ���
	bool operator<(const String& other) const { return strcmp(m_data, other.m_data) < 0; }; // �ж�С��
	bool operator>=(const String& other) const { return strcmp(m_data, other.m_data) >= 0; }; // �жϴ��ڵ���
	bool operator<=(const String& other) const { return strcmp(m_data, other.m_data) <= 0; }; // �ж�С�ڵ���
	String& operator+=(const String& other); // �����ַ���
	String operator+(const String& other); // �����ַ���
	char operator[](int index) const; // ȡ�±�Ϊindex���ַ�,index��0��ʼ
	bool operator!()const { return m_data[0]=='\0'; };//ȡ��������,�ж��Ƿ�Ϊ��
	void Clear();//����ַ���
	int Find(const String& pat,int pos) const; // �����Ӵ�,�ҵ������Ӵ���һ���ַ����±�,�±��0��ʼ,��pos�±괦��ʼ����(����pos)���Ҳ�������-1
	int KMP_Find(const String&pat, int pos);//KMPƥ��,�ҵ������Ӵ���һ���ַ����±�,�±��0��ʼ,��pos�±괦��ʼ����(����pos)���Ҳ�������-1
	void getNext(int* next)const;//next����
	void getNextVal(int* next)const;//next�����Ż�
private:
	char* m_data; // ���ڱ����ַ���
	int size;//������\0�ĳ���
};

