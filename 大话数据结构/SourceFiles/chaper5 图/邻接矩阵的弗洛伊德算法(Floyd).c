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
typedef int Pathmatirx[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
typedef int Status;
typedef int Boolean;
Boolean visited[MAXVEX];

typedef struct
{
	VertexType vexes[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVextexes, numEdges;
}MGraph;

void CreateMGraph(MGraph G)
{
	int i, j, k, w;
	printf("请输入顶点数和边数：");
	scanf("%d %d", &G.numVextexes, &G.numEdges);
	for (i = 0; i < G.numVextexes; i++)
	{
		printf("请输入顶点%d的信息：", i + 1);
		scanf("\n%c", &G.vexes[i]);

	}
	for (i = 0; i < G.numVextexes; i++)
	{
		for (j = 0; j < G.numVextexes; j++)
		{
			G.arc[i][j] = INFINITY;
		}
	}
	for (k = 0; k < G.numEdges; k++)
	{
		printf("请输入边(Vi,Vj)的下标i，下标j和权值w：");
		scanf("%d %d %d", &i, &j, &w);
		G.arc[i][j] = w;
		G.arc[j][i] = G.arc[i][j];
	}
}

/*Floyd算法，求网图G中各顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w]*/
void ShortestPATH_Floyd(MGraph G, Pathmatirx* P, ShortPathTable* D)
{
	int v, w, k;
	/*初始化D与P*/
	for (v = 0; v < G.numVextexes; v++)
	{
		for (w = 0; w < G.numVextexes; w++)
		{
			/*D[v][w]值即为对应点间的权值*/
			(*D)[v][w] = G.arc[v][w];
			/*初始化P*/
			(*P)[v][w] = w;
		}
	}
	for (k = 0; k < G.numVextexes; k++)
	{
		for (v = 0; v < G.numVextexes; v++)
		{
			for (w = 0; w < G.numVextexes; w++)
			{
				/*(*D)[v][w]表示从顶点v到顶点w的权值*/
				if ((*D)[v][k] + (*D)[k][w] < (*D)[v][w])
				{
					/*如果经过下标为k顶点路径比原两点间路径更短*/
					/*将当前两点间权值设为更小的一个*/
					(*D)[v][w] = (*D)[v][k] + (*D)[k][w];
					/*路径设置经过下标为k的顶点*/
					(*P)[v][w] = (*P)[v][k];
				}
			}
		}
	}
}