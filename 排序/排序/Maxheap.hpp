#pragma once
#include<iostream>
#include<vector>

template<class T>
class Maxheap
{
public:
	Maxheap(int cap);
	~Maxheap();
	Maxheap(const Maxheap<T>& h);
	Maxheap<T>& operator=(const Maxheap<T>& h);
	void createHeap(T end);//end表示输入结束，而后直接创建堆
	void createHeap(std::vector<T> data);//直接创建堆
	void insert(T data);
	void remove(T data);
	void print();
	void printSorted();
	void Size() { return size;};
	void Capacity() { return capacity;};
private:
	T* heap;
	int size;
	int capacity;
	void swap(T& a, T& b);
	void heapify(int index);
	void addSpace();
};

template<class T>
Maxheap<T>::Maxheap(int cap)
{
	heap = new T[cap];
	size = 0;
	capacity = 100;
	for (int i = 0; i < capacity; i++)
	{
		heap[i] = 0;
	}
}
template<class T>
Maxheap<T>::~Maxheap()
{
	delete[] heap;
}
template<class T>
Maxheap<T>::Maxheap(const Maxheap<T>& h)
{
	size = h.size;
	capacity = h.capacity;
	heap = new T[capacity];
	for (int i = 0; i < capacity; i++)
	{
		heap[i] = h.heap[i];
	}
}
template<class T>
Maxheap<T>& Maxheap<T>::operator=(const Maxheap<T>& h)
{
	if (this != &h)
	{
		delete[] heap;
		size = h.size;
		capacity = h.capacity;
		heap = new T[capacity];
		for (int i = 0; i < capacity; i++)
		{
			heap[i] = h.heap[i];
		}
	}
	return *this;
}
template<class T>
void Maxheap<T>::createHeap(T end)
{
	std::vector<T>nodeData;
	T item;
	while (true)
	{
		std::cin >> item;
		if (item == end)
			break;
		nodeData.push_back(item);
		size++;
		if (size == capacity)
		{
			addSpace();
		}
	}
	createHeap(nodeData, end);
}
template<class T>
void Maxheap<T>::createHeap(std::vector<T> data)
{
	size = data.size();
	capacity = size;
	for (int i = 0; i < size; i++)
	{
		heap[i] = data[i];
	}
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		heapify(i);
	}
}
template<class T>
void Maxheap<T>::insert(T data)
{
	if (size == capacity)
	{
		//std::cout << "堆已满" << std::endl;
		addSpace();
		return;
	}
	heap[size] = data;
	int index = size;
	while (index > 0)
	{
		int parent = (index - 1) / 2;
		if (heap[parent] < heap[index])
		{
			swap(heap[parent], heap[index]);
			index = parent;
		}
		else
			break;
	}
	size++;
}
template<class T>
void Maxheap<T>::remove(T data)
{
	if (size == 0)
	{
		std::cout << "堆为空" << std::endl;
		return;
	}
	int index = 0;
	while (index < size)
	{
		if (heap[index] == data)
			break;
		index++;
	}
	if (index == size)
	{
		std::cout << "无此元素" << std::endl;
		return;
	}
	heap[index] = heap[size - 1];
	size--;
	heapify(index);
}
template<class T>
void Maxheap<T>::print()
{
	for (int i = 0; i < size; i++)
		std::cout << heap[i] << " ";
	std::cout << std::endl;
}
template<class T>
void Maxheap<T>::printSorted()
{
	Maxheap<T> h(*this);
	std::vector <T> sorted;
	while (h.size > 0)
	{
		//std::cout << h.heap[0] << " ";
		sorted.push_back(h.heap[0]);
		h.remove(h.heap[0]);
	}
	for (int i = sorted.size() - 1; i >= 0; i--)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;
	
}
template<class T>
void Maxheap<T>::swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
template<class T>
void Maxheap<T>::heapify(int index)
{
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int largest = index;
	if (left < size && heap[left] > heap[largest])
		largest = left;
	if (right < size && heap[right] > heap[largest])
		largest = right;
	if (largest != index)
	{
		swap(heap[index], heap[largest]);
		heapify(largest);
	}
}
template<class T>
void Maxheap<T>::addSpace()
{
	capacity = capacity * 2;
	T* newHeap = new T[capacity];
	if (!newHeap)
	{
		std::cout << "空间开辟失败" << std::endl;
		return;
	}
	for (int i = 0; i < size; i++)
	{
		newHeap[i] = heap[i];
	}
	delete[]heap;
	heap = newHeap;
}