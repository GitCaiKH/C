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
/* ���ڴ洢���·���±������ */
typedef int Patharc[MAXVEX];
/* ���ڴ洢���������·����Ȩֵ�� */
typedef int ShortPathTable[MAXVEX];
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

/*����ͼ���ڽӱ�*/
void CreateALGraph(GraphAdjList* GL)
{
	int i, j, k;
	EdgeType w;
	EdgeNode* e;
	printf("���붥�㶥�����ͱ���: ");
	/*���붥�㶥�����ͱ���*/
	scanf("%d %d", &GL->numVertexes, &GL->numEdges);
	/*���붥����Ϣ�����������*/
	for (i = 0; i < GL->numVertexes; i++)
	{
		printf("�����붥�� %d ����Ϣ: ", i + 1);
		/*���붥����Ϣ*/
		scanf("\n%c", &GL->adjList[i].data);
		/*���߱���Ϊ�ձ�*/
		GL->adjList[i].firstEdge = NULL;
	}
	/*�����߱�*/
	for (k = 0; k < GL->numEdges; k++)
	{
		printf("�����(vi,vj)�ϵĶ�����ŶԺ�Ȩֵ: ");
		/* �����(vi,vj)�ϵĶ������ */
		scanf("%d %d %d", &i, &j, &w);
		/* ���ڴ�����ռ䣬���ɱ߱��� */
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/* �ڽ����Ϊj */
		e->adjvex = j;
		/*�ߵ�Ȩֵ*/
		e->weight = w;
		/* ��eָ��ָ��ǰ����ָ��Ľ�� */
		e->next = GL->adjList[i].firstEdge;
		/* ����ǰ�����ָ��ָ��e */
		GL->adjList[i].firstEdge = e;

		/* ���ڴ�����ռ䣬���ɱ߱��� */
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/* �ڽ����Ϊi*/
		e->adjvex = i;
		/*�ߵ�Ȩֵ*/
		e->weight = w;
		/* ��eָ��ָ��ǰ����ָ��Ľ�� */
		e->next = GL->adjList[j].firstEdge;
		/* ����ǰ�����ָ��ָ��e */
		GL->adjList[j].firstEdge = e;
	}
}

/* Dijkstra�㷨����������G��v0���㵽���ඥ��v���·��P[v]����Ȩ����D[v] */
/* P[v]��ֵΪǰ�������±꣬D[v]��ʾv0��v�����·�����Ⱥ͡� */
void GraphAdjList_ShortestPath_Dijkstra(GraphAdjList GL, int v0, Patharc* P, ShortPathTable* D)
{
	int i, j, k, min;
	EdgeNode* p;
	/* final[j]=1��ʾ�Ѿ���ö���v0��vj�����·�� */
	Status final[MAXVEX];
	for (i = 0; i < GL.numVertexes; i++)
	{
		/* ȫ�������ʼ��Ϊδ֪���·��״̬ */
		final[i] = FALSE;
		/*��ʼ��D��P����*/
		(*D)[i] = INFINITY;
		/* ��ʼ��·������PΪ-1 */
		(*P)[i] = -1;
	}
	for (p = GL.adjList[v0].firstEdge; p; p = p->next)
	{
		/* ����v0�������ߵĶ������Ȩֵ */
		(*D)[p->adjvex] = p->weight;
	}
	/*v0��v0·��Ϊ0*/
	(*D)[v0] = 0;
	/*v0��v0����Ҫ��·��*/
	final[v0] = TRUE;
	/* ��ʼ��ѭ����ÿ�����v0��ĳ��vi��������·�� */
	for (i = 1; i < GL.numVertexes; i++)
	{
		/* ��ǰ��֪��v0������������ */
		min = INFINITY;
		/* Ѱ����v0����Ķ��� */
		for (j = 0; j < GL.numVertexes; j++)
		{
			if (!final[j] && (*D)[i] < min)
			{
				/* w������v0������� */
				min = (*D)[j];
				k = j;
			}
		}
		/* ��Ŀǰ�ҵ�������Ķ�����ΪTRUE */
		final[k] = TRUE;
		/* ������ǰ���·�������� */
		for (p = GL.adjList[k].firstEdge; p; p = p->next)
		{
			/* �������v�����·������������·���ĳ��ȶ̵Ļ� */
			if (!final[p->adjvex] && (min + p->weight) < (*D)[p->adjvex])
			{
				/* ˵���ҵ��˸��̵�·�����޸�D[w]��P[w] */
				/* �޸ĵ�ǰ·������ */
				(*D)[p->adjvex] = min + p->weight;
				(*P)[p->adjvex] = k;
			}
		}
	}
}

void PrintPath(GraphAdjList GL, int v0, Patharc* P, int i)
{
	if (i != -1)
	{
		PrintPath(GL, v0, P, (*P)[i]);
		printf("V%c->", GL.adjList[i].data);
	}
	else
		printf("���·��Ϊ��V%c->", GL.adjList[v0].data);
}

/*���·��*/
void Path(GraphAdjList GL, int v0, Patharc* P, ShortPathTable* D)
{
	int i;
	for (i = 0; i < GL.numVertexes; i++)
	{
		/*��Ϊ��V0�����������㣬����i����v0��ִ��*/
		if (i != v0)
		{
			/*V0�������������ֱ��ǰ��*/
			if ((*P)[i] != -1)
			{
				PrintPath(GL, v0, P, (*P)[i]);
				printf("V%c\n", GL.adjList[i].data);
			}
			else
				printf("���·��Ϊ��V%c->V%c\n", GL.adjList[v0].data, GL.adjList[i].data);
			printf("���·������Ϊ��%d\n\n", (*D)[i]);
		}
	}
}

/*������������Ϣ��Ӧ���ڽӱ��е�λ�ã������ڽӱ���λ���±�*/
int LocateVex(GraphAdjList GL, VerTexType start)
{
	int i;
	for (i = 0; i < GL.numVertexes; i++)
	{
		if (start == GL.adjList[i].data)
			return i;
	}
	if (i >= GL.numVertexes)
		/*δ�ҵ�������Ϣ������-1*/
		return -1;
}

int main()
{
	GraphAdjList GL;
	Patharc P;
	ShortPathTable D;
	VerTexType start;
	int v0;
	CreateALGraph(&GL);
	printf("������Դ�㣺");
	scanf("\n%c", &start);
	v0 = LocateVex(GL, start);
	if (v0 != -1)
	{
		GraphAdjList_ShortestPath_Dijkstra(GL, v0, &P, &D);
		printf("\n");
		Path(GL, v0, &P, &D);
	}
	else
		/*��������˳�����*/
		exit(ERROR);
	system("pause");
	return 0;
}