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

/*��˳���L��ϣ������*/
void ShellSort(SqList* L)
{
	int i, j;
	int increment = L->length;
	do
	{
		/*��������*/
		increment = increment / 3 + 1;
		for (i = increment + 1; i <= L->length; i++)
		{
			if (L->r[i] < L->r[i - increment])
			{
				/*�轫L->r[i]�������������ӱ�*/
				/*�ݴ���L->r[0]*/
				L->r[0] = L->r[i];
				for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment)
					/*��¼���ƣ����Ҳ���λ��*/
					L->r[j + increment] = L->r[j];
				/*����*/
				L->r[j + increment] = L->r[0];
			}
		}
	} while (increment > 1);
}