#include<stdio.h>
#include<iostream>
#include<string>

typedef char* String;
/* �����Ӵ�T������S�е�pos���ַ�֮���λ�á�
�������ڣ���������ֵΪ0��*/
/* T�ǿգ�1��pos��StrLength(S)�� */
int Index(String S, String T, int pos)
{
	/*i��������S�е�ǰλ���±꣬��pos��Ϊ1* /
	/* ���posλ�ÿ�ʼƥ�� */
	int i = pos;
	/* j�����Ӵ�T�е�ǰλ���±�ֵ */
	int j = 1;
	/* ��iС��S������jС��T�ĳ���ʱѭ�� */
	while (i <= S[0] && j <= T[0])
	{
		/* ����ĸ�������� */
		if (S[i] == T[i])
		{
			i++;
			j++;
		}
		/* ָ��������¿�ʼƥ�� */
		else
		{
			/* i�˻ص��ϴ�ƥ����λ����һλ*/
			i = i - j + 2;
			/* j�˻ص��Ӵ�T����λ*/
			j = 1;
		}
	}

	if (j == T[0])
		return i - T[0];
	else
		return 0;
}

int main()
{
	return 0;
}