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

/*交换L中数组r的下标为i和j的值*/
void swap(SqList* L, int i, int j)
{
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}

/* 交换顺序表L中子表的记录，使枢轴记录到位，并返回其所在位置 */
/* 此时在它之前（后）的记录均不大（小）于它。*/
int Partition(SqList* L, int low, int high)
{
	int pivotkey;
	/* 用子表的第一个记录作枢轴记录 */
	pivotkey = L->r[low];
	/* 从表的两端交替向中间扫描 */
	while (low < high)
	{
		while (low < high && L->r[high] >= pivotkey)
			high--;
		/* 将比枢轴记录小的记录交换到低端 */
		swap(L, low, high);
		while (low < high && L->r[low] <= pivotkey)
			low++;
		/* 将比枢轴记录大的记录交换到高端 */
		swap(L, low, high);
	}
	/* 返回枢轴所在位置 */
	return low;
}

/* 对顺序表L中的子序列L->r[low..high]作快速排序 */
void QSort(SqList* L, int low, int high)
{
	int pivot;
	if (low < high)
	{
		/* 将L->r[low...high]一分为二， */
		/* 算出枢轴值pivot */
		pivot = Partition(L, low, high);
		/*对低子表递归排序*/
		QSort(L, low, pivot - 1);
		/*对高子表递归排序*/
		QSort(L, pivot + 1, high);
	}
}

/*对顺序表作快速排序*/
void QuickSort(SqList* L)
{
	QSort(L, 1, L->length);
}