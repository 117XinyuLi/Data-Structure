#include<iostream>

using namespace std;

int F[100]={0}; //쳲���������

//쳲���������
int fibonacciSearch(int* a, int n, int key)
{
	int low = 0;
	int high = n - 1;
	int k = 0; //쳲������ָ���ֵ�±�
	int mid = 0;
	while (n > F[k] - 1) //����nλ��쳲��������е�λ��
		k++;
	for (int i = n; i < F[k] - 1; i++) //����������ֵ��ȫ
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
				return mid; //�������˵��mid��Ϊ���ҵ���λ��
			else
				return n - 1; //��mid>n-1˵���ǲ�ȫ��ֵ������n-1
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