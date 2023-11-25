#include<iostream>
using namespace std;

// ≤Â÷µ≤È’“
int interpolationSearch(int arr[], int n, int target) 
{
	int left = 0, right = n - 1;
	while (left <= right) 
	{
		int mid = left + (right - left) * (target - arr[left]) / (arr[right] - arr[left]);
		if (arr[mid] == target) return mid;
		if (arr[mid] < target) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}

int main() 
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = sizeof(arr) / sizeof(int);
	int target = 1;
	int index = interpolationSearch(arr, n, target);
	cout << index << endl;
	return 0;
}