#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
/*用于要排序数组个数最大值，可根据需要修改*/
#define MAXSIZE 10

typedef int Status;

typedef struct
{
	/*用于存储要排序的数组，r[0]用作哨兵或临时变量*/
	int r[MAXSIZE + 1];
	/*用于记录顺序表的长度*/
	int length;
}SqList;

/*将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]*/
void Merge(int SR[], int TR[], int i, int m, int n)
{
	int j, k, l;
	/* 将SR中记录由小到大归并入TR */
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
			/* 将剩余的SR[i..m]复制到TR */
			TR[k + l] = SR[i + l];
	}
	if (j <= n)
	{
		for (l = 0; l <= n - j; l++)
			/* 将剩余的SR[j..n]复制到TR */
			TR[k + l] = SR[j + l];
	}
}


/* 将SR[]中相邻长度为s的子序列两两归并到TR[] */
void MergePass(int SR[], int TR[], int s, int n)
{
	int i = 1;
	int j;
	while (i <= n - 2 * s + 1)
	{
		/*两两归并*/
		Merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
		i = i + 2 * s;
	}
	/*归并最后两个序列*/
	if (i < n - s + 1)
		Merge(SR, TR, i, i + s - 1, n);
	/*若最后只剩下单个子序列*/
	else
		for (j = i; j <= n; j++)
			TR[j] = SR[j];
}


/* 对顺序表L作归并非递归排序 */
void MergeSort2(SqList* L)
{
	/*申请额外空间*/
	int* TR = (int*)malloc(sizeof(int) * L->length);
	int k = 1;
	while (k < L->length)
	{
		MergePass(L->r, TR, k, L->length);
		/*子序列长度加倍*/
		k = k * 2;
		MergePass(TR, L->r, k, L->length);
		/*子序列长度加倍*/
		k = k * 2;
	}
}