#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
/*����Ҫ��������������ֵ���ɸ�����Ҫ�޸�*/
#define MAXSIZE 10

typedef int Status;

typedef struct
{
	/*���ڴ洢Ҫ��������飬r[0]�����ڱ�����ʱ����*/
	int r[MAXSIZE + 1];
	/*���ڼ�¼˳���ĳ���*/
	int length;
}SqList;

/*����L������r���±�Ϊi��j��ֵ*/
void swap(SqList* L, int i, int j)
{
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}

/*ð������(Bubble Sort)*/
/*��˳���L����������(ð�����������)*/
void BubbleSort0(SqList* L)
{
	int i, j;
	for (i = 1; i < L->length; i++)
	{
		for (j = i + 1; j <= L->length; j++)
		{
			if (L->r[i] > L->r[j])
			{
				/*����L->r[i]��L->r[j]��ֵ*/
				swap(L, i, j);
			}
		}
	}
}

/*��˳���L��ð������*/
void BubbleSort(SqList* L)
{
	int i, j;
	for (i = 1; i < L->length; i++)
	{
		/*ע��j�ǴӺ���ǰѭ��*/
		for (j = L->length - 1; j >= i; j--)
		{
			/*��ǰ�ߴ��ں���(ע����������һ�㷨����)*/
			if (L->r[j] > L->r[j + 1])
			{
				/*����L->r[j]��L->r[j+1]��ֵ*/
				swap(L, j, j + 1);
			}
		}
	}
}

/*��˳���L���Ľ�ð���㷨*/
void BubbleSort2(SqList* L)
{
	int i, j;
	/*flag������Ϊ���*/
	Status flag = TRUE;
	/*��flagΪTRUE˵���й����ݽ���������ֹͣѭ��*/
	for (i = 1; i < L->length && flag; i++)
	{
		/*��ʼΪfalse*/
		flag = FALSE;
		for (j = L->length - 1; j >= i; j--)
		{
			if (L->r[j] > L->r[j + 1])
			{
				/*����L->r[j]��L->r[j+1]��ֵ*/
				swap(L, j, j + 1);
				/*��������ݽ�������flagΪtrue*/
				flag = TRUE;
			}
		}
	}
}