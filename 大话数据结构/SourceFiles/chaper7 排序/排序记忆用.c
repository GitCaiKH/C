#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAXSIZE 50

typedef struct
{
	int r[MAXSIZE];
	int length;
}SqList;

/*交换类排序用，例如冒泡排序和快速排序*/
void Swap(SqList* L, int i, int j)
{
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}

/*--------------插入类排序--------------*/

/*对顺序表进行插入排序*/
void InsertSort(SqList* L)
{
	int i, j;
	for (i = 2; i <= L->length; i++)
	{
		L->r[0] = L->r[i];
		for (j = i - 1; L->r[0] < L->r[j]; j--)
			L->r[j + 1] = L->r[j];
		L->r[j + 1] = L->r[0];
	}
}
/*对顺序表进行折半插入排序*/
void BInsertSort(SqList* L)
{
	int low, high, mid;
	int i, j;
	for (i = 2; i <= L->length; i++)
	{
		low = 1;
		high = i - 1;
		L->r[0] = L->r[i];
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (L->r[0] < L->r[mid])
				high = mid - 1;
			else
				low = mid + 1;
		}
		for (j = i - 1; j >= high + 1; j--)
			L->r[j + 1] = L->r[j];
		L->r[high + 1] = L->r[0];
	}
}

/*对顺序表进行希尔排序*/
void ShellSort(SqList* L)
{
	int i, j;
	int increment = L->length;
	do
	{
		increment = increment / 3 + 1;
		for (i = increment + 1; i <= L->length; i++)
		{
			if (L->r[i] < L->r[i - increment])
			{
				L->r[0] = L->r[i];
				for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment)
					L->r[j + increment] = L->r[j];
				L->r[j + increment] = L->r[0];
			}
		}
	} while (increment > 1);
}

/*--------------交换类排序--------------*/

/*对顺序表进行冒泡排序(优化版)*/
void BubbleSort(SqList* L)
{
	int i, j;
	int flag = 1;
	for (i = 1; i < L->length && flag == 1; i++)
	{
		flag = 0;
		for (j = L->length - 1; j >= i; j--)
		{
			if (L->r[j] > L->r[j + 1])
			{
				Swap(L, j, j + 1);
				flag = 1;
			}
		}
	}
}

/*对顺序表进行快速排序*/
int Partition(SqList* L, int low, int high)
{
	int pivotkey;
	pivotkey = L->r[low];
	L->r[0] = L->r[low];
	while (low < high)
	{
		while (low < high && L->r[high] >= pivotkey)
			high--;
		L->r[low] = L->r[high];
		while (low < high && L->r[low] <= pivotkey)
			low++;
		L->r[high] = L->r[low];
	}
	L->r[low] = L->r[0];
	return low;
}

void QSort(SqList* L, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = Partition(L, low, high);
		QSort(L, low, pivot - 1);
		QSort(L, pivot + 1, high);
	}
}

void QuickSort(SqList* L)
{
	QSort(L, 1, L->length);
}

/*--------------选择类排序--------------*/

void SelectSort(SqList* L)
{
	int i, j, min;
	for (i = 1; i < L->length; i++)
	{
		min = i;
		for (j = i + 1; j <= L->length; j++)
			if (L->r[min] > L->r[j])
				min = j;
		if (min != i)
			Swap(L, i, min);
	}
}

/*对顺序表进行堆排序*/
void HeapAdjust(SqList* L, int s, int m)
{
	int temp, j;
	temp = L->r[s];
	for (j = 2 * s; j <= m; j *= 2)
	{
		if (j < m && L->r[j] < L->r[j + 1])
			j++;
		if (temp >= L->r[j])
			break;
		L->r[s] = L->r[j];
		s = j;
	}
	L->r[s] = temp;
}

void HeapSort(SqList* L)
{
	int i;
	for (i = L->length / 2; i > 0; i--)
		HeapAdjust(L, i, L->length);
	for (i = L->length; i > 1; i--)
	{
		Swap(L, 1, i);
		HeapAdjust(L, 1, i - 1);
	}
}

/*--------------归并类排序--------------*/

/*对顺序表进行归并排序*/
void Merge(int SR[], int TR[], int low, int mid, int high)
{
	int i, j, k;
	i = low;
	j = mid + 1;
	k = low;
	while (i <= mid && j <= high)
	{
		if (SR[i] < SR[j])
			TR[k++] = SR[i++];
		else
			TR[k++] = SR[j++];
	}
	while (i <= mid)
		TR[k++] = SR[i++];
	while (j <= high)
		TR[k++] = SR[j++];
}

/*递归版*/
void MSort(int SR[], int TR1[], int low, int high)
{
	int mid;
	int TR2[MAXSIZE + 1];
	if (low == high)
		TR1[low] = SR[low];
	else
	{
		mid = (low + high) / 2;
		MSort(SR, TR2, low, mid);
		MSort(SR, TR2, mid + 1, high);
		Merge(TR2, TR1, low, mid, high);
	}
}

void MergeSort(SqList* L)
{
	MSort(L->r, L->r, 1, L->length);
}

/*非递归版*/
void MergePass(int SR[], int TR[], int s, int n)
{
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i = i + 2 * s)
		Merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
	if (i < n - s + 1)
		Merge(SR, TR, i, i + s - 1, n);
	else
		for (j = i; j <= n; j++)
			TR[j] = SR[j];
}

void MergeSort2(SqList* L)
{
	int* TR = (int)malloc(sizeof(int) * L->length);
	int k;
	for (k = 1; k < L->length; k *= 2)
	{
		MergePass(L->r, TR, k, L->length);
		k *= 2;
		MergePass(TR, L->r, k, L->length);
	}
}