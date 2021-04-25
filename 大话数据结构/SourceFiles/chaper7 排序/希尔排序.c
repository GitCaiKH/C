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

/*对顺序表L作希尔排序*/
void ShellSort(SqList* L)
{
	int i, j;
	int increment = L->length;
	do
	{
		/*增量序列*/
		increment = increment / 3 + 1;
		for (i = increment + 1; i <= L->length; i++)
		{
			if (L->r[i] < L->r[i - increment])
			{
				/*需将L->r[i]插入有序增量子表*/
				/*暂存在L->r[0]*/
				L->r[0] = L->r[i];
				for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment)
					/*记录后移，查找插入位置*/
					L->r[j + increment] = L->r[j];
				/*插入*/
				L->r[j + increment] = L->r[0];
			}
		}
	} while (increment > 1);
}