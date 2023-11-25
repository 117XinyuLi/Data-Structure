#include<iostream>
int length = 10;
int x[10] = { 9,8,7,6,5,4,3,2,1 };

void swap(int* L, int i, int j)
{
	int temp = L[i];
	L[i] = L[j];
	L[j] = temp;
}
int Partition(int* L, int low, int high)
{
	int pivotkey;

	pivotkey = L[low]; /* 用子表的第一个记录作枢轴记录 */
	while (low < high) /*  从表的两端交替地向中间扫描 */
	{
		while (low < high && L[high] >= pivotkey)
			high--;
		swap(L, low, high);/* 将比枢轴记录小的记录交换到低端 */
		while (low < high && L[low] <= pivotkey)
			low++;
		swap(L, low, high);/* 将比枢轴记录大的记录交换到高端 */
	}
	return low; /* 返回枢轴所在位置 */
}

/* 对顺序表L中的子序列L->r[low..high]作快速排序 */
void QSort(int* L, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = Partition(L, low, high); /*  将L->r[low..high]一分为二，算出枢轴值pivot */
		
		for (int i = 0; i < length; i++)
		{
			std::cout << x[i] << " ";
		}
		std::cout << std::endl;

		QSort(L, low, pivot - 1); /* 对低子表递归排序 */
		QSort(L, pivot + 1, high); /* 对高子表递归排序 */
		
	}
}
int main()
{
	QSort(x,0, length-1);
}