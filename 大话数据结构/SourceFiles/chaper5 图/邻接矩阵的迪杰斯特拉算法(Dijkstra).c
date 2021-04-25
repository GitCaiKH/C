#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define MAXVEX 20
#define INFINITY 65535

typedef char VertexType;
typedef int EdgeType;
typedef int Patharc[MAXVEX];//用于存储最短路径下标的数组
typedef int ShortPathTable[MAXVEX];//用于存储到各点最短路径的权值和
typedef int Status;
typedef int Boolean;
Boolean visited[MAXVEX];

typedef struct MGraph
{
	VertexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;


/*用邻接矩阵作为存储结构创建无向图*/
void CreateMGraph(MGraph* G)
{
	int i, j, k, w;
	printf("请输入顶点数和边数：");
	scanf("%d %d", &G->numVertexes, &G->numEdges);
	for (i = 0; i < G->numVertexes; i++)
	{
		printf("请输入顶点%d的信息：", i + 1);
		scanf("\n%c", &G->vexs[i]);
	}
	for (i = 0; i < G->numVertexes; i++)
	{
		for (j = 0; j < G->numVertexes; j++)
		{
			G->arc[i][j] = INFINITY;
		}
	}
	for (k = 0; k < G->numEdges; k++)
	{
		printf("请输入边(Vi,Vj)顶点下标i，下标j和权值w：");
		scanf("%d %d", &i, &j, &w);
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
}

/*DijKstra算法，求有向图G的V0顶点到其余顶点V最短路径P[V]及带权长*/
/*P[V]的值为前驱顶点下标，D[V]表示V0到V的最短路径长度和*/
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc* P, ShortPathTable* D)
{
	int v, w, k, min;
	/*final[w] = 1表示求顶点V0至Vw的最短路径*/
	int final[MAXVEX];
	/*初始化数据*/
	for (v = 0; v < G.numVertexes; v++)
	{
		/*全部顶点初始化为未知最短路径状态*/
		final[v] = 0;
		/*将与V0点有连线的顶点加上权值*/
		(*D)[v] = G.arc[v0][v];
		/*初始化路径数组P为-1*/
		(*P)[v] = -1;
	}
	/*v0到v0路径为0*/
	(*D)[v0] = 0;
	/*v0至v0不需要求路径*/
	final[v0] = 1;
	/*开始主循环，每次求得V0到某个顶点的最短路径*/
	for (v = 1; v < G.numVertexes; v++)
	{
		/*当前所知离V0顶点的最近距离*/
		min = INFINITY;
		/*寻找离V0最近的顶点*/
		for (w = 0; w < G.numVertexes; w++)
		{
			if (!final[w] && (*D)[w] < min)
			{
				k = w;
				/*w顶点离V0顶点更近*/
				min = (*D)[w];
			}
		}
		/*将目前找到的最近的顶点置为1*/
		final[k] = 1;
		/*修正当前最短路径及距离*/
		for (w = 0; w < G.numVertexes; w++)
		{
			/*如果经过v顶点的路径比现在这条路径的长度短的话*/
			if (!final[w] && (min + G.arc[k][w] < (*D)[w]))
			{
				/*说明找到了更短的路径，修改D[w]和P[w]*/
				/*修改当前路径长度*/
				(*D)[w] = min + G.arc[k][w];
				(*P)[w] = k;
			}
		}
	}
}