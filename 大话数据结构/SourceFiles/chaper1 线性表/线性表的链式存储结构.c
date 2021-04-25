#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FLASE 0

typedef int Status;
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	struct Node* next;
}Node;
/*定义LinkList*/
typedef struct Node* LinkList;

//单链表的读取
Status GetElem(LinkList L, int i, ElemType* e)
{
	int j;
	LinkList p;
	/*L是带头结点，所以p指向头结点的next*/
	p = L->next;
	j = 1;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return ERROR;
	*e = p->data;
	return OK;
}

//单链表的插入
Status ListInsert(LinkList* L, int i, ElemType e)
{
	int j;
	LinkList p, s;
	p = *L;
	j = 1;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return ERROR;
	s = (LinkList)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

//单链表的删除
Status ListDelete(LinkList* L, int i, ElemType* e)
{
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next && j < i)
	{
		p = p->next;
		j++;
	}
	if (!(p->next) || j > i)
		return ERROR;
	q = p->next;
	p->next = q->next;   //相当于令p->next=p->next->next;
	*e = q->data;
	free(q);
	return OK;
}

//单链表的整表创建(头插法)
void CreateListHead(LinkList* L, int n)
{
	LinkList p;
	int i;
	/*初始化随机数种子*/
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	/*先建一个带头结点的单链表*/
	(*L)->next = NULL;
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

//单链表的整表创建(尾插法)
void CreateListTail(LinkList* L, int n)
{
	LinkList p, r;
	int i;
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	/*r为指向尾部的结点*/
	r = *L;
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		p->next = NULL;
		r->next = p;
		r = p;
	}
}

//单链表的整表删除
Status ClearList(LinkList* L)
{
	LinkList p, q;
	p = (*L)->next;
	/*没到表尾*/
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
	return OK;
}

int main()
{
	return 0;
}