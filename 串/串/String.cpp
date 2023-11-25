#include"String.h"
String::String(const char* str)
{
	if (str == NULL)
	{
		size = 0;
		m_data = new char[size + 1];
		m_data[0] = '\0';
	}
	else
	{
		int length = strlen(str);
		size = length;
		m_data = new char[size + 1];
		strcpy(m_data, str);
	}
}
String::String(const String& other)
{
	int length = strlen(other.m_data);
	size = length;
	m_data = new char[size + 1];
	strcpy(m_data, other.m_data);
}
String::~String()
{
	delete[] m_data;
	size = 0;
}
String& String::operator=(const String& other)
{
	if (this == &other)
		return *this;
	delete[] m_data;
	int length = strlen(other.m_data);
	size = length;
	m_data = new char[size + 1];
	strcpy(m_data, other.m_data);
	return *this;
}
String String::operator()(int pos, int len)
{
	String temp;
	if (pos < 0 || len < 0 || pos + len > size)
	{
		std::cout << "范围错误" << std::endl;
		return temp;
	}
	else
	{
		delete[]temp.m_data;
		temp.size = len;
		temp.m_data = new char[temp.size + 1];
		int i = 0;
		for (i = 0; i < len; i++)
		{
			temp.m_data[i] = m_data[i + pos];
		}
		temp.m_data[i] = '\0';
		return temp;
	}
}
std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.m_data;
	return os;
}
String& String::operator+=(const String& other)
{
	int length = strlen(other.m_data);
	char* temp = new char[size + length + 1];
	strcpy(temp, m_data);
	strcat(temp, other.m_data);
	delete[] m_data;
	size = size + length;
	m_data = new char[size + 1];
	strcpy(m_data, temp);
	delete[] temp;
	return *this;
}
String String::operator+(const String& other)
{
	String temp;
	int length = strlen(other.m_data);
	temp.size = size + length;
	delete[]temp.m_data;
	temp.m_data = new char[temp.size + 1];
	strcpy(temp.m_data, m_data);
	strcat(temp.m_data, other.m_data);
	return temp;
}
char String::operator[](int index) const
{
	if (index < 0 || index > size - 1)
	{
		std::cout << "范围错误" << std::endl;
		return m_data[0];
	}
	else
		return m_data[index];
}
String& String::operator=(const char* str)
{
	delete[]m_data;
	if (str == NULL)
	{
		size = 0;
		m_data = new char[size + 1];
		m_data[0] = '\0';
	}
	else
	{
		int length = strlen(str);
		size = length;
		m_data = new char[size + 1];
		strcpy(m_data, str);
	}
	return *this;
}
void String::Clear()
{
	delete[] m_data;
	size = 0;
	m_data = new char[size + 1];
	m_data[0] = '\0';
}
int String::Find(const String& pat, int pos) const
{
	int i = pos, j = 0;
	if (size == 0 || pat.size == 0 || pos<0 || pos>size - 1)
	{
		std::cout << "有字符串为空或pos有误" << std::endl;
		return -1;
	}
	while (i <= size - 1 && j <= pat.size - 1)
	{
		if (m_data[i] == pat.m_data[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == pat.size)
		return i - pat.size;
	return -1;

}
int String::KMP_Find(const String& pat, int pos)//pos从0开始
{
	int i = pos, j = 0, ret;
	if (size == 0 || pat.size == 0 || pos<0 || pos>size - 1)
	{
		std::cout << "有字符串为空或pos有误" << std::endl;
		return -1;
	}
	int* next = new int[pat.size];
	pat.getNextVal(next);
	while (i <= size - 1 && j <= pat.size - 1)
	{
		if (j == -1 || m_data[i] == pat.m_data[j])
		{
			i++; j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j == pat.size)
	{
		ret = i - pat.size;
	}
	else
	{
		ret = -1;
	}
	delete[]next;
	return ret;
}
void String::getNext(int* next)const
{
	//next[i]表示前i个(next[0]~next[i-1])元素的最长公共前后缀长度
	int j = 0, k = -1;
	next[0] = -1;
	while (j < size - 1)
	{
		if (k == -1 || m_data[j] == m_data[k])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
	
}
void String::getNextVal(int* nextval)const
{
	int j = 0, k = -1;
	nextval[0] = -1;
	while (j < size - 1)
	{
		if (k == -1 || m_data[j] == m_data[k])
		{
			j++;
			k++;
			nextval[j] = k;
			if (m_data[j] != m_data[k])
				nextval[j] = k;
			else
				nextval[j] = nextval[k];
		}
		else
		{
			k = nextval[k];
		}
	}
}

//int main()
//{
//	String str1 = "abacababdeadcde";
//	String str2 = "abab";
//	int i[100] = { 0 };
//	str1.getNext(i);
//	for (int j = 0; j < str1.Length(); j++)
//	{
//		std::cout << i[j] << " ";
//	}
//	std::cout <<str1<<" "<<str2<< str1.KMP_Find(str2, 0);
//	return 0;
//}