#include <iostream>
#define NULLTAG 0

template<class KeyType>
class Element
{
public:
	KeyType key;//关键字
	bool isFill;//是否装填
	int times;//关键字出现次数
	Element()
	{
		key = NULLTAG;
		isFill = false;
		times = 0;
	}
};

template<class KeyType>
class HashList
{
public:
	HashList(int MaxSZ);
	HashList(const HashList& L);
	~HashList();
	HashList& operator=(const HashList& L);
	void ClearHashList();
	bool Insert(KeyType key);
	bool Delete(KeyType key);
	int Search(KeyType key, int& times);
	void Create(int num);
private:
	Element<KeyType>* HT;
	void ReSize(int NewSize);
	int CurrentSize;
	int MaxSize;
};
template<class KeyType>
HashList<KeyType>::HashList(int MaxSZ)
{
	MaxSize = MaxSZ;
	CurrentSize = 0;
	HT = new Element<KeyType>[MaxSize];
}
template<class KeyType>
HashList<KeyType>::HashList(const HashList& L)
{
	MaxSize = L.MaxSize;
	CurrentSize = L.CurrentSize;
	delete[]HT;
	HT = new Element<KeyType>[MaxSize];
	for (int i = 0; i < MaxSize; i++)
	{
		HT[i] = L.HT[i];
	}
}
template<class KeyType>
HashList<KeyType>::~HashList()
{
	delete[]HT;
	HT = NULL;
}
template<class KeyType>
HashList<KeyType>& HashList<KeyType>::operator=(const HashList& L)
{
	if (this != &L)
	{
		delete[]HT;
		MaxSize = L.MaxSize;
		CurrentSize = L.CurrentSize;
		HT = new Element<KeyType>[MaxSize];
		for (int i = 0; i < MaxSize; i++)
		{
			HT[i] = L.HT[i];
		}
	}
	return *this;
}
template<class KeyType>
void HashList<KeyType>::ClearHashList()
{
	CurrentSize = 0;
	for (int i = 0; i < MaxSize; i++)
	{
		HT[i].key = NULLTAG;
		HT[i].isFill = false;
		HT[i].times = 0;
	}
}
template<class KeyType>
bool HashList<KeyType>::Insert(KeyType key)
{
	if (CurrentSize == MaxSize)
	{
		ReSize(2 * MaxSize);
	}
	int i = 0;
	int pos = key % MaxSize;
	while (HT[pos].isFill && HT[pos].key != key)
	{
		i++;
		pos = (key + i) % MaxSize;
	}
	if (HT[pos].isFill)
	{
		std::cout << "关键字已存在，出现次数加一" << std::endl;
		HT[pos].times++;
		return false;
	}
	else
	{
		HT[pos].key = key;
		HT[pos].isFill = true;
		HT[pos].times = 1;
		CurrentSize++;
		return true;
	}
}
template<class KeyType>
bool HashList<KeyType>::Delete(KeyType key)
{
	int i = key % MaxSize;
	int j = i;
	while (HT[i].key != key)
	{
		i = (i + 1) % MaxSize;
		if (i == j)
		{
			std::cout << "未找到关键字" << std::endl;
			return false;
		}
	}
	if (HT[i].isFill)
	{
		HT[i].isFill = false;
		HT[i].key = NULLTAG;
		HT[i].times = 0;
		CurrentSize--;
		return true;
	}
	else
	{
		std::cout << "未找到关键字" << std::endl;
		return false;
	}
}
template<class KeyType>
int HashList<KeyType>::Search(KeyType key,int&times)
{
	int i = key % MaxSize;
	int j = i;
	while (HT[i].key != key)
	{
		i = (i + 1) % MaxSize;
		if (i == j)
		{
			std::cout << "未找到关键字" << std::endl;
			return -1;
		}
	}
	if (HT[i].isFill)
	{
		times = HT[i].times;
		return i;
	}
	else
	{
		std::cout << "未找到关键字" << std::endl;
		return -1;
	}
}
template<class KeyType>
void HashList<KeyType>::Create(int num)
{
	if (num > MaxSize)
	{
		ReSize(num);
	}
	if (CurrentSize != 0)
	{
		ClearHashList();
		std::cout << "哈希表已清空" << std::endl;
	}
	std::cout << "请输入关键字" << std::endl;
	for (int i = 0; i < num; i++)
	{
		KeyType key;
		std::cin >> key;
		Insert(key);
	}
}
template<class KeyType>
void HashList<KeyType>::ReSize(int NewSize)
{
	HashList<KeyType> temp(*this);
	delete[]HT;
	HT = new Element<KeyType>[NewSize];
	MaxSize = NewSize;
	CurrentSize = 0;
	for (int i = 0; i < temp.MaxSize; i++)
	{
		if (temp.HT[i].isFill)
		{
			Insert(temp.HT[i].key);
		}
	}
}

//int main()
//{
//	HashList<int> L(1);
//	int num;
//	std::cin >> num;
//	L.Create(num);
//	int key;
//	std::cin >> key;
//	int times=0;
//	int i = L.Search(key,times);
//	if (i != -1)
//	{
//		std::cout << "关键字" << key << "的位置为" << i << std::endl;
//	}
//	L.Delete(key);
//	i = L.Search(key,times);
//	if (i != -1)
//	{
//		std::cout << "关键字" << key << "的位置为" << i << std::endl;
//	}
//
//	HashList<int> L2=L;
//	L2 = L;
//	i=L2.Search(2,times);
//	if (i != -1)
//	{
//		std::cout << "关键字" << 2 << "的位置为" << i << std::endl;
//	}
//	L2.ClearHashList();
//	
//	return 0;
//}