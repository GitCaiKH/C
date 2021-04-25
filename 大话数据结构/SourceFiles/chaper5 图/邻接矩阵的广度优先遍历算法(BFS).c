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
	/*ͷָ��*/
	int front;
	/*βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ��*/
	int rear;
}SqQueue;

typedef struct
{
	VerTexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

/*����������ͼ���ڽӾ����ʾ*/
void CreateMGraph(MGraph* G)
{
	int i, j, k, w;
	printf("�����붥�����ͱ�����");
	/*�����붥�����ͱ���*/
	scanf("%d %d", &G->numVertexes, &G->numEdges);
	/*���붥����Ϣ�����������*/
	
	for (i = 0; i < G->numVertexes; i++)
	{
		printf("�����붥��%d����Ϣ��", i + 1);
		scanf("\n%c", &G->vexs[i]);
	}
	for (i = 0; i < G->numVertexes; i++)
		for (j = 0; j < G->numVertexes; j++)
			/*�ڽӾ���ĳ�ʼ��*/
			G->arc[i][j] = INFINITY;
	/*����numEdges���ߣ������ڽӾ���*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("�����(Vi,Vj)�ϵ��±�i���±�j:");
		/*�����(Vi,Vj)�ϵ��±�i���±�j*/
		scanf("%d %d", &i, &j);
		G->arc[i][j] = 1;
		G->arc[j][i] = G->arc[i][j];
	}
}

void Print_Matrix(MGraph G)
{
	int i, j;
	printf("\nͼ�Ķ���Ϊ: ");
	for (i = 0; i < G.numVertexes; i++)
		printf("%c ", G.vexs[i]);
	printf("\n����ڽӾ���:\n");
	printf("\t");
	for (i = 0; i < G.numVertexes; i++)
		printf("\t%8c", G.vexs[i]);
	for (i = 0; i < G.numVertexes; i++)
	{
		printf("\n\n%8c", G.vexs[i]);
		for (j = 0; j < G.numVertexes; j++)
		{
			if (G.arc[i][j] == INFINITY)
				printf("\t%8s", "��");
			else
				printf("\t%8d", G.arc[i][j]);
		}
		printf("\n");
	}
}

/*���еĳ�ʼ��*/
Status InitQueue(SqQueue* Q)
{
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//�����п�
Status QueueEmpty(SqQueue Q)
{
	return (Q.front == Q.rear) ? TRUE : FALSE;
}

/*��������*/
Status QueueFull(SqQueue Q)
{
	return ((Q.rear + 1) % MAXSIZE == Q.front) ? TRUE : FALSE;
}

//����еĳ���
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

//�����
Status EnQueue(SqQueue* Q, QElemType e)
{
	/*�����ж�*/
	if ((Q->rear + 1) % MAXSIZE == Q->front)
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

//������
Status DeQueue(SqQueue* Q, QElemType* e)
{
	/*�ӿ��ж�*/
	if (Q->front = Q->rear)
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

/*�ڽӾ���Ĺ�ȱ����㷨*/
void BFSTraverse(MGraph G)
{
	VerTexType i, j;
	SqQueue Q;	
	/*��ʼ��һ�����õĶ���*/
	InitQueue(&Q);
	for (i = 0; i < G.numVertexes; i++)
		visited[i] = FALSE;
	/*��ÿһ��������ѭ��*/
	for (i = 0; i < G.numVertexes; i++)
	{
		/*����δ���ʹ��ʹ���*/
		if (!visited[i])
		{
			/*���õ�ǰ������ʹ�*/
			visited[i] = TRUE;
			/*��ӡ��㣬Ҳ������������*/
			printf("%c ", G.vexs[i]);
			/*���˶��������*/
			EnQueue(&Q, i);
			/*����ǰ���в�Ϊ��*/
			while (!QueueEmpty(Q))
			{
				/*������Ԫ�س��У���ֵ��i*/
				DeQueue(&Q, &i);
				for (j = 0; j < G.numVertexes; j++)
				{
					/*�ж������������뵱ǰ������ڱ���δ���ʹ�*/
					if (G.arc[i][j] == 1 && !visited[j])
					{
						/*���ҵ��Ĵ˶�����Ϊ�ѷ���*/
						visited[j] = TRUE;
						/*��ӡ����*/
						printf("%c ", G.vexs[j]);
						/*���ҵ��Ĵ˶��������*/
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