#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1024

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int SElemType;
typedef int Status;

typedef struct StackNode
{
	SElemType data;
	struct StackNode* next;
}StackNode, * LinkStackPtr;

typedef struct LinkStack
{
	LinkStackPtr top;
	int count;
}LinkStack;

//入栈操作
Status Push(LinkStack* S, SElemType e)
{
	LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
	s->data = e;
	s->next = S->top;
	S->top = s;
	S->count++;
	return OK;
}

//出栈操作
Status Pop(LinkStack* S, SElemType* e)
{
	LinkStackPtr p;
	if (StackEmpty(*S))
		return ERROR;
	*e = S->top->data;
	p = S->top;
	S->top = S->top->next;
	free(p);
	S->count--;
	return OK;
}

int main()
{
	return 0;
}