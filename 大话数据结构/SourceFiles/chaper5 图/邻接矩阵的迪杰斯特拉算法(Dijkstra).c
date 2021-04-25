#pragma warning(disable:4996)
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
typedef int Patharc[MAXVEX];//���ڴ洢���·���±������
typedef int ShortPathTable[MAXVEX];//���ڴ洢���������·����Ȩֵ��
typedef int Status;
typedef int Boolean;
Boolean visited[MAXVEX];

typedef struct MGraph
{
	VertexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;


/*���ڽӾ�����Ϊ�洢�ṹ��������ͼ*/
void CreateMGraph(MGraph* G)
{
	int i, j, k, w;
	printf("�����붥�����ͱ�����");
	scanf("%d %d", &G->numVertexes, &G->numEdges);
	for (i = 0; i < G->numVertexes; i++)
	{
		printf("�����붥��%d����Ϣ��", i + 1);
		scanf("\n%c", &G->vexs[i]);
	}
	for (i = 0; i < G->numVertexes; i++)
	{
		for (j = 0; j < G->numVertexes; j++)
		{
			G->arc[i][j] = INFINITY;
		}
	}
	for (k = 0; k < G->numEdges; k++)
	{
		printf("�������(Vi,Vj)�����±�i���±�j��Ȩֵw��");
		scanf("%d %d", &i, &j, &w);
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
}

/*DijKstra�㷨��������ͼG��V0���㵽���ඥ��V���·��P[V]����Ȩ��*/
/*P[V]��ֵΪǰ�������±꣬D[V]��ʾV0��V�����·�����Ⱥ�*/
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc* P, ShortPathTable* D)
{
	int v, w, k, min;
	/*final[w] = 1��ʾ�󶥵�V0��Vw�����·��*/
	int final[MAXVEX];
	/*��ʼ������*/
	for (v = 0; v < G.numVertexes; v++)
	{
		/*ȫ�������ʼ��Ϊδ֪���·��״̬*/
		final[v] = 0;
		/*����V0�������ߵĶ������Ȩֵ*/
		(*D)[v] = G.arc[v0][v];
		/*��ʼ��·������PΪ-1*/
		(*P)[v] = -1;
	}
	/*v0��v0·��Ϊ0*/
	(*D)[v0] = 0;
	/*v0��v0����Ҫ��·��*/
	final[v0] = 1;
	/*��ʼ��ѭ����ÿ�����V0��ĳ����������·��*/
	for (v = 1; v < G.numVertexes; v++)
	{
		/*��ǰ��֪��V0������������*/
		min = INFINITY;
		/*Ѱ����V0����Ķ���*/
		for (w = 0; w < G.numVertexes; w++)
		{
			if (!final[w] && (*D)[w] < min)
			{
				k = w;
				/*w������V0�������*/
				min = (*D)[w];
			}
		}
		/*��Ŀǰ�ҵ�������Ķ�����Ϊ1*/
		final[k] = 1;
		/*������ǰ���·��������*/
		for (w = 0; w < G.numVertexes; w++)
		{
			/*�������v�����·������������·���ĳ��ȶ̵Ļ�*/
			if (!final[w] && (min + G.arc[k][w] < (*D)[w]))
			{
				/*˵���ҵ��˸��̵�·�����޸�D[w]��P[w]*/
				/*�޸ĵ�ǰ·������*/
				(*D)[w] = min + G.arc[k][w];
				(*P)[w] = k;
			}
		}
	}
}