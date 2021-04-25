#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

#define MAX 100
/*��󶥵�����Ӧ���û�����*/
#define MAXVEX 100
/*��35535����ʾ����*/
#define INFINITY 65535

/*��������Ӧ���û�����*/
typedef char VertexType;
/*���ϵ�Ȩֵ����Ӧ���û�����*/
typedef int EdgeType;

/*Boolean�ǲ������ͣ���ֵ��TRUE��FALSE*/
typedef int Boolean;
Boolean visited[MAXVEX];

/*�߱���*/
typedef struct EdgeNode
{
	/*�ڽӵ���*/
	int adjvex;
	/*���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ*/
	EdgeType weight;
	/*����*/
	struct EdgeNode* next;
}EdgeNode;

/*�������*/
typedef struct VertexNode
{
	/*������,�洢������Ϣ*/
	VertexType data;
	/*�߱�ͷָ��*/
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
	int i, j, k;
	EdgeNode* e;
	printf("�����붥�����ͱ�����\n");
	/*�����붥�����ͱ���*/
	scanf("%d,%d", &G->numVertexes, &G->numEdges);
	/*���붥����Ϣ�����������*/
	for (i = 0; i < G->numVertexes; i++)
	{
		/*���붥����Ϣ*/
		scanf(&G->adjList[i].data);
		/*���߱���Ϊ�ձ�*/
		G->adjList[i].firstedge = NULL;
	}
	/*�����߱�*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("�����(Vi,Vj)�ϵĶ�����ţ�\n");
		/*�����(Vi,Vj)�ϵĶ������*/
		scanf("%d,%d", &i, &j);
		/*���ڴ�����ռ�*/
		/*���ɱ߱���*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*�ڽ����Ϊj*/
		e->adjvex = j;
		/*��eָ��ָ��ǰ����ָ��Ľ��*/
		e->next = G->adjList[i].firstedge;
		/*����ǰ�����ָ��ָ��e*/
		G->adjList[i].firstedge = e;

		/*���ڴ�����ռ�*/
		/*���ɱ߱���*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*�ڽ����Ϊi*/
		e->adjvex = i;
		/*��eָ��ָ��ǰ����ָ��Ľ��*/
		e->next = G->adjList[j].firstedge;
		/*����ǰ�����ָ��ָ��e*/
		G->adjList[j].firstedge = e;
	}
}

/*�ڽӱ��������ȵݹ��㷨*/
void DFS(GraphAdjList GL, int i)
{
	EdgeNode* p;
	visited[i] = TRUE;
	/*��ӡ���㣬Ҳ��������������*/
	printf("%c ", GL.adjList[i].data);
	p = GL.adjList[i].firstedge;
	while (p)
	{
		if (!visited[p->adjvex])
			/*�Է��ʵ��ڽӶ���ݹ����*/
			DFS(GL, p->adjvex);
		p = p->next;
	}
}

/*�ڽӱ����ȱ�������*/
void DFSTraverse(GraphAdjList GL)
{
	int i;
	for (i = 0; i < GL.numVertexes; i++)
		/*��ʼ�����ж���״̬����δ���ʹ�״̬*/
		visited[i] = FALSE;
	for (i = 0; i < GL.numVertexes; i++)
		/*��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ��*/
		if (!visited[i])
			DFS(GL, i);
}
