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

/* 将SR[s..t]归并排序为TR1[s..t] */
void MSort(int SR[], int TR1[], int s, int t)
{
	int m;
	int TR2[MAXSIZE + 1];
	if (s == t)
		TR1[s] = SR[s];
	else
	{
		/* 将SR[s..t]平分为SR[s..m]和SR[m+1..t] */
		m = (s + t) / 2;
		/* 递归将SR[s..m]归并为有序的TR2[s..m] */
		MSort(SR, TR2, s, m);
		/* 递归将SR[m+1..t]归并为有序TR2[m+1..t] */
		MSort(SR, TR2, m + 1, t);
		/* 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]*/
		Merge(TR2, TR1, s, m, t);
	}
}

/*对顺序表L作归并排序*/
void MergeSort(SqList* L)
{
	MSort(L->r, L->r, 1, L->length);
}