#include<stdio.h>
#include<stdlib.h>

#define MAXVEX 20
#define MAXEDGE 20
#define INFINITY 65535
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef char VertexType;
typedef int EdgeType;

/*�߱���*/
typedef struct EdgeNode
{
	/*�ڽӵ��򣬴洢�ö����Ӧ���±�*/
	int adjvex;
	/*���ڴ洢Ȩֵ�� ���ڷ���ͼ���Բ���Ҫ*/
	int weight;
	/*����ָ����һ���ڽӵ�*/
	struct EdgeNode* next;
}EdgeNode;

/*�������*/
typedef struct VertexNode
{
	/*�������*/
	int in;
	/*�����򣬴洢������Ϣ*/
	int data;
	/*�߱�ͷָ��*/
	EdgeNode* firstedge;
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	/*ͼ�е�ǰ�������ͱ���*/
	int numVertexes, numEdges;
}graphAdjList, * GraphAdjList;

/*����ͼ���ڽӱ�ṹ*/
void CreateALGraph(graphAdjList* G)
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
		scanf("%d", &G->adjList[i].data);
		/*���߱� �ÿ�*/
		G->adjList[i].firstedge = NULL;
		/*����i�������0*/
		G->adjList[i].in = 0;
	}

	/*�����߱�*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("�����(Vi,Vj)�ϵĶ�����ŶԺ�Ȩֵ��\n");
		/*�����(Vi,Vj)�ϵĶ������*/
		scanf("%d %d %d", &i, &j, &w);

		/*���ڴ�����ռ�*/
		/*���ɱ߱���*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*�ڽ����Ϊj*/
		e->adjvex = j;
		/*���ϵ�Ȩֵ*/
		e->weight = w;
		/*��eָ��ָ��ǰ����ָ��Ľ��*/
		e->next = G->adjList[i].firstedge;
		/*����j��ȼ�1 */
		G->adjList[j].in++;
		/*����ǰ�����ָ��ָ��e*/
		G->adjList[i].firstedge = e;
	}
}

int* etv, * ltv;   /*�¼����緢��ʱ�����ٷ���ʱ������*/
int* stack2;       /*���ڴ洢�������е�ջ*/
int top2;          /*����stack2��ָ��*/

Status TopologicalSort(GraphAdjList GL)
{
	EdgeNode* e;
	int i, k, gettop;
	/*����ջָ���±�*/
	int top = 0;
	/*����ͳ���������ĸ���*/
	int count = 0;
	/*��ջ�����Ϊ0�Ķ�����ջ*/
	int* stack = (int*)malloc(sizeof(int) * GL->numVertexes);
	for (i = 0; i < GL->numVertexes; i++)
	{
		if (GL->adjList[i].in == 0)
			stack[++top] = i;
	}
	/*��ʼ��Ϊ0*/
	top2 = 0;
	/*�¼����緢��ʱ��*/
	etv = (int*)malloc(sizeof(int) * GL->numVertexes);
	for (i = 0; i < GL->numVertexes; i++)
		/*��ʼ��Ϊ0*/
		etv[i] = 0;
	/*��ʼ��*/
	stack2 = (int*)malloc(sizeof(int) * GL->numVertexes);
	while (top != 0)
	{
		gettop = stack[top--];
		count++;
		/*�������Ķ������ѹ���������е�ջ*/
		stack2[++top2] = gettop;
		for (e = GL->adjList[gettop].firstedge; e; e = e->next)
		{
			k = e->adjvex;
			if (!(--GL->adjList[k].in))
				stack[++top] = k;
			/*��������¼����緢��ʱ��ֵ*/
			if (etv[k] < (etv[gettop] + e->weight))
				etv[k] = etv[gettop] + e->weight;
		}
	}
	if (count < GL->numVertexes)
		return ERROR;
	else
		return OK;
}

/*��ؼ�·����GLΪ�����������GL�ĸ���ؼ��*/
void CriticalPath(GraphAdjList GL)
{
	EdgeNode* e;
	int i, gettop, k, j;
	/*��������緢��ʱ�����ٷ���ʱ�����*/
	int ete, lte;
	/*���������У���������etv��stack2��ֵ*/
	TopologicalSort(GL);
	/*�¼�������ʱ��*/
	ltv = (int*)malloc(sizeof(int) * GL->numVertexes);
	for (i = 0; i < GL->numVertexes; i++)
		/*��ʼ��ltv*/
		ltv[i] = etv[GL->numVertexes - 1];
	/*����ltv*/
	while (top2 != 0)
	{
		/*���������г�ջ������ȳ�*/
		gettop = stack2[top2--];
		/*��������¼�����ٷ���ʱ��ltvֵ*/
		for (e = GL->adjList[gettop].firstedge; e; e = e->next)
		{
			k = e->adjvex;
			/*��������¼�������ʱ��ltv*/
			if (ltv[gettop] > ltv[k] - e->weight)
				ltv[gettop] = ltv[k] - e->weight;
		}
	}
	/*��ete��lte�͹ؼ��*/
	for (j = 0; j < GL->numVertexes; j++)
	{
		for (e = GL->adjList[j].firstedge; e; e = e->next)
		{
			k = e->adjvex;
			/*����緢��ʱ��*/
			ete = etv[j];
			/*���ٷ���ʱ��*/
			lte = ltv[k] - e->weight;
			if (ete == lte)
				printf("<v%d,v%d> length: %d , ", GL->adjList[j].data, GL->adjList[k].data, e->weight);
		}
	}
}
