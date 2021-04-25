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

/*冒泡排序(Bubble Sort)*/
/*对顺序表L作交换排序(冒泡排序初级版)*/
void BubbleSort0(SqList* L)
{
	int i, j;
	for (i = 1; i < L->length; i++)
	{
		for (j = i + 1; j <= L->length; j++)
		{
			if (L->r[i] > L->r[j])
			{
				/*交换L->r[i]与L->r[j]的值*/
				swap(L, i, j);
			}
		}
	}
}

/*对顺序表L作冒泡排序*/
void BubbleSort(SqList* L)
{
	int i, j;
	for (i = 1; i < L->length; i++)
	{
		/*注意j是从后往前循环*/
		for (j = L->length - 1; j >= i; j--)
		{
			/*若前者大于后者(注意这里与上一算法差异)*/
			if (L->r[j] > L->r[j + 1])
			{
				/*交换L->r[j]和L->r[j+1]的值*/
				swap(L, j, j + 1);
			}
		}
	}
}

/*对顺序表L作改进冒泡算法*/
void BubbleSort2(SqList* L)
{
	int i, j;
	/*flag用来作为标记*/
	Status flag = TRUE;
	/*若flag为TRUE说明有过数据交换，否则停止循环*/
	for (i = 1; i < L->length && flag; i++)
	{
		/*初始为false*/
		flag = FALSE;
		for (j = L->length - 1; j >= i; j--)
		{
			if (L->r[j] > L->r[j + 1])
			{
				/*交换L->r[j]与L->r[j+1]的值*/
				swap(L, j, j + 1);
				/*如果有数据交换，则flag为true*/
				flag = TRUE;
			}
		}
	}
}