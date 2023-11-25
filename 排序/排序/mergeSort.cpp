#include<iostream>
#define MAXSIZE 100
using namespace std;
int sort_floor = -1;
int ans[10][MAXSIZE] = { 0 };
void Merge(int SR[], int TR[], int i, int m, int n, int depth)
{
	int low = i;
	int high = n;
	int j, k, l;
	for (j = m + 1, k = i; i <= m && j <= n; k++)
	{
		if (SR[i] < SR[j])
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	if (i <= m)
	{
		for (l = 0; l <= m - i; l++)
			TR[k + l] = SR[i + l];		
	}
	if (j <= n)
	{
		for (l = 0; l <= n - j; l++)
			TR[k + l] = SR[j + l];		
	}
	for (int  g= low; g <=high ; g++)
	{
		ans[depth][g] = TR[g];
	}
	if (sort_floor < depth)
	{
		sort_floor = depth;
	}
	
}

void MSort(int SR[], int TR1[], int s, int t,int depth)
{
	int TR2[MAXSIZE]={0};
	if (s == t)
	{
		TR1[s] = SR[s];
		ans[depth][s] = TR1[s];
	}
	else
	{
		int m = (s + t-1) / 2;				
		MSort(SR, TR2, s, m,depth+1);		
		MSort(SR, TR2, m + 1, t,depth+1);	
		Merge(TR2, TR1, s, m, t,depth);	
		
	}
}

int main()
{
	int arr[MAXSIZE] = { 17,18,60,40,7,32,73,65,85 };
	int length = 9;
	MSort(arr,arr,0 ,length-1,0);
	
	for (int i = sort_floor; i >= 0; i--)
	{
		for (int j = 0; j < length; j++)
		{
			cout << ans[i][j]<<" ";
		}
		cout << endl;
	}
	
}