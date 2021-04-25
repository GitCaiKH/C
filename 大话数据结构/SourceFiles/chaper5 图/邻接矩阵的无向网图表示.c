#include<stdio.h>
#include<stdlib.h>

/*��󶥵�����Ӧ���û�����*/
#define MAXVEX 100
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

void CreateMGraph(MGraph* G)
{
	int i, j, k, w;
	printf("���붥�����ͱ���:\n");
	/*���붥�����ͱ���*/
	scanf("%d,%d", &G->numVertexes, &G->numEdges);
	/*���붥����Ϣ�����������*/
	for (i = 0; i < G->numVertexes; i++)
		scanf("%c", &G->vexs[i]);
	for (i = 0; i < G->numVertexes; i++)
		for (j = 0; j < G->numVertexes; j++)
			/*�ڽӾ����ʼ��*/
			G->arc[i][j] = INFINITY;
	/*����numEdges���ߣ������ڽӾ���*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("�����(Vi,Vj)�ϵ��±�i���±�j��Ȩw:\n");
		/*�����(Vi,Vj)�ϵ�Ȩ*/
		scanf("%d,%d,%d", &i, &j, &w);
		G->arc[i][j] = w;
		/*��Ϊ������ͼ������Գ�*/
		G->arc[i][j] = G->arc[i][j];
	}
}