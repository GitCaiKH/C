#include<stdio.h>
#include<stdlib.h>

/*���ĺ��ӱ�ʾ���ṹ����*/
#define MAX_TREE_SIZE 100
typedef int TElemType;

/*���ӽ��*/
typedef struct CTNode
{
	int child;
	struct CTNode* next;
}*ChildPtr;

/*��ͷ�ṹ*/
typedef struct
{
	TElemType data;
	ChildPtr firstchild;
}CTBox;

/*���ṹ*/
typedef struct
{
	/*���ṹ*/
	CTBox nodes[MAX_TREE_SIZE];
	/*����λ�úͽ����*/
	int r, n;
}CTree;