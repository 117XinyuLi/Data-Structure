#include<iostream>
using namespace std;

void selectSort1(int arr[], int size)
{
	int temp = 0;
	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j <= size - 1; j++)
		{
			if (arr[min] > arr[j])
				min = j;
		}
		if (min != i)
		{
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}

void selectSort2(int arr[], int size)//—°‘Ò≈≈–Ú”≈ªØ
{
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		int maxpos = right;
		int minpos = left;
		int temp = 0;
		for (int i = left; i <= right; i++)
		{
			if (arr[i] > arr[maxpos])
			{
				maxpos = i;
			}
			else if (arr[i] < arr[minpos])
			{
				minpos = i;
			}
		}
		if (maxpos != right)
		{
			temp = arr[maxpos];
			arr[maxpos] = arr[right];
			arr[right] = temp;
		}
		if (minpos == right)
		{
			minpos = maxpos;
		}
		if (minpos != left)
		{
			temp = arr[minpos];
			arr[minpos] = arr[left];
			arr[left] = temp;
		}
		left++;
		right--;
	}
}

void print(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main()
{
	int arr[] = { 9,8,7,6,5,4,3,2,1,0 };
	int size = sizeof(arr) / sizeof(arr[0]);
	selectSort1(arr, size);
	print(arr, size);

	int arr2[] = { 9,8,7,6,5,4,3,2,1,0 };
	int size2 = sizeof(arr2) / sizeof(arr2[0]);
	selectSort2(arr2, size2);
	print(arr2, size2);
	return 0;
}