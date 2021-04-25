#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define MAXVEX 1024
#define MAXSIZE 1024
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
	int front, rear;
}SqQueue;

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
void CreateALGraph(GraphAdjList* G)
{
	int i, j, k;
	EdgeNode* e;
	printf("输入顶点顶点数和边数：\n");
	/*输入顶点顶点数和边数*/
	scanf("%d,%d", &G->numVertexes, &G->numEdges);
	/*读入顶点信息，建立顶点表*/
	for (i = 0; i < G->numVertexes; i++)
	{
		/*输入顶点信息*/
		scanf("%c", &G->adjList[i].data);
		/*将边表置为空表*/
		G->adjList[i].firstEdge = NULL;
	}
	/*建立边表*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("输入边(vi,vj)上的顶点序号:\n");
		/* 输入边(vi,vj)上的顶点序号 */
		scanf("%d,%d", &i, &j);
		/* 向内存申请空间，生成边表结点 */
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/* 邻接序号为j */
		e->adjvex = j;
		/* 将e指针指向当前顶点指向的结点 */
		e->next = G->adjList[i].firstEdge;
		/* 将当前顶点的指针指向e */
		G->adjList[i].firstEdge = e;

		/* 向内存申请空间，生成边表结点 */
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/* 邻接序号为i*/
		e->adjvex = i;
		/* 将e指针指向当前顶点指向的结点 */
		e->next = G->adjList[j].firstEdge;
		/* 将当前顶点的指针指向e */
		G->adjList[j].firstEdge = e;	
	}
}

/*队列的初始化*/
Status InitQueue(SqQueue* Q)
{
	Q = (SqQueue*)malloc(sizeof(SqQueue));
	Q->front = 0;
	Q->front = 0;
	return OK;
}

//队列求长
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

/*队列判空*/
Status QueueEmpty(SqQueue Q)
{
	return (Q.front == Q.rear) ? TRUE : FALSE;
}

/*队列判满*/
Status QueueFull(SqQueue Q)
{
	return ((Q.rear + 1) % MAXSIZE == Q.front) ? TRUE : FALSE;
}

//入队
Status EnQueue(SqQueue* Q, QElemType e)
{
	if (QueueFull(*Q))
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

//出队
Status DeQueue(SqQueue* Q, QElemType* e)
{
	if (QueueEmpty(*Q))
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

/*邻接表的广度遍历算法*/
void BFSTraverse(GraphAdjList GL)
{
	int i;
	EdgeNode* p;
	SqQueue Q;
	InitQueue(&Q);
	for (i = 0; i < GL.numVertexes; i++)
		visited[i] = FALSE;
	for (i = 0; i < GL.numVertexes; i++)
	{
		if (!visited[i])
		{
			visited[i] = TRUE;
			/*打印顶点，也可以其他操作*/
			printf("%c ", GL.adjList[i].data);
			EnQueue(&Q, i);
			while (!QueueEmpty(Q))
			{
				DeQueue(&Q, &i);
				/*打到当前顶点边表链表头指针*/
				p = GL.adjList[i].firstEdge;
				while (p)
				{
					/*若此顶点未被访问*/
					if (!visited[p->adjvex])
					{
						visited[p->adjvex] = TRUE;
						printf("%c ", GL.adjList[p->adjvex].data);
						/*将此顶点入队列*/
						EnQueue(&Q, p->adjvex);
					}
					/*指针指向下一个邻接点*/
					p = p->next;
				}
			}
		}
	}
}