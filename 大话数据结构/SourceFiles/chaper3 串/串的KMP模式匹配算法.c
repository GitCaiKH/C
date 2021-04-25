#include<stdio.h>
#include<string.h>

typedef char* String;
void get_nextval(String T, int* nextval)
{
	int j, k;
	j = 0;
	k = -1;
	nextval[0] = -1;
	/*此处T[0]表示串T的长度*/
	while (j < strlen(T) - 1)
	{
		/*T[i]表示后缀的单个字符*/
		/*T[j]表示前缀的单个字符*/
		if (k == -1 || T[j] == T[k])
		{
			++j;
			++k;
			/*若当前字符和前缀字符不同*/
			if (T[j] != T[k])
				nextval[j] = k;
			else
				/*如果当前缀字符相同，刚将前缀字符的nextval值赋值给nextval在i位置的值*/
				nextval[j] = nextval[k];
		}
		else
			/*若字符不相同，则j值回溯*/
			k = nextval[k];
	}
}

int Index_KMP(String S, String T, int pos)
{
	/*i用于主串S当前位置下标值，若pos不为1*/
	/*则从pos位置开始匹配*/
	int i = pos - 1;
	/*j用于子串T中当前位置下标值*/
	int j = 0;
	/*定义一个next数组*/
	int next[255];
	get_nextval(T, next);
	/*若i小于S的长度且j小于T的长度时，循环继续*/
	while (i < strlen(S) && j < strlen(T))
	{
		/*两字母相等则继续，相对于BF算法增加了j=0的判断*/
		if (j == -1 || S[i] == T[j])
		{
			++i;
			++j;
		}
		/*指针后退重新开始匹配*/
		else
		{
			/*j退回合适的位置，i值不变*/
			j = next[j];
		}
	}	
	if (j >= strlen(T))
		return (i - strlen(T));
	else
		return -1;
}
