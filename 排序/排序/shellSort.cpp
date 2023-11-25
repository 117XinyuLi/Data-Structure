#include<iostream>
using namespace std;

void shellSort(int *x, int length)
{
	int gap = length / 2;
	while (gap >= 1)
	{
		for (int i = 0; i < gap; i++)
		{
			for (int j = i + gap; j < length; j += gap)
			{
				int temp = x[j];
				int k = j - gap;
				while (k >= 0 && x[k] > temp)
				{
					x[k + gap] = x[k];
					k -= gap;
				}
				x[k + gap] = temp;
			}
		}
		gap=gap/2;
	}
	
}
int main()
{
	int x[10] = {9,8,7,6,5,4,3,2,1,0};
	int length = 10;
	shellSort(x, length);
	for (int i = 0; i < length; i++)
	{
		cout << x[i] << " ";
	}
	
}