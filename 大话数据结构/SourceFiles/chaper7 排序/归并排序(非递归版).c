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

/*�������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n]*/
void Merge(int SR[], int TR[], int i, int m, int n)
{
	int j, k, l;
	/* ��SR�м�¼��С����鲢��TR */
	for (j = m + 1, k = i; i <= m && j <= n; k++)
	{
		if (SR[i] < SR[j])
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	if (i <= m)
	{
		for (l = 0; l <= m - i; l++)
			/* ��ʣ���SR[i..m]���Ƶ�TR */
			TR[k + l] = SR[i + l];
	}
	if (j <= n)
	{
		for (l = 0; l <= n - j; l++)
			/* ��ʣ���SR[j..n]���Ƶ�TR */
			TR[k + l] = SR[j + l];
	}
}


/* ��SR[]�����ڳ���Ϊs�������������鲢��TR[] */
void MergePass(int SR[], int TR[], int s, int n)
{
	int i = 1;
	int j;
	while (i <= n - 2 * s + 1)
	{
		/*�����鲢*/
		Merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
		i = i + 2 * s;
	}
	/*�鲢�����������*/
	if (i < n - s + 1)
		Merge(SR, TR, i, i + s - 1, n);
	/*�����ֻʣ�µ���������*/
	else
		for (j = i; j <= n; j++)
			TR[j] = SR[j];
}


/* ��˳���L���鲢�ǵݹ����� */
void MergeSort2(SqList* L)
{
	/*�������ռ�*/
	int* TR = (int*)malloc(sizeof(int) * L->length);
	int k = 1;
	while (k < L->length)
	{
		MergePass(L->r, TR, k, L->length);
		/*�����г��ȼӱ�*/
		k = k * 2;
		MergePass(TR, L->r, k, L->length);
		/*�����г��ȼӱ�*/
		k = k * 2;
	}
}