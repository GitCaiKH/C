#include<stdio.h>
#include<stdlib.h>

/*最大顶点数，应由用户定义*/
#define MAXVEX 100
/*用65535表示无穷*/
#define INFINITY 65535

/*顶点类型应由用户定义*/
typedef char VertexType;
/*边上的权值类型应由用户定义*/
typedef int EdgeType;

/*边表 结点*/
typedef struct EdgeNode
{
	/*邻接点域，存储该顶点对应的下标*/
	int adjvex;
	/*用于存储权值，对于非网图可以不需要*/
	EdgeType weight;
	/*链域，指向下一个邻接点*/
	struct EdgeNode* next;
}EdgeNode;

/*顶点表 结点*/
typedef struct VertexNode
{
	/*顶点域，存储顶点信息*/
	VertexType data;
	/*边表 头指针*/
	struct EdgeNode* firstedge;
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	/*图中当前顶点数和边数*/
	int numVertexes, numEdges;
}GraphAdjList;

/*建立图的邻接表结构*/
void CreateALGraph(GraphAdjList* G)
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
		scanf(&G->adjList[i].data);
		/*将边表 置空*/
		G->adjList[i].firstedge = NULL;
	}

	/*建立 边表*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("输入边(Vi,Vj)上的顶点序号对和权值：\n");
		/*输入边(Vi,Vj)上的顶点序号*/
		scanf("%d %d %d", &i, &j, &w);

		/*向内存申请空间*/
		/*生成 边表 结点*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*邻接序号为j*/
		e->adjvex = j;
		/*边的权值*/
		e->weight = w;
		/*将e指针指向当前顶点指向的结点*/
		e->next = G->adjList[i].firstedge;
		/*将当前顶点的指针指向e*/
		G->adjList[i].firstedge = e;

		/*向内存申请空间*/
		/*生成 边表 结点*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*邻接序号为i*/
		e->adjvex = i;
		/*边的权值*/
		e->weight = w;
		/*将e指针指向当前顶点指向的结点*/
		e->next = G->adjList[j].firstedge;
		/*将当前顶点的指针指向e*/
		G->adjList[j].firstedge = e;
	}
}