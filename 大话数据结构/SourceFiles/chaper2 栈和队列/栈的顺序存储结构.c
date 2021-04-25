#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1024

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int SElemType;
typedef int Status;

typedef struct
{
	SElemType data[MAXSIZE];
	int top;
}SqStack;

//��ջ����
Status Push(SqStack* S, SElemType e)
{
	if (S->top == MAXSIZE - 1)
	{
		return ERROR;
	}
	S->top++;
	S->data[S->top] = e;
	return OK;
}

//��ջ����
Status Pop(SqStack* S, SElemType* e)
{
	if (S->top == -1)
		return ERROR;
	*e = S->data[S->top];
	S->top--;
	return OK;
}

int main()
{
	return 0;
}