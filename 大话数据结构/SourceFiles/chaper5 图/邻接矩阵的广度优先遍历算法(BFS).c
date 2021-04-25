#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define MAXSIZE 50
#define MAXVEX 50
#define INFINITY 65535

/*QElemType类型根据实际情况而定，这里为char*/
typedef char QElemType;
typedef int Status;
typedef char VerTexType;
typedef int EdgeType;
typedef int Boolean;
Boolean visited[MAXVEX];

/*循环队列的顺序存储结构*/
typedef struct
{
	QElemType data[MAXSIZE];
	/*头指针*/
	int front;
	/*尾指针，若队列不空，指向队列尾元素的下一个位置*/
	int rear;
}SqQueue;

typedef struct
{
	VerTexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

/*建立无向网图的邻接矩阵表示*/
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
		printf("输入边(Vi,Vj)上的下标i，下标j:");
		/*输入边(Vi,Vj)上的下标i，下标j*/
		scanf("%d %d", &i, &j);
		G->arc[i][j] = 1;
		G->arc[j][i] = G->arc[i][j];
	}
}

void Print_Matrix(MGraph G)
{
	int i, j;
	printf("\n图的顶点为: ");
	for (i = 0; i < G.numVertexes; i++)
		printf("%c ", G.vexs[i]);
	printf("\n输出邻接矩阵:\n");
	printf("\t");
	for (i = 0; i < G.numVertexes; i++)
		printf("\t%8c", G.vexs[i]);
	for (i = 0; i < G.numVertexes; i++)
	{
		printf("\n\n%8c", G.vexs[i]);
		for (j = 0; j < G.numVertexes; j++)
		{
			if (G.arc[i][j] == INFINITY)
				printf("\t%8s", "∞");
			else
				printf("\t%8d", G.arc[i][j]);
		}
		printf("\n");
	}
}

/*队列的初始化*/
Status InitQueue(SqQueue* Q)
{
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//队列判空
Status QueueEmpty(SqQueue Q)
{
	return (Q.front == Q.rear) ? TRUE : FALSE;
}

/*队列判满*/
Status QueueFull(SqQueue Q)
{
	return ((Q.rear + 1) % MAXSIZE == Q.front) ? TRUE : FALSE;
}

//求队列的长度
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

//入队列
Status EnQueue(SqQueue* Q, QElemType e)
{
	/*队满判断*/
	if ((Q->rear + 1) % MAXSIZE == Q->front)
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

//出队列
Status DeQueue(SqQueue* Q, QElemType* e)
{
	/*队空判断*/
	if (Q->front = Q->rear)
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

/*邻接矩阵的广度遍历算法*/
void BFSTraverse(MGraph G)
{
	VerTexType i, j;
	SqQueue Q;	
	/*初始化一辅助用的队列*/
	InitQueue(&Q);
	for (i = 0; i < G.numVertexes; i++)
		visited[i] = FALSE;
	/*对每一个顶点做循环*/
	for (i = 0; i < G.numVertexes; i++)
	{
		/*若是未访问过就处理*/
		if (!visited[i])
		{
			/*设置当前顶点访问过*/
			visited[i] = TRUE;
			/*打印结点，也可以其他操作*/
			printf("%c ", G.vexs[i]);
			/*将此顶点入队列*/
			EnQueue(&Q, i);
			/*若当前队列不为空*/
			while (!QueueEmpty(Q))
			{
				/*将队中元素出列，赋值给i*/
				DeQueue(&Q, &i);
				for (j = 0; j < G.numVertexes; j++)
				{
					/*判断其他顶点若与当前顶点存在边且未访问过*/
					if (G.arc[i][j] == 1 && !visited[j])
					{
						/*将找到的此顶点标记为已访问*/
						visited[j] = TRUE;
						/*打印顶点*/
						printf("%c ", G.vexs[j]);
						/*将找到的此顶点入队列*/
						EnQueue(&Q, j);
					}
				}
			}
		}
	}
}

int main()
{
	MGraph* G = (MGraph*)malloc(sizeof(MGraph));
	CreateMGraph(G);
	Print_Matrix(*G);
	BFSTraverse(*G);
	return 0;
}