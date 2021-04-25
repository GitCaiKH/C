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

/*建立图的邻接表*/
void CreateALGraph(GraphAdjList* GL)
{
	int i, j, k;
	EdgeType w;
	EdgeNode* e;
	printf("输入顶点顶点数和边数: ");
	/*输入顶点顶点数和边数*/
	scanf("%d %d", &GL->numVertexes, &GL->numEdges);
	/*读入顶点信息，建立顶点表*/
	for (i = 0; i < GL->numVertexes; i++)
	{
		printf("请输入顶点 %d 的信息: ", i + 1);
		/*输入顶点信息*/
		scanf("\n%c", &GL->adjList[i].data);
		/*将边表置为空表*/
		GL->adjList[i].firstEdge = NULL;
	}
	/*建立边表*/
	for (k = 0; k < GL->numEdges; k++)
	{
		printf("输入边(vi,vj)上的顶点序号对和权值: ");
		/* 输入边(vi,vj)上的顶点序号 */
		scanf("%d %d %d", &i, &j, &w);
		/* 向内存申请空间，生成边表结点 */
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/* 邻接序号为j */
		e->adjvex = j;
		/*边的权值*/
		e->weight = w;
		/* 将e指针指向当前顶点指向的结点 */
		e->next = GL->adjList[i].firstEdge;
		/* 将当前顶点的指针指向e */
		GL->adjList[i].firstEdge = e;

		/* 向内存申请空间，生成边表结点 */
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/* 邻接序号为i*/
		e->adjvex = i;
		/*边的权值*/
		e->weight = w;
		/* 将e指针指向当前顶点指向的结点 */
		e->next = GL->adjList[j].firstEdge;
		/* 将当前顶点的指针指向e */
		GL->adjList[j].firstEdge = e;
	}
}

/*邻接表实现Prim算法，适用于稀疏图*/
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
		mincost += min; //求最小权值和

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

/*找输入的起点信息对应在邻接表中的位置，返回邻接表中位置下标*/
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

/*主函数测试*/
int main()
{
	GraphAdjList GL;
	CreateALGraph(&GL);
	VerTexType start;
	printf("请输入起点：");
	scanf("\n%c", &start);
	start = LocateVex(GL, start);
	if (start != -1)
		GraphAdjList_MiniSpanTree_Prim(GL, start);
	else
		exit(ERROR);
	return 0;
}