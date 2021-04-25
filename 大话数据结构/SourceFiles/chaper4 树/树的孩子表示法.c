#include<stdio.h>
#include<stdlib.h>

/*树的孩子表示法结构定义*/
#define MAX_TREE_SIZE 100
typedef int TElemType;

/*孩子结点*/
typedef struct CTNode
{
	int child;
	struct CTNode* next;
}*ChildPtr;

/*表头结构*/
typedef struct
{
	TElemType data;
	ChildPtr firstchild;
}CTBox;

/*树结构*/
typedef struct
{
	/*结点结构*/
	CTBox nodes[MAX_TREE_SIZE];
	/*根的位置和结点数*/
	int r, n;
}CTree;