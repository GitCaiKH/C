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

/* ����˳���L���ӱ�ļ�¼��ʹ�����¼��λ��������������λ�� */
/* ��ʱ����֮ǰ���󣩵ļ�¼������С��������*/
int Partition(SqList* L, int low, int high)
{
	int pivotkey;
	/* ���ӱ�ĵ�һ����¼�������¼ */
	pivotkey = L->r[low];
	/* �ӱ�����˽������м�ɨ�� */
	while (low < high)
	{
		while (low < high && L->r[high] >= pivotkey)
			high--;
		/* ���������¼С�ļ�¼�������Ͷ� */
		swap(L, low, high);
		while (low < high && L->r[low] <= pivotkey)
			low++;
		/* ���������¼��ļ�¼�������߶� */
		swap(L, low, high);
	}
	/* ������������λ�� */
	return low;
}

/* ��˳���L�е�������L->r[low..high]���������� */
void QSort(SqList* L, int low, int high)
{
	int pivot;
	if (low < high)
	{
		/* ��L->r[low...high]һ��Ϊ���� */
		/* �������ֵpivot */
		pivot = Partition(L, low, high);
		/*�Ե��ӱ�ݹ�����*/
		QSort(L, low, pivot - 1);
		/*�Ը��ӱ�ݹ�����*/
		QSort(L, pivot + 1, high);
	}
}

/*��˳�������������*/
void QuickSort(SqList* L)
{
	QSort(L, 1, L->length);
}