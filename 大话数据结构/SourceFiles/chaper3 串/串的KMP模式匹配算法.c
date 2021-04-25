#include<stdio.h>
#include<string.h>

typedef char* String;
void get_nextval(String T, int* nextval)
{
	int j, k;
	j = 0;
	k = -1;
	nextval[0] = -1;
	/*�˴�T[0]��ʾ��T�ĳ���*/
	while (j < strlen(T) - 1)
	{
		/*T[i]��ʾ��׺�ĵ����ַ�*/
		/*T[j]��ʾǰ׺�ĵ����ַ�*/
		if (k == -1 || T[j] == T[k])
		{
			++j;
			++k;
			/*����ǰ�ַ���ǰ׺�ַ���ͬ*/
			if (T[j] != T[k])
				nextval[j] = k;
			else
				/*�����ǰ׺�ַ���ͬ���ս�ǰ׺�ַ���nextvalֵ��ֵ��nextval��iλ�õ�ֵ*/
				nextval[j] = nextval[k];
		}
		else
			/*���ַ�����ͬ����jֵ����*/
			k = nextval[k];
	}
}

int Index_KMP(String S, String T, int pos)
{
	/*i��������S��ǰλ���±�ֵ����pos��Ϊ1*/
	/*���posλ�ÿ�ʼƥ��*/
	int i = pos - 1;
	/*j�����Ӵ�T�е�ǰλ���±�ֵ*/
	int j = 0;
	/*����һ��next����*/
	int next[255];
	get_nextval(T, next);
	/*��iС��S�ĳ�����jС��T�ĳ���ʱ��ѭ������*/
	while (i < strlen(S) && j < strlen(T))
	{
		/*����ĸ���������������BF�㷨������j=0���ж�*/
		if (j == -1 || S[i] == T[j])
		{
			++i;
			++j;
		}
		/*ָ��������¿�ʼƥ��*/
		else
		{
			/*j�˻غ��ʵ�λ�ã�iֵ����*/
			j = next[j];
		}
	}	
	if (j >= strlen(T))
		return (i - strlen(T));
	else
		return -1;
}
