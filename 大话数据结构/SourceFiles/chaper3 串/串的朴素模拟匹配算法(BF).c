#include<stdio.h>
#include<iostream>
#include<string>

typedef char* String;
/* 返回子串T在主串S中第pos个字符之后的位置。
若不存在，则函数返回值为0。*/
/* T非空，1≤pos≤StrLength(S)。 */
int Index(String S, String T, int pos)
{
	/*i用于主串S中当前位置下标，若pos不为1* /
	/* 则从pos位置开始匹配 */
	int i = pos;
	/* j用于子串T中当前位置下标值 */
	int j = 1;
	/* 若i小于S长度且j小于T的长度时循环 */
	while (i <= S[0] && j <= T[0])
	{
		/* 两字母相等则继续 */
		if (S[i] == T[i])
		{
			i++;
			j++;
		}
		/* 指针后退重新开始匹配 */
		else
		{
			/* i退回到上次匹配首位的下一位*/
			i = i - j + 2;
			/* j退回到子串T的首位*/
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