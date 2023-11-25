#include<iostream>
using namespace std;

int sequentialSearch1(int arr[], int n, int target) 
{
	for (int i = 0; i < n; i++)
		if (arr[i] == target)
			return i;
	return -1;
}

int sequentialSearch2(int arr[], int n, int target) 
{
	int i = n;
	if (arr[0] == target)
	{
		return 0;
	}
	arr[0] = target;
	while (arr[i] != target)
	{
		i--;
	}
	return i;
}


int main() 
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = sizeof(arr) / sizeof(int);
	int target = 10;
	int index = sequentialSearch1(arr, n, target);
	cout << index << endl;

	index = sequentialSearch2(arr, n, target);
	cout << index << endl;
	
	return 0;
}