#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

/*��󶥵�����Ӧ���û�����*/
#define MAXVEX 20
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

/*Prim�㷨������С������*/
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	/*������ض����±�*/
	int adjvex[MAXVEX];
	/*������ض����ߵ�Ȩֵ*/
	int lowcost[MAXVEX];
	/*��ʼ����һ��ȨֵΪ0����v0����������*/
	/*lowcost��ֵΪ0����������Ǵ��±�Ķ����Ѿ�����������*/
	lowcost[0] = 0;
	/*��ʼ����һ�������±�Ϊ0*/
	adjvex[0] = 0;
	/*ѭ�����±�Ϊ0���ȫ������*/
	for (i = 1; i < G.numVertexes; i++)
	{
		/*��v0������֮�бߵ�Ȩֵ��������*/
		lowcost[i] = G.arc[0][i];
		/*��ʼ����Ϊv0���±�*/
		adjvex[i] = 0;
	}

	for (i = 1; i < G.numVertexes; i++)
	{
		/*��ʼ����СȨֵΪ�ޣ�*/
		/*ͨ������Ϊ�����ܵĴ�������32767��65535��*/
		min = INFINITY;
		j = 1;
		k = 0;
		/*ѭ��ȫ������*/
		while (j < G.numVertexes)
		{
			/*���Ȩֵ��Ϊ0��ȨֵС��min*/
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				/*���õ�ǰȨֵ��Ϊ��Сֵ*/
				min = lowcost[j];
				/*����ǰ��Сֵ���±����k*/
				k = j;
			}
			j++;
		}

		/*��ӡ��ǰ�������Ȩֵ��С��*/
		/*������������ıߣ�adjvex[k]�д洢�����Ǿ�����СȨֵ�ߵ����*/
		printf("(%d,%d) ", adjvex[k], k);
		/*����ǰ�����Ȩֵ����Ϊ0����ʾ�˶����Ѿ��������*/
		lowcost[k] = 0;
		/*ѭ�����ж���*/
		for (j = 1; j < G.numVertexes; j++)
		{
			/*�ڵ�k�ɹ������������ˣ���Ҫ��������ڵ㵽�ڵ㼯��u�ľ��룬�Ǹ���*/
			/*���±�Ϊk�������ȨֵС�ڴ�ǰ��Щ����δ������������Ȩֵ*/
			if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
			{
				/*����СȨֵ����lowcost*/
				lowcost[j] = G.arc[k][j];
				/*���±�Ϊk�Ķ������adjvex*/
				adjvex[j] = k;
			}
		}
	}
}

int main()
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Prim(G);
	return 0;
}