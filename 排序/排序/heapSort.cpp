#include"Maxheap.hpp"

int main()
{
	Maxheap<int> h(100);
	std::vector<int> data;
	for (int i = 0; i < 100; i++)
	{
		data.push_back(100-i);
	}
	h.createHeap(data);
	h.printSorted();
	return 0;
}