#include<iostream>
using namespace std;

void bubbleSort(int arr[], int size)
{
	int temp = 0;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = size - 1; j >= i + 1; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}

void cocktailSort(int arr[], int size)
{
	int left = 0;
	int right = size - 1;
	int current = 0;
	int temp = 0;
	while (left < right)
	{
		for (int i = left; i < right; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				current = i;
			}
		}
		right = current;
		for (int i = right; i > left; i--)
		{
			if (arr[i] < arr[i - 1])
			{
				temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
				current = i;
			}
		}
		left = current;
	}
}//Ë«ÏòÃ°ÅÝÅÅÐò

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
	bubbleSort(arr, size);
	print(arr, size);

	int arr2[] = { 9,8,7,6,5,4,3,2,1,0 };
	int size2 = sizeof(arr2) / sizeof(arr2[0]);
	cocktailSort(arr2, size2);
	print(arr2, size2);
	
	return 0;
}