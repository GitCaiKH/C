#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

/*最大顶点数，应由用户定义*/
#define MAXVEX 20
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

/*Prim算法生成最小生成树*/
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	/*保存相关顶点下标*/
	int adjvex[MAXVEX];
	/*保存相关顶点间边的权值*/
	int lowcost[MAXVEX];
	/*初始化第一个权值为0，即v0加入生成树*/
	/*lowcost的值为0，在这里就是此下标的顶点已经加入生成树*/
	lowcost[0] = 0;
	/*初始化第一个顶点下标为0*/
	adjvex[0] = 0;
	/*循环除下标为0外的全部顶点*/
	for (i = 1; i < G.numVertexes; i++)
	{
		/*将v0顶点与之有边的权值存入数组*/
		lowcost[i] = G.arc[0][i];
		/*初始化都为v0的下标*/
		adjvex[i] = 0;
	}

	for (i = 1; i < G.numVertexes; i++)
	{
		/*初始化最小权值为∞，*/
		/*通常设置为不可能的大数字如32767，65535等*/
		min = INFINITY;
		j = 1;
		k = 0;
		/*循环全部顶点*/
		while (j < G.numVertexes)
		{
			/*如果权值不为0且权值小于min*/
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				/*则让当前权值成为最小值*/
				min = lowcost[j];
				/*将当前最小值的下标存入k*/
				k = j;
			}
			j++;
		}

		/*打印当前顶点边中权值最小边*/
		/*输出符合条件的边，adjvex[k]中存储的正是具有最小权值边的起点*/
		printf("(%d,%d) ", adjvex[k], k);
		/*将当前顶点的权值设置为0，表示此顶点已经完成任务*/
		lowcost[k] = 0;
		/*循环所有顶点*/
		for (j = 1; j < G.numVertexes; j++)
		{
			/*节点k成功加入生成树了，需要更新其余节点到节点集合u的距离，是更新*/
			/*若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值*/
			if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
			{
				/*将较小权值存入lowcost*/
				lowcost[j] = G.arc[k][j];
				/*将下标为k的顶点存入adjvex*/
				adjvex[j] = k;
			}
		}
	}
}

int main()
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Prim(G);
	return 0;
}