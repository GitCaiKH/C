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

/*��˳���L��ֱ�Ӳ�������*/
void InsertSort(SqList* L)
{
	int i, j;
	for (i = 2; i <= L->length; i++)
	{
		/*�轫L->r[i]���������ӱ�*/
		if (L->r[i] < L->r[i - 1])
		{
			/*�����ڱ�*/
			L->r[0] = L->r[i];
			for (j = i - 1; L->r[j] > L->r[0]; j--)
				/*��¼����*/
				L->r[j + 1] = L->r[j];
			/*���뵽��ȷλ��*/
			L->r[j + 1] = L->r[0];
		}
	}
}