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

/*对顺序表L作直接插入排序*/
void InsertSort(SqList* L)
{
	int i, j;
	for (i = 2; i <= L->length; i++)
	{
		/*需将L->r[i]插入有序子表*/
		if (L->r[i] < L->r[i - 1])
		{
			/*设置哨兵*/
			L->r[0] = L->r[i];
			for (j = i - 1; L->r[j] > L->r[0]; j--)
				/*记录后移*/
				L->r[j + 1] = L->r[j];
			/*插入到正确位置*/
			L->r[j + 1] = L->r[0];
		}
	}
}