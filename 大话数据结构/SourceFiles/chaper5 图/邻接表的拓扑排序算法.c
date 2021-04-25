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
	int i, j, k;
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
		printf("输入边(Vi,Vj)上的顶点序号：\n");
		/*输入边(Vi,Vj)上的顶点序号*/
		scanf("%d,%d", &i, &j);

		/*向内存申请空间*/
		/*生成边表结点*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*邻接序号为j*/
		e->adjvex = j;
		/*将e指针指向当前顶点指向的结点*/
		e->next = G->adjList[i].firstedge;
		/*顶点j入度加1 */
		G->adjList[j].in++;
		/*将当前顶点的指针指向e*/
		G->adjList[i].firstedge = e;
	}
}

Status TopologicalSort(GraphAdjList GL)
{
	EdgeNode* e;
	int i, k, gettop;
	/*用于栈指针下标*/
	int top = 0;
	/*用于统计输出顶点的个数*/
	int count = 0;
	/*建栈，用来存储入度为0的顶点*/
	int* stack;
	stack = (int*)malloc(sizeof(int) * GL->numVertexes);
	for (i = 0; i < GL->numVertexes; i++)
	{
		if (GL->adjList[i].in == 0)
			/*将入度为0的顶点入栈*/
			stack[++top] = i;
	}
	while (top != 0)
	{
		/*出栈*/
		gettop = stack[top--];
		/*打印此顶点*/
		printf("%d -> ", GL->adjList[gettop].data);
		/*统计输出顶点数*/
		count++;
		/*对此顶点弧表遍历*/
		for (e = GL->adjList[gettop].firstedge; e; e = e->next)
		{
			k = e->adjvex;
			/*将k号顶点邻接点的入度减1 */
			if (!(GL->adjList[k].in))
				/*若为0则入栈，以便于下次循环输出*/
				stack[++top] = k;
		}
	}
	/*如果count小于顶点数，说明存在环*/
	if (count < GL->numVertexes)
		return ERROR;
	else
		return OK;
}