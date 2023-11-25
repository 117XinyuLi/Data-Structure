#include<iostream>

using namespace std;

int F[100]={0}; //斐波那契数列

//斐波那契查找
int fibonacciSearch(int* a, int n, int key)
{
	int low = 0;
	int high = n - 1;
	int k = 0; //斐波那契分割数值下标
	int mid = 0;
	while (n > F[k] - 1) //计算n位于斐波那契数列的位置
		k++;
	for (int i = n; i < F[k] - 1; i++) //将不满的数值补全
		a[i] = a[n - 1];
	while (low <= high)
	{
		mid = low + F[k - 1] - 1;
		if (key < a[mid])
		{
			high = mid - 1;
			k = k - 1;
		}
		else if (key > a[mid])
		{
			low = mid + 1;
			k = k - 2;
		}
		else
		{
			if (mid <= n - 1)
				return mid; //若相等则说明mid即为查找到的位置
			else
				return n - 1; //若mid>n-1说明是补全数值，返回n-1
		}
	}
	return -1;

}


int main()
{
	F[0] = 0;
	F[1] = 1;
	for (int i = 2; i < 100; i++)
	{
		F[i] = F[i - 1] + F[i - 2];
	}

	int a[200]={0};
	for (int i = 0; i < 100; i++)
	{
		a[i] = i;
	}
	
	int key = 99;
	int n = 100;
	int result = fibonacciSearch(a, n, key);
	cout << result << endl;

	return 0;
}