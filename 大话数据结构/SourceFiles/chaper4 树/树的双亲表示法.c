#include<stdio.h>
#include<stdlib.h>

/*����˫�ױ�ʾ�����ṹ����*/
#define MAX_TREE_SIZE 100
/*�������������ͣ�Ŀǰ�ݶ�Ϊ����*/
typedef int TElemType;
/*���ṹ*/
typedef struct PTNode
{
	/*�������*/
	TElemType data;
	/*˫��λ��*/
	int parent;
}PTNode;

/*���ṹ*/
typedef struct
{
	/*�������*/
	PTNode nodes[MAX_TREE_SIZE];
	/*����λ�úͽ����*/
	int r, n;
}PTree;