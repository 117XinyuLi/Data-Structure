#include<iostream>

using namespace std;

int binarySearch(int arr[], int n, int target) 
{
	int l = 0, r = n - 1;
	while (l <= r) 
	{
		int mid = (l + r) / 2;
		if (arr[mid] == target) 
			return mid;
		if (target < arr[mid]) 
			r = mid - 1;
		else 
			l = mid + 1;
	}
	return -1;
}

int main() 
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int n = sizeof(arr) / sizeof(int);
	int target = 7;
	int res = binarySearch(arr, n, target);
	cout << res << endl;
	return 0;
}