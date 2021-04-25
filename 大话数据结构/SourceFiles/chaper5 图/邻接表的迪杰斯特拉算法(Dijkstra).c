#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define MAXVEX 20
#define MAXEDGE 30
#define INFINITY 65535

typedef int Status;
typedef char VerTexType;
typedef int EdgeType;
typedef int Boolean;
/* 用于存储最短路径下标的数组 */
typedef int Patharc[MAXVEX];
/* 用于存储到各点最短路径的权值和 */
typedef int ShortPathTable[MAXVEX];
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

/* Dijkstra算法，求有向网G的v0顶点到其余顶点v最短路径P[v]及带权长度D[v] */
/* P[v]的值为前驱顶点下标，D[v]表示v0到v的最短路径长度和。 */
void GraphAdjList_ShortestPath_Dijkstra(GraphAdjList GL, int v0, Patharc* P, ShortPathTable* D)
{
	int i, j, k, min;
	EdgeNode* p;
	/* final[j]=1表示已经求得顶点v0至vj的最短路径 */
	Status final[MAXVEX];
	for (i = 0; i < GL.numVertexes; i++)
	{
		/* 全部顶点初始化为未知最短路径状态 */
		final[i] = FALSE;
		/*初始化D和P数组*/
		(*D)[i] = INFINITY;
		/* 初始化路径数组P为-1 */
		(*P)[i] = -1;
	}
	for (p = GL.adjList[v0].firstEdge; p; p = p->next)
	{
		/* 将与v0点有连线的顶点加上权值 */
		(*D)[p->adjvex] = p->weight;
	}
	/*v0至v0路径为0*/
	(*D)[v0] = 0;
	/*v0至v0不需要求路径*/
	final[v0] = TRUE;
	/* 开始主循环，每次求得v0到某个vi顶点的最短路径 */
	for (i = 1; i < GL.numVertexes; i++)
	{
		/* 当前所知离v0顶点的最近距离 */
		min = INFINITY;
		/* 寻找离v0最近的顶点 */
		for (j = 0; j < GL.numVertexes; j++)
		{
			if (!final[j] && (*D)[i] < min)
			{
				/* w顶点离v0顶点更近 */
				min = (*D)[j];
				k = j;
			}
		}
		/* 将目前找到的最近的顶点置为TRUE */
		final[k] = TRUE;
		/* 修正当前最短路径及距离 */
		for (p = GL.adjList[k].firstEdge; p; p = p->next)
		{
			/* 如果经过v顶点的路径比现在这条路径的长度短的话 */
			if (!final[p->adjvex] && (min + p->weight) < (*D)[p->adjvex])
			{
				/* 说明找到了更短的路径，修改D[w]和P[w] */
				/* 修改当前路径长度 */
				(*D)[p->adjvex] = min + p->weight;
				(*P)[p->adjvex] = k;
			}
		}
	}
}

void PrintPath(GraphAdjList GL, int v0, Patharc* P, int i)
{
	if (i != -1)
	{
		PrintPath(GL, v0, P, (*P)[i]);
		printf("V%c->", GL.adjList[i].data);
	}
	else
		printf("最短路径为：V%c->", GL.adjList[v0].data);
}

/*输出路径*/
void Path(GraphAdjList GL, int v0, Patharc* P, ShortPathTable* D)
{
	int i;
	for (i = 0; i < GL.numVertexes; i++)
	{
		/*因为是V0到其它各顶点，所以i等于v0不执行*/
		if (i != v0)
		{
			/*V0不是其他顶点的直接前驱*/
			if ((*P)[i] != -1)
			{
				PrintPath(GL, v0, P, (*P)[i]);
				printf("V%c\n", GL.adjList[i].data);
			}
			else
				printf("最短路径为：V%c->V%c\n", GL.adjList[v0].data, GL.adjList[i].data);
			printf("最短路径长度为：%d\n\n", (*D)[i]);
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
		/*未找到顶点信息，返回-1*/
		return -1;
}

int main()
{
	GraphAdjList GL;
	Patharc P;
	ShortPathTable D;
	VerTexType start;
	int v0;
	CreateALGraph(&GL);
	printf("请输入源点：");
	scanf("\n%c", &start);
	v0 = LocateVex(GL, start);
	if (v0 != -1)
	{
		GraphAdjList_ShortestPath_Dijkstra(GL, v0, &P, &D);
		printf("\n");
		Path(GL, v0, &P, &D);
	}
	else
		/*输入错误，退出程序*/
		exit(ERROR);
	system("pause");
	return 0;
}