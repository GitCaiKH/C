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

/* ��SR[s..t]�鲢����ΪTR1[s..t] */
void MSort(int SR[], int TR1[], int s, int t)
{
	int m;
	int TR2[MAXSIZE + 1];
	if (s == t)
		TR1[s] = SR[s];
	else
	{
		/* ��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t] */
		m = (s + t) / 2;
		/* �ݹ齫SR[s..m]�鲢Ϊ�����TR2[s..m] */
		MSort(SR, TR2, s, m);
		/* �ݹ齫SR[m+1..t]�鲢Ϊ����TR2[m+1..t] */
		MSort(SR, TR2, m + 1, t);
		/* ��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]*/
		Merge(TR2, TR1, s, m, t);
	}
}

/*��˳���L���鲢����*/
void MergeSort(SqList* L)
{
	MSort(L->r, L->r, 1, L->length);
}