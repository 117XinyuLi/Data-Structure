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

	pivotkey = L[low]; /* ���ӱ�ĵ�һ����¼�������¼ */
	while (low < high) /*  �ӱ�����˽�������м�ɨ�� */
	{
		while (low < high && L[high] >= pivotkey)
			high--;
		swap(L, low, high);/* ���������¼С�ļ�¼�������Ͷ� */
		while (low < high && L[low] <= pivotkey)
			low++;
		swap(L, low, high);/* ���������¼��ļ�¼�������߶� */
	}
	return low; /* ������������λ�� */
}

/* ��˳���L�е�������L->r[low..high]���������� */
void QSort(int* L, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = Partition(L, low, high); /*  ��L->r[low..high]һ��Ϊ�����������ֵpivot */
		
		for (int i = 0; i < length; i++)
		{
			std::cout << x[i] << " ";
		}
		std::cout << std::endl;

		QSort(L, low, pivot - 1); /* �Ե��ӱ�ݹ����� */
		QSort(L, pivot + 1, high); /* �Ը��ӱ�ݹ����� */
		
	}
}
int main()
{
	QSort(x,0, length-1);
}