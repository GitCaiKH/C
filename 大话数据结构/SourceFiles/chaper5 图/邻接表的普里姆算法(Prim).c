#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define MAXVEX 20
#define MAXSIZE 20
#define INFINITY 65535

typedef int Status;
typedef char VerTexType;
typedef int EdgeType;
typedef int Boolean;
Boolean visited[MAXVEX];

typedef struct EdgeNode
{
	int adjvex;
	EdgeType weight;
	struct EdgeNode* next;
}EdgeNode;

typedef struct VertexNode
{
	VerTexType data;
	EdgeNode* firstEdge;
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes, numEdges;
}GraphAdjList;

/*����ͼ���ڽӱ�*/
void CreateALGraph(GraphAdjList* GL)
{
	int i, j, k;
	EdgeType w;
	EdgeNode* e;
	printf("���붥�㶥�����ͱ���: ");
	/*���붥�㶥�����ͱ���*/
	scanf("%d %d", &GL->numVertexes, &GL->numEdges);
	/*���붥����Ϣ�����������*/
	for (i = 0; i < GL->numVertexes; i++)
	{
		printf("�����붥�� %d ����Ϣ: ", i + 1);
		/*���붥����Ϣ*/
		scanf("\n%c", &GL->adjList[i].data);
		/*���߱���Ϊ�ձ�*/
		GL->adjList[i].firstEdge = NULL;
	}
	/*�����߱�*/
	for (k = 0; k < GL->numEdges; k++)
	{
		printf("�����(vi,vj)�ϵĶ�����ŶԺ�Ȩֵ: ");
		/* �����(vi,vj)�ϵĶ������ */
		scanf("%d %d %d", &i, &j, &w);
		/* ���ڴ�����ռ䣬���ɱ߱��� */
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/* �ڽ����Ϊj */
		e->adjvex = j;
		/*�ߵ�Ȩֵ*/
		e->weight = w;
		/* ��eָ��ָ��ǰ����ָ��Ľ�� */
		e->next = GL->adjList[i].firstEdge;
		/* ����ǰ�����ָ��ָ��e */
		GL->adjList[i].firstEdge = e;

		/* ���ڴ�����ռ䣬���ɱ߱��� */
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/* �ڽ����Ϊi*/
		e->adjvex = i;
		/*�ߵ�Ȩֵ*/
		e->weight = w;
		/* ��eָ��ָ��ǰ����ָ��Ľ�� */
		e->next = GL->adjList[j].firstEdge;
		/* ����ǰ�����ָ��ָ��e */
		GL->adjList[j].firstEdge = e;
	}
}

/*�ڽӱ�ʵ��Prim�㷨��������ϡ��ͼ*/
void GraphAdjList_MiniSpanTree_Prim(GraphAdjList GL, int start)
{
	EdgeNode* p;
	int i, j, k, min;
	int adjvex[MAXVEX];
	int lowcost[MAXVEX];
	int mincost = 0;
	lowcost[start] = start;
	adjvex[start] = start;
	visited[start] = TRUE;
	for (i = 0; i < GL.numVertexes; i++)
	{
		if (i != start)
		{
			visited[i] = FALSE;
			lowcost[i] = INFINITY;
			adjvex[i] = start;
		}
	}
    for(p = GL.adjList[start].firstEdge; p; p = p->next)
	{
		lowcost[p->adjvex] = p->weight;
		adjvex[p->adjvex] = start;
	}

	for (i = 1; i < GL.numVertexes; i++)
	{
		min = INFINITY;
		k = start;
		for (j = 0; j < GL.numVertexes; j++)
		{
			if (!visited[j] && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
		}
		mincost += min; //����СȨֵ��

		printf("(%c,%c) ", GL.adjList[adjvex[k]].data, GL.adjList[k].data);
		visited[k] = TRUE;
		for (p = GL.adjList[k].firstEdge; p; p = p->next)
		{
			if (!visited[p->adjvex] && p->weight < lowcost[p->adjvex])
			{
				lowcost[p->adjvex] = p->weight;
				adjvex[p->adjvex] = k;
			}
		}
	}
}

/*������������Ϣ��Ӧ���ڽӱ��е�λ�ã������ڽӱ���λ���±�*/
int LocateVex(GraphAdjList GL, VerTexType start)
{
	int i;
	for (i = 0; i < GL.numVertexes; i++)
	{
		if (start == GL.adjList[i].data)
			return i;
	}
	if (i >= GL.numVertexes)
		return -1;
}

/*����������*/
int main()
{
	GraphAdjList GL;
	CreateALGraph(&GL);
	VerTexType start;
	printf("��������㣺");
	scanf("\n%c", &start);
	start = LocateVex(GL, start);
	if (start != -1)
		GraphAdjList_MiniSpanTree_Prim(GL, start);
	else
		exit(ERROR);
	return 0;
}