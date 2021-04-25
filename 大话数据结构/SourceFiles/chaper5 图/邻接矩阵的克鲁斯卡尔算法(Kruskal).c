#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

/*��󶥵�����Ӧ���û�����*/
#define MAXVEX 40
/*��������Ӧ���û�����*/
#define MAXEDGE 20
/*��65535��ʾ����*/
#define INFINITY 65535

/*��������Ӧ���û�����*/
typedef char VertexType;
/*���ϵ�Ȩֵ����Ӧ���û�����*/
typedef int EdgeType;

typedef struct
{
	/*�����*/
	VertexType vexs[MAXVEX];
	/*�ڽӾ��󣬿ɿ����߱�*/
	EdgeType arc[MAXVEX][MAXVEX];
	/*ͼ�е�ǰ�Ķ������ͱ���*/
	int numVertexes, numEdges;
}MGraph;

/*�Ա߼�����Edge�ṹ�Ķ���*/
typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;

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
		printf("�����(Vi,Vj)�ϵ��±�i���±�j��Ȩw��");
		/*�����(Vi,Vj)�ϵ��±�i���±�j��Ȩw*/
		scanf("%d %d %d", &i, &j, &w);
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
}

/*�������߶����β���±�*/
int Find(int* parent, int f)
{
	while (parent[f] > 0)
		f = parent[f];
	return f;
}

/*�Ա߼������������*/
void EdgesSort(Edge edges[MAXVEX], int k)
{
	int i, j;
	/*t����������*/
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

/*Kruskal�㷨������С������*/
/*������С������*/
void MiniSpanTree_Kruskal(MGraph G)
{
	int i, j, k, n, m;
	/*����߼�����*/
	Edge edges[MAXEDGE];
	/*����һ���������жϱ�����Ƿ��γɻ�·*/
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
	/*���߼����鰴Ȩ��С��������*/
	EdgesSort(edges, k);

	for (i = 0; i < G.numVertexes; i++)
		/*��ʼ������ֵΪ0*/
		parent[i] = 0;
	/*ѭ��ÿһ����*/
	for (i = 0; i < G.numEdges; i++)
	{
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);
		/*����n��m���ȣ�˵���˱�û���������������γɻ�·*/
		if (n != m)
		{
			/*���˱ߵĽ�β��������±�Ϊ����parent��*/
			/*��ʾ�˶����Ѿ���������������*/
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