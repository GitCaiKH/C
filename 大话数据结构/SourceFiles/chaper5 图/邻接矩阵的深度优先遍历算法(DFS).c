#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

#define MAX 100
/*��󶥵�����Ӧ���û�����*/
#define MAXVEX 100
/*��35535����ʾ����*/
#define INFINITY 65535

/*��������Ӧ���û�����*/
typedef char VertexType;
/*���ϵ�Ȩֵ����Ӧ���û�����*/
typedef int EdgeType;

/*Boolean�ǲ������ͣ���ֵ��TRUE��FALSE*/
typedef int Boolean;
Boolean visited[MAXVEX];

typedef struct
{
	/*�����*/
	VertexType vexs[MAXVEX];
	/*�ڽӾ��󣬿ɿ����߱�*/
	EdgeType arc[MAXVEX][MAXVEX];
	/*ͼ�е�ǰ�Ķ������ͱ���*/
	int numVertexes, numEdges;
}MGraph;

/*����������ͼ���ڽӾ����ʾ*/
void CreateMGraph(MGraph* G)
{
	int i, j, k, w;
	pirntf("���붥�����ͱ�����\n");
	/*���붥�����ͱ���*/
	scanf("%d,%d", &G->numVertexes, &G->numVertexes);
	/*���붥����Ϣ�����������*/
	for (i = 0; i < G->numVertexes; i++)
		scanf(&G->vexs[i]);
	for (i = 0; i < G->numVertexes; i++)
		for (j = 0; j < G->numVertexes; j++)
			/*�ڽӾ���ĳ�ʼ��*/
			G->arc[i][j] = INFINITY;
	/*����numEdges���ߣ������ڽӾ���*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("�����(Vi,Vj)�ϵ��±�i���±�j��Ȩw��\n");
		/*�����(Vi,Vj)�ϵ��±�i���±�j��Ȩw*/
		scanf("%d,%d,%d", &i, &j, &w);
		G->arc[i][j] = w;
		/*��Ϊͬ����ͼ������ĶԳ�*/
		G->arc[j][i] = G->arc[i][j];
	}
}

/*�ڽӾ����������ȵݹ��㷨*/
void DFS(MGraph G, int i)
{
	int j;
	visited[i] = TRUE;
	/*��ӡ���㣬Ҳ��������������*/
	printf("%c ", G.vexs[i]);
	for (j = 0; j < G.numVertexes; j++)
		if (G.arc[i][j] == 1 && !visited[j])
			/*��Ϊ���ʵ��ڽӶ���ݹ����*/
			DFS(G, j);
}

/*�ڽӾ������ȱ�������*/
void DFSTraverse(MGraph G)
{
	int i;
	for (i = 0; i < G.numVertexes; i++)
		/*��ʼ�����ж���״̬����δ���ʹ���״̬*/
		visited[i] = FALSE;
	for (i = 0; i < G.numVertexes; i++)
		/*��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ��*/
		if (!visited[i])
			DFS(G, i);
}