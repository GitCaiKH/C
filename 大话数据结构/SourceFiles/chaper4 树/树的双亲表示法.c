#include<stdio.h>
#include<stdlib.h>

/*树的双亲表示法结点结构定义*/
#define MAX_TREE_SIZE 100
/*树结点的数据类型，目前暂定为整型*/
typedef int TElemType;
/*结点结构*/
typedef struct PTNode
{
	/*结点数据*/
	TElemType data;
	/*双亲位置*/
	int parent;
}PTNode;

/*树结构*/
typedef struct
{
	/*结点数组*/
	PTNode nodes[MAX_TREE_SIZE];
	/*根的位置和结点数*/
	int r, n;
}PTree;