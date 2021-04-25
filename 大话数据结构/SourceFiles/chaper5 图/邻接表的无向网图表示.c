#include<stdio.h>
#include<stdlib.h>

/*��󶥵�����Ӧ���û�����*/
#define MAXVEX 100
/*��65535��ʾ����*/
#define INFINITY 65535

/*��������Ӧ���û�����*/
typedef char VertexType;
/*���ϵ�Ȩֵ����Ӧ���û�����*/
typedef int EdgeType;

/*�߱� ���*/
typedef struct EdgeNode
{
	/*�ڽӵ��򣬴洢�ö����Ӧ���±�*/
	int adjvex;
	/*���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ*/
	EdgeType weight;
	/*����ָ����һ���ڽӵ�*/
	struct EdgeNode* next;
}EdgeNode;

/*����� ���*/
typedef struct VertexNode
{
	/*�����򣬴洢������Ϣ*/
	VertexType data;
	/*�߱� ͷָ��*/
	struct EdgeNode* firstedge;
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	/*ͼ�е�ǰ�������ͱ���*/
	int numVertexes, numEdges;
}GraphAdjList;

/*����ͼ���ڽӱ�ṹ*/
void CreateALGraph(GraphAdjList* G)
{
	int i, j, k, w;
	EdgeNode* e;
	printf("���붥�����ͱ�����\n");
	/*���붥�����ͱ���*/
	scanf("%d,%d", &G->numVertexes, &G->numEdges);
	/*���붥����Ϣ�����������*/
	for (i = 0; i < G->numVertexes; i++)
	{
		/*���붥����Ϣ*/
		scanf(&G->adjList[i].data);
		/*���߱� �ÿ�*/
		G->adjList[i].firstedge = NULL;
	}

	/*���� �߱�*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("�����(Vi,Vj)�ϵĶ�����ŶԺ�Ȩֵ��\n");
		/*�����(Vi,Vj)�ϵĶ������*/
		scanf("%d %d %d", &i, &j, &w);

		/*���ڴ�����ռ�*/
		/*���� �߱� ���*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*�ڽ����Ϊj*/
		e->adjvex = j;
		/*�ߵ�Ȩֵ*/
		e->weight = w;
		/*��eָ��ָ��ǰ����ָ��Ľ��*/
		e->next = G->adjList[i].firstedge;
		/*����ǰ�����ָ��ָ��e*/
		G->adjList[i].firstedge = e;

		/*���ڴ�����ռ�*/
		/*���� �߱� ���*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*�ڽ����Ϊi*/
		e->adjvex = i;
		/*�ߵ�Ȩֵ*/
		e->weight = w;
		/*��eָ��ָ��ǰ����ָ��Ľ��*/
		e->next = G->adjList[j].firstedge;
		/*����ǰ�����ָ��ָ��e*/
		G->adjList[j].firstedge = e;
	}
}