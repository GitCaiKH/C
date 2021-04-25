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

/*对边集数组Edge结构的定义*/
typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;


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

/*邻接表实现Prim算法，适用于稀疏图*/
void GraphAdjList_MiniSpanTree_Kruskal(GraphAdjList GL)
{
	EdgeNode* p;
	int i, x, k, n, m;
	Status flag;
	/*定义边集数组*/
	Edge edges[MAXEDGE];
	/*定义一数组用来判断边与边是否形成环路*/
	int parent[MAXVEX];
	k = 0;
	for (i = 0; i < GL.numVertexes; i++)
	{
		for (p = GL.adjList[i].firstEdge; p; p = p->next)
		{
			/*无向图判断V(i)到V(p->adjvex)和V(p->adjvex)到V(i)算一次*/
			flag = TRUE;
			/*遍历已存在的边集数组*/
			for (x = 0; x < k; x++)
			{

				if (edges[x].begin == p->adjvex && edges[x].end == i)
				{
					/*无向图中如果边集数组已经存在一条V(i)到V(p->adjvex)的边则flag为FALSE*/
					flag = FALSE;
					break;
				}
			}
			if (flag == TRUE)
			{
				/*起点为i，终点为p->adjvex，权值是p->weight*/
				edges[k].begin = i;       
				edges[k].end = p->adjvex;
				edges[k].weight = p->weight;
				k++;
			}
		}
	}
	/*将边集数组按权从小到大排序*/
	EdgesSort(edges, k);
	for (i = 0; i < GL.numVertexes; i++)
		/*初始化数组值为0*/
		parent[i] = 0;
	/*循环每一条边*/
	for (i = 0; i < GL.numEdges; i++)
	{
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);
		/*假如n和m不等，说明此边没有与现有生成树形成环路*/
		if (n != m)
		{
			/*将此边的结尾顶点放入下标为起点的parent中*/
			/*表示此顶点已经在生成树集合中*/
			parent[n] = m;
			printf("(%c,%c),%d\n", GL.adjList[edges[i].begin].data, GL.adjList[edges[i].end].data, edges[i].weight);
		}
	}
}

/*主函数测试*/
int main()
{
	GraphAdjList GL;
	CreateALGraph(&GL);
	GraphAdjList_MiniSpanTree_Kruskal(GL);
	return 0;
}