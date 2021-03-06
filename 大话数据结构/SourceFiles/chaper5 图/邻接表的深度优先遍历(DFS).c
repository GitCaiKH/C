#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

#define MAX 100
/*最大顶点数，应由用户定义*/
#define MAXVEX 100
/*用35535来表示无穷*/
#define INFINITY 65535

/*顶点类型应由用户定义*/
typedef char VertexType;
/*边上的权值类型应由用户定义*/
typedef int EdgeType;

/*Boolean是布尔类型，其值是TRUE或FALSE*/
typedef int Boolean;
Boolean visited[MAXVEX];

/*边表结点*/
typedef struct EdgeNode
{
	/*邻接点域*/
	int adjvex;
	/*用于存储权值，对于非网图可以不需要*/
	EdgeType weight;
	/*链域*/
	struct EdgeNode* next;
}EdgeNode;

/*顶点表结点*/
typedef struct VertexNode
{
	/*顶点域,存储顶点信息*/
	VertexType data;
	/*边表头指针*/
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
	int i, j, k;
	EdgeNode* e;
	printf("请输入顶点数和边数：\n");
	/*请输入顶点数和边数*/
	scanf("%d,%d", &G->numVertexes, &G->numEdges);
	/*读入顶点信息，建立顶点表*/
	for (i = 0; i < G->numVertexes; i++)
	{
		/*输入顶点信息*/
		scanf(&G->adjList[i].data);
		/*将边表置为空表*/
		G->adjList[i].firstedge = NULL;
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
		/*将当前顶点的指针指向e*/
		G->adjList[i].firstedge = e;

		/*向内存申请空间*/
		/*生成边表结点*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*邻接序号为i*/
		e->adjvex = i;
		/*将e指针指向当前顶点指向的结点*/
		e->next = G->adjList[j].firstedge;
		/*将当前顶点的指针指向e*/
		G->adjList[j].firstedge = e;
	}
}

/*邻接表的深度优先递归算法*/
void DFS(GraphAdjList GL, int i)
{
	EdgeNode* p;
	visited[i] = TRUE;
	/*打印顶点，也可以作其他操作*/
	printf("%c ", GL.adjList[i].data);
	p = GL.adjList[i].firstedge;
	while (p)
	{
		if (!visited[p->adjvex])
			/*对访问的邻接顶点递归调用*/
			DFS(GL, p->adjvex);
		p = p->next;
	}
}

/*邻接表的深度遍历操作*/
void DFSTraverse(GraphAdjList GL)
{
	int i;
	for (i = 0; i < GL.numVertexes; i++)
		/*初始化所有顶点状态都是未访问过状态*/
		visited[i] = FALSE;
	for (i = 0; i < GL.numVertexes; i++)
		/*对未访问过的顶点调用DFS，若是连通图，只会执行一次*/
		if (!visited[i])
			DFS(GL, i);
}
