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

typedef struct
{
	/*顶点表*/
	VertexType vexs[MAXVEX];
	/*邻接矩阵，可看作边表*/
	EdgeType arc[MAXVEX][MAXVEX];
	/*图中当前的顶点数和边数*/
	int numVertexes, numEdges;
}MGraph;

void CreateMGraph(MGraph* G)
{
	int i, j, k, w;
	printf("输入顶点数和边数:\n");
	/*输入顶点数和边数*/
	scanf("%d,%d", &G->numVertexes, &G->numEdges);
	/*读入顶点信息，建立顶点表*/
	for (i = 0; i < G->numVertexes; i++)
		scanf("%c", &G->vexs[i]);
	for (i = 0; i < G->numVertexes; i++)
		for (j = 0; j < G->numVertexes; j++)
			/*邻接矩阵初始化*/
			G->arc[i][j] = INFINITY;
	/*读入numEdges条边，建立邻接矩阵*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("输入边(Vi,Vj)上的下标i，下标j和权w:\n");
		/*输入边(Vi,Vj)上的权*/
		scanf("%d,%d,%d", &i, &j, &w);
		G->arc[i][j] = w;
		/*因为是无向图，矩阵对称*/
		G->arc[i][j] = G->arc[i][j];
	}
}