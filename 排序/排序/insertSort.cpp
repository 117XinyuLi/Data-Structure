#include<iostream>
using namespace std;

void insertSort1(int a[], int n)
{
	int i, j, temp;
	for (i = 1; i < n; i++)
	{
		temp = a[i];
		for (j = i; j > 0 && a[j - 1] > temp; j--)
			a[j] = a[j - 1];
		a[j] = temp;
	}
}

void insertSort2(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			int x = arr[i];
			int j = i - 1;
			int left = 0;
			int right = i - 1;
			int mid = 0;
			while (left <= right)
			{
				mid = (int)((left + right) / 2);
				if (x == arr[mid])
				{
					left = mid;
					break;
				}
				else if (x < arr[mid])
					right = mid - 1;
				else
					left = mid + 1;
			}//用对分查找找位置
			while (j >= left)//这里不用mid，不然会在第一次排序时出错
			{
				arr[j + 1] = arr[j];
				j--;
			}
			arr[left] = x;
		}
	}
}

int main()
{
	int a[10] = { 3, 1, 5, 7, 2, 4, 9, 6, 10, 8 };
	insertSort1(a, 10);
	for (int i = 0; i < 10; i++)
		cout << a[i] << " ";
	cout << endl;

	int b[10] = { 3, 1, 5, 7, 2, 4, 9, 6, 10, 8 };
	insertSort2(b, 10);
	for (int i = 0; i < 10; i++)
		cout << b[i] << " ";
	cout << endl;
	
	return 0;
}