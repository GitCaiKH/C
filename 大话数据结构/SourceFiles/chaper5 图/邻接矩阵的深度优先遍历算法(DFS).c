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

typedef struct
{
	/*顶点表*/
	VertexType vexs[MAXVEX];
	/*邻接矩阵，可看作边表*/
	EdgeType arc[MAXVEX][MAXVEX];
	/*图中当前的顶点数和边数*/
	int numVertexes, numEdges;
}MGraph;

/*建立无向网图的邻接矩阵表示*/
void CreateMGraph(MGraph* G)
{
	int i, j, k, w;
	pirntf("输入顶点数和边数：\n");
	/*输入顶点数和边数*/
	scanf("%d,%d", &G->numVertexes, &G->numVertexes);
	/*读入顶点信息，建立顶点表*/
	for (i = 0; i < G->numVertexes; i++)
		scanf(&G->vexs[i]);
	for (i = 0; i < G->numVertexes; i++)
		for (j = 0; j < G->numVertexes; j++)
			/*邻接矩阵的初始化*/
			G->arc[i][j] = INFINITY;
	/*读入numEdges条边，建立邻接矩阵*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("输入边(Vi,Vj)上的下标i，下标j和权w：\n");
		/*输入边(Vi,Vj)上的下标i，下标j和权w*/
		scanf("%d,%d,%d", &i, &j, &w);
		G->arc[i][j] = w;
		/*因为同无向图，矩阵的对称*/
		G->arc[j][i] = G->arc[i][j];
	}
}

/*邻接矩阵的深度优先递归算法*/
void DFS(MGraph G, int i)
{
	int j;
	visited[i] = TRUE;
	/*打印顶点，也可以作其他操作*/
	printf("%c ", G.vexs[i]);
	for (j = 0; j < G.numVertexes; j++)
		if (G.arc[i][j] == 1 && !visited[j])
			/*对为访问的邻接顶点递归调用*/
			DFS(G, j);
}

/*邻接矩阵的深度遍历操作*/
void DFSTraverse(MGraph G)
{
	int i;
	for (i = 0; i < G.numVertexes; i++)
		/*初始化所有顶点状态都是未访问过的状态*/
		visited[i] = FALSE;
	for (i = 0; i < G.numVertexes; i++)
		/*对未访问过的顶点调用DFS，若是连通图，只会执行一次*/
		if (!visited[i])
			DFS(G, i);
}