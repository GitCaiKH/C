#include<stdio.h>
#include<stdlib.h>

typedef int TElemType;

typedef struct CSNode
{
	TElemType data;
	struct CSNode* firstchild, * rightsib;
}CSNode, * CSTree;