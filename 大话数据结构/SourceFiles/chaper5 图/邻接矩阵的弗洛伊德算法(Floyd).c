#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define MAXVEX 20
#define INFINITY 65535

typedef char VertexType;
typedef int EdgeType;
typedef int Pathmatirx[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
typedef int Status;
typedef int Boolean;
Boolean visited[MAXVEX];

typedef struct
{
	VertexType vexes[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVextexes, numEdges;
}MGraph;

void CreateMGraph(MGraph G)
{
	int i, j, k, w;
	printf("�����붥�����ͱ�����");
	scanf("%d %d", &G.numVextexes, &G.numEdges);
	for (i = 0; i < G.numVextexes; i++)
	{
		printf("�����붥��%d����Ϣ��", i + 1);
		scanf("\n%c", &G.vexes[i]);

	}
	for (i = 0; i < G.numVextexes; i++)
	{
		for (j = 0; j < G.numVextexes; j++)
		{
			G.arc[i][j] = INFINITY;
		}
	}
	for (k = 0; k < G.numEdges; k++)
	{
		printf("�������(Vi,Vj)���±�i���±�j��Ȩֵw��");
		scanf("%d %d %d", &i, &j, &w);
		G.arc[i][j] = w;
		G.arc[j][i] = G.arc[i][j];
	}
}

/*Floyd�㷨������ͼG�и�����v�����ඥ��w���·��P[v][w]����Ȩ����D[v][w]*/
void ShortestPATH_Floyd(MGraph G, Pathmatirx* P, ShortPathTable* D)
{
	int v, w, k;
	/*��ʼ��D��P*/
	for (v = 0; v < G.numVextexes; v++)
	{
		for (w = 0; w < G.numVextexes; w++)
		{
			/*D[v][w]ֵ��Ϊ��Ӧ����Ȩֵ*/
			(*D)[v][w] = G.arc[v][w];
			/*��ʼ��P*/
			(*P)[v][w] = w;
		}
	}
	for (k = 0; k < G.numVextexes; k++)
	{
		for (v = 0; v < G.numVextexes; v++)
		{
			for (w = 0; w < G.numVextexes; w++)
			{
				/*(*D)[v][w]��ʾ�Ӷ���v������w��Ȩֵ*/
				if ((*D)[v][k] + (*D)[k][w] < (*D)[v][w])
				{
					/*��������±�Ϊk����·����ԭ�����·������*/
					/*����ǰ�����Ȩֵ��Ϊ��С��һ��*/
					(*D)[v][w] = (*D)[v][k] + (*D)[k][w];
					/*·�����þ����±�Ϊk�Ķ���*/
					(*P)[v][w] = (*P)[v][k];
				}
			}
		}
	}
}