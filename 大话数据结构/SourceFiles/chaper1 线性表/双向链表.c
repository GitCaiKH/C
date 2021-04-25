#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FLASE 0

typedef int Status;
typedef int ElemType;

typedef struct DulNode
{
	ElemType data;
	struct DulNode* prior;   /*ֱ��ǰ��ָ��*/
	struct DulNode* next;    /*ֱ�Ӻ��ָ��*/
}DulNode, * DuLinkList;

//˫������Ĳ���
Status DuListInsert(DuLinkList* L, int i, ElemType e)
{
	int j;
	DuLinkList p, s;
	p = *L;
	j = 1;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return ERROR;
	s = (DuLinkList)malloc(sizeof(DulNode));
	s->data = e;

	s->prior = p;
	s->next = p->next;
	p->next->prior = s;
	p->next = s;
	return OK;
}

//˫�������ɾ��
Status ListDelete(DuLinkList* L, int i, ElemType* e)
{
	int j;
	DuLinkList p, q;
	p = *L;
	j = 1;
	while (p->next && j < i)
	{
		p = p->next;
		j++;
	}
	if (!(p->next) || j > i)
		return ERROR;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}