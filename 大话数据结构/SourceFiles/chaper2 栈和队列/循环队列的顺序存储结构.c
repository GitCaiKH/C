#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 1024
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int QElemType;

typedef struct
{
	QElemType data[MAXSIZE];
	int front;
	int rear;
}SqQueue;

//空队列的初始化
Status InitQueue(SqQueue* Q)
{
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//循环队列求长度
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

//入队操作
Status EnQueue(SqQueue* Q, QElemType e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

//出队操作
Status DeQueue(SqQueue* Q, QElemType* e)
{
	if (Q->front == Q->rear)
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

int main()
{
	return 0;
}