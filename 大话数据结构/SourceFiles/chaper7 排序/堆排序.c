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

/*已知L->r[s...m]中记录的关键字除L—>r[s]之外均满足堆的定义*/
/*本函数调整L->r[s]的关键字，使L->r[s...m]成为一个大顶堆*/
void HeapAdjust(SqList* L, int s, int m)
{
	int temp, j;
	temp = L->r[s];
	/*沿关键字较大的孩子结点向下筛选*/
	for (j = 2 * s; j <= m; j *= 2)
	{
		if (j < m && L->r[j] < L->r[j + 1])
			/*j为关键字中较大的记录的下标*/
			++j;
		if (temp >= L->r[j])
			/*temp应该插入在位置s上*/
			break;
		L->r[s] = L->r[j];
		s = j;
	}
	/*插入*/
	L->r[s] = temp;
}

/*对顺序表L进行堆排序*/
void HeapSort(SqList* L)
{
	int i;
	/*把L中的r构建成一个大顶堆*/
	for (i = L->length / 2; i > 0; i--)
		HeapAdjust(L, i, L->length);
	for (i = L->length; i > 1; i--)
	{
		/*将堆顶记录和当前未经排序子序列的最后一个记录交换*/
		swap(L, 1, i);
		HeapAdjust(L, 1, i - 1);
	}
}