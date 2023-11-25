#include<iostream>

using namespace std;

int maxbit(int data[], int n)
{
    int maxData = data[0];
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        maxData /= 10;
        ++d;
    }
    return d;
}
void radixSort(int data[], int n)
{
    int d = maxbit(data, n);
    int* tmp = new int[n];
    int* count = new int [10];
	
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++)
    {
        for (j = 0; j < 10; j++)
            count[j] = 0;
        for (j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10;
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j];
        for (j = n - 1; j >= 0; j--)
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for (j = 0; j < n; j++)
            data[j] = tmp[j];
        radix = radix * 10;
        for (int i = 0; i < n; i++)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    delete[]tmp;
    delete[]count;
}

int main()
{
    int a[10]={ 17,18,60,40,7,32,73,65,85 };
    radixSort(a, 9);
    return 0;
}
