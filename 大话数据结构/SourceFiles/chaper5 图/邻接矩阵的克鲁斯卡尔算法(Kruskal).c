#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

/*最大顶点数，应由用户定义*/
#define MAXVEX 40
/*最大边数，应由用户定义*/
#define MAXEDGE 20
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

/*对边集数组Edge结构的定义*/
typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;

void CreateMGraph(MGraph* G)
{
	int i, j, k, w;
	printf("请输入顶点数和边数：");
	/*请输入顶点数和边数*/
	scanf("%d %d", &G->numVertexes, &G->numEdges);
	/*读入顶点信息，建立顶点表*/
	for (i = 0; i < G->numVertexes; i++)
	{
		printf("请输入顶点%d的信息：", i + 1);
		scanf("\n%c", &G->vexs[i]);
	}
	for (i = 0; i < G->numVertexes; i++)
		for (j = 0; j < G->numVertexes; j++)
			/*邻接矩阵的初始化*/
			G->arc[i][j] = INFINITY;
	/*读入numEdges条边，建立邻接矩阵*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("输入边(Vi,Vj)上的下标i，下标j和权w：");
		/*输入边(Vi,Vj)上的下标i，下标j和权w*/
		scanf("%d %d %d", &i, &j, &w);
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
}

/*查找连线顶点的尾部下标*/
int Find(int* parent, int f)
{
	while (parent[f] > 0)
		f = parent[f];
	return f;
}

/*对边集数组进行排序*/
void EdgesSort(Edge edges[MAXVEX], int k)
{
	int i, j;
	/*t用于排序用*/
	Edge t;
	for (i = 0; i < k - 1; i++)
	{
		for (j = i + 1; j < k; j++)
		{
			if (edges[i].weight > edges[j].weight)
			{
				t = edges[i];
				edges[i] = edges[j];
				edges[j] = t;
			}
		}
	}
}

/*Kruskal算法生成最小生成树*/
/*生成最小生成树*/
void MiniSpanTree_Kruskal(MGraph G)
{
	int i, j, k, n, m;
	/*定义边集数组*/
	Edge edges[MAXEDGE];
	/*定义一数组用来判断边与边是否形成环路*/
	int parent[MAXVEX];
	k = 0;
	for (i = 0; i < G.numVertexes; i++)
	{
		for (j = 0; j < G.numVertexes; j++)
		{
			if (G.arc[i][j] < INFINITY)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
	}
	/*将边集数组按权从小到大排序*/
	EdgesSort(edges, k);

	for (i = 0; i < G.numVertexes; i++)
		/*初始化数组值为0*/
		parent[i] = 0;
	/*循环每一条边*/
	for (i = 0; i < G.numEdges; i++)
	{
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);
		/*假如n和m不等，说明此边没有与现有生成树形成环路*/
		if (n != m)
		{
			/*将此边的结尾顶点放入下标为起点的parent中*/
			/*表示此顶点已经在生成树集合中*/
			parent[n] = m;
			printf("(%d,%d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
}



int main()
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Kruskal(G);
	return 0;
}