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

/*��˳���L����ѡ������*/
void SelectSort(SqList* L)
{
	int i, j, min;
	for (i = 1; i < L->length; i++)
	{
		/*����ǰ�±궨��Ϊ��Сֵ�±�*/
		min = i;
		/*ѭ��֮�������*/
		for (j = i + 1; j <= L->length; j++)
		{
			/*�����С�ڵ�ǰ��Сֵ�Ĺؼ���*/
			if (L->r[min] > L->r[j])
				/*���˹ؼ��ֵ��±긳ֵ��min*/
				min = j;
		}
		/*��min������i��˵���ҵ���Сֵ������*/
		if (i != min)
			/*����L->r[i]��L->r[min]��ֵ*/
			swap(L, i, min);
	}
}