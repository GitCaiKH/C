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

/*��֪L->r[s...m]�м�¼�Ĺؼ��ֳ�L��>r[s]֮�������ѵĶ���*/
/*����������L->r[s]�Ĺؼ��֣�ʹL->r[s...m]��Ϊһ���󶥶�*/
void HeapAdjust(SqList* L, int s, int m)
{
	int temp, j;
	temp = L->r[s];
	/*�عؼ��ֽϴ�ĺ��ӽ������ɸѡ*/
	for (j = 2 * s; j <= m; j *= 2)
	{
		if (j < m && L->r[j] < L->r[j + 1])
			/*jΪ�ؼ����нϴ�ļ�¼���±�*/
			++j;
		if (temp >= L->r[j])
			/*tempӦ�ò�����λ��s��*/
			break;
		L->r[s] = L->r[j];
		s = j;
	}
	/*����*/
	L->r[s] = temp;
}

/*��˳���L���ж�����*/
void HeapSort(SqList* L)
{
	int i;
	/*��L�е�r������һ���󶥶�*/
	for (i = L->length / 2; i > 0; i--)
		HeapAdjust(L, i, L->length);
	for (i = L->length; i > 1; i--)
	{
		/*���Ѷ���¼�͵�ǰδ�����������е����һ����¼����*/
		swap(L, 1, i);
		HeapAdjust(L, 1, i - 1);
	}
}