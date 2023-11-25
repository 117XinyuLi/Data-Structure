#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstring>

class String
{
	friend std::ostream& operator<<(std::ostream& os, const String& str);
public:
	String(const char* str = NULL); // 普通构造函数
	String(const String& other); // 拷贝构造函数
	~String(); // 析构函数
	int Length() const { return size; };//字符串长度（不包含\0）
	String operator()(int pos, int len); // 取子串,pos范围0~size-1,len>=0,从pos开始取len个字符(包含pos),pos向后len个字符不能到\0,范围错误返回空字符串
	String& operator=(const String& other); // 赋值函数
	String& operator=(const char* str); // 赋值函数
	bool operator==(const String& other) const { return strcmp(m_data,other.m_data)==0; }; // 判断相等
	bool operator!=(const String& other) const { return strcmp(m_data, other.m_data) != 0; }; // 判断不等
	bool operator>(const String& other) const { return strcmp(m_data, other.m_data) > 0; }; // 判断大于
	bool operator<(const String& other) const { return strcmp(m_data, other.m_data) < 0; }; // 判断小于
	bool operator>=(const String& other) const { return strcmp(m_data, other.m_data) >= 0; }; // 判断大于等于
	bool operator<=(const String& other) const { return strcmp(m_data, other.m_data) <= 0; }; // 判断小于等于
	String& operator+=(const String& other); // 连接字符串
	String operator+(const String& other); // 连接字符串
	char operator[](int index) const; // 取下标为index的字符,index从0开始
	bool operator!()const { return m_data[0]=='\0'; };//取反操作符,判断是非为空
	void Clear();//清空字符串
	int Find(const String& pat,int pos) const; // 查找子串,找到返回子串第一个字符的下标,下标从0开始,从pos下标处开始查找(包含pos)，找不到返回-1
	int KMP_Find(const String&pat, int pos);//KMP匹配,找到返回子串第一个字符的下标,下标从0开始,从pos下标处开始查找(包含pos)，找不到返回-1
	void getNext(int* next)const;//next数组
	void getNextVal(int* next)const;//next数组优化
private:
	char* m_data; // 用于保存字符串
	int size;//不包含\0的长度
};

