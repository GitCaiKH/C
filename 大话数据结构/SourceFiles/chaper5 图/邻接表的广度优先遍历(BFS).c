#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define MAXVEX 1024
#define MAXSIZE 1024
#define INFINITY 65535

/*QElemType���͸���ʵ���������������Ϊchar*/
typedef char QElemType;
typedef int Status;
typedef char VerTexType;
typedef int EdgeType;
typedef int Boolean;
Boolean visited[MAXVEX];

/*ѭ�����е�˳��洢�ṹ*/
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

/*����ͼ���ڽӱ�*/
void CreateALGraph(GraphAdjList* G)
{
	int i, j, k;
	EdgeNode* e;
	printf("���붥�㶥�����ͱ�����\n");
	/*���붥�㶥�����ͱ���*/
	scanf("%d,%d", &G->numVertexes, &G->numEdges);
	/*���붥����Ϣ�����������*/
	for (i = 0; i < G->numVertexes; i++)
	{
		/*���붥����Ϣ*/
		scanf("%c", &G->adjList[i].data);
		/*���߱���Ϊ�ձ�*/
		G->adjList[i].firstEdge = NULL;
	}
	/*�����߱�*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("�����(vi,vj)�ϵĶ������:\n");
		/* �����(vi,vj)�ϵĶ������ */
		scanf("%d,%d", &i, &j);
		/* ���ڴ�����ռ䣬���ɱ߱��� */
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/* �ڽ����Ϊj */
		e->adjvex = j;
		/* ��eָ��ָ��ǰ����ָ��Ľ�� */
		e->next = G->adjList[i].firstEdge;
		/* ����ǰ�����ָ��ָ��e */
		G->adjList[i].firstEdge = e;

		/* ���ڴ�����ռ䣬���ɱ߱��� */
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/* �ڽ����Ϊi*/
		e->adjvex = i;
		/* ��eָ��ָ��ǰ����ָ��Ľ�� */
		e->next = G->adjList[j].firstEdge;
		/* ����ǰ�����ָ��ָ��e */
		G->adjList[j].firstEdge = e;	
	}
}

/*���еĳ�ʼ��*/
Status InitQueue(SqQueue* Q)
{
	Q = (SqQueue*)malloc(sizeof(SqQueue));
	Q->front = 0;
	Q->front = 0;
	return OK;
}

//������
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

/*�����п�*/
Status QueueEmpty(SqQueue Q)
{
	return (Q.front == Q.rear) ? TRUE : FALSE;
}

/*��������*/
Status QueueFull(SqQueue Q)
{
	return ((Q.rear + 1) % MAXSIZE == Q.front) ? TRUE : FALSE;
}

//���
Status EnQueue(SqQueue* Q, QElemType e)
{
	if (QueueFull(*Q))
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

//����
Status DeQueue(SqQueue* Q, QElemType* e)
{
	if (QueueEmpty(*Q))
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

/*�ڽӱ�Ĺ�ȱ����㷨*/
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
			/*��ӡ���㣬Ҳ������������*/
			printf("%c ", GL.adjList[i].data);
			EnQueue(&Q, i);
			while (!QueueEmpty(Q))
			{
				DeQueue(&Q, &i);
				/*�򵽵�ǰ����߱�����ͷָ��*/
				p = GL.adjList[i].firstEdge;
				while (p)
				{
					/*���˶���δ������*/
					if (!visited[p->adjvex])
					{
						visited[p->adjvex] = TRUE;
						printf("%c ", GL.adjList[p->adjvex].data);
						/*���˶��������*/
						EnQueue(&Q, p->adjvex);
					}
					/*ָ��ָ����һ���ڽӵ�*/
					p = p->next;
				}
			}
		}
	}
}