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

/*边表结点*/
typedef struct EdgeNode
{
	/*邻接点域，存储该顶点对应的下标*/
	int adjvex;
	/*用于存储权值， 对于非网图可以不需要*/
	int weight;
	/*链域，指向下一个邻接点*/
	struct EdgeNode* next;
}EdgeNode;

/*顶点表结点*/
typedef struct VertexNode
{
	/*顶点入度*/
	int in;
	/*顶点域，存储顶点信息*/
	int data;
	/*边表头指针*/
	EdgeNode* firstedge;
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	/*图中当前顶点数和边数*/
	int numVertexes, numEdges;
}graphAdjList, * GraphAdjList;

/*建立图的邻接表结构*/
void CreateALGraph(graphAdjList* G)
{
	int i, j, k, w;
	EdgeNode* e;
	printf("输入顶点数和边数：\n");
	/*输入顶点数和边数*/
	scanf("%d,%d", &G->numVertexes, &G->numEdges);
	/*读入顶点信息，建立顶点表*/
	for (i = 0; i < G->numVertexes; i++)
	{
		/*输入顶点信息*/
		scanf("%d", &G->adjList[i].data);
		/*将边表 置空*/
		G->adjList[i].firstedge = NULL;
		/*顶点i的入度置0*/
		G->adjList[i].in = 0;
	}

	/*建立边表*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("输入边(Vi,Vj)上的顶点序号对和权值：\n");
		/*输入边(Vi,Vj)上的顶点序号*/
		scanf("%d %d %d", &i, &j, &w);

		/*向内存申请空间*/
		/*生成边表结点*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*邻接序号为j*/
		e->adjvex = j;
		/*边上的权值*/
		e->weight = w;
		/*将e指针指向当前顶点指向的结点*/
		e->next = G->adjList[i].firstedge;
		/*顶点j入度加1 */
		G->adjList[j].in++;
		/*将当前顶点的指针指向e*/
		G->adjList[i].firstedge = e;
	}
}

int* etv, * ltv;   /*事件最早发生时间和最迟发生时间数组*/
int* stack2;       /*用于存储拓扑序列的栈*/
int top2;          /*用于stack2的指针*/

Status TopologicalSort(GraphAdjList GL)
{
	EdgeNode* e;
	int i, k, gettop;
	/*用于栈指针下标*/
	int top = 0;
	/*用于统计输出顶点的个数*/
	int count = 0;
	/*建栈将入度为0的顶点入栈*/
	int* stack = (int*)malloc(sizeof(int) * GL->numVertexes);
	for (i = 0; i < GL->numVertexes; i++)
	{
		if (GL->adjList[i].in == 0)
			stack[++top] = i;
	}
	/*初始化为0*/
	top2 = 0;
	/*事件最早发生时间*/
	etv = (int*)malloc(sizeof(int) * GL->numVertexes);
	for (i = 0; i < GL->numVertexes; i++)
		/*初始化为0*/
		etv[i] = 0;
	/*初始化*/
	stack2 = (int*)malloc(sizeof(int) * GL->numVertexes);
	while (top != 0)
	{
		gettop = stack[top--];
		count++;
		/*将弹出的顶点序号压入拓扑序列的栈*/
		stack2[++top2] = gettop;
		for (e = GL->adjList[gettop].firstedge; e; e = e->next)
		{
			k = e->adjvex;
			if (!(--GL->adjList[k].in))
				stack[++top] = k;
			/*求各顶点事件最早发生时间值*/
			if (etv[k] < (etv[gettop] + e->weight))
				etv[k] = etv[gettop] + e->weight;
		}
	}
	if (count < GL->numVertexes)
		return ERROR;
	else
		return OK;
}

/*求关键路径，GL为有向网，输出GL的各项关键活动*/
void CriticalPath(GraphAdjList GL)
{
	EdgeNode* e;
	int i, gettop, k, j;
	/*声明活动最早发生时间和最迟发生时间变量*/
	int ete, lte;
	/*求拓扑序列，计算数组etv和stack2的值*/
	TopologicalSort(GL);
	/*事件最晚发生时间*/
	ltv = (int*)malloc(sizeof(int) * GL->numVertexes);
	for (i = 0; i < GL->numVertexes; i++)
		/*初始化ltv*/
		ltv[i] = etv[GL->numVertexes - 1];
	/*计算ltv*/
	while (top2 != 0)
	{
		/*将拓扑序列出栈，后进先出*/
		gettop = stack2[top2--];
		/*求各顶点事件的最迟发生时间ltv值*/
		for (e = GL->adjList[gettop].firstedge; e; e = e->next)
		{
			k = e->adjvex;
			/*求各顶点事件最晚发生时间ltv*/
			if (ltv[gettop] > ltv[k] - e->weight)
				ltv[gettop] = ltv[k] - e->weight;
		}
	}
	/*求ete，lte和关键活动*/
	for (j = 0; j < GL->numVertexes; j++)
	{
		for (e = GL->adjList[j].firstedge; e; e = e->next)
		{
			k = e->adjvex;
			/*活动最早发生时间*/
			ete = etv[j];
			/*活动最迟发生时间*/
			lte = ltv[k] - e->weight;
			if (ete == lte)
				printf("<v%d,v%d> length: %d , ", GL->adjList[j].data, GL->adjList[k].data, e->weight);
		}
	}
}
