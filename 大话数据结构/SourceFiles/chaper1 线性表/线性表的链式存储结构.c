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
/*����LinkList*/
typedef struct Node* LinkList;

//������Ķ�ȡ
Status GetElem(LinkList L, int i, ElemType* e)
{
	int j;
	LinkList p;
	/*L�Ǵ�ͷ��㣬����pָ��ͷ����next*/
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

//������Ĳ���
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

//�������ɾ��
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
	p->next = q->next;   //�൱����p->next=p->next->next;
	*e = q->data;
	free(q);
	return OK;
}

//�������������(ͷ�巨)
void CreateListHead(LinkList* L, int n)
{
	LinkList p;
	int i;
	/*��ʼ�����������*/
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	/*�Ƚ�һ����ͷ���ĵ�����*/
	(*L)->next = NULL;
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

//�������������(β�巨)
void CreateListTail(LinkList* L, int n)
{
	LinkList p, r;
	int i;
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	/*rΪָ��β���Ľ��*/
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

//�����������ɾ��
Status ClearList(LinkList* L)
{
	LinkList p, q;
	p = (*L)->next;
	/*û����β*/
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