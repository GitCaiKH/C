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

/*�Ա߼�����Edge�ṹ�Ķ���*/
typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;


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

/*�ڽӱ�ʵ��Prim�㷨��������ϡ��ͼ*/
void GraphAdjList_MiniSpanTree_Kruskal(GraphAdjList GL)
{
	EdgeNode* p;
	int i, x, k, n, m;
	Status flag;
	/*����߼�����*/
	Edge edges[MAXEDGE];
	/*����һ���������жϱ�����Ƿ��γɻ�·*/
	int parent[MAXVEX];
	k = 0;
	for (i = 0; i < GL.numVertexes; i++)
	{
		for (p = GL.adjList[i].firstEdge; p; p = p->next)
		{
			/*����ͼ�ж�V(i)��V(p->adjvex)��V(p->adjvex)��V(i)��һ��*/
			flag = TRUE;
			/*�����Ѵ��ڵı߼�����*/
			for (x = 0; x < k; x++)
			{

				if (edges[x].begin == p->adjvex && edges[x].end == i)
				{
					/*����ͼ������߼������Ѿ�����һ��V(i)��V(p->adjvex)�ı���flagΪFALSE*/
					flag = FALSE;
					break;
				}
			}
			if (flag == TRUE)
			{
				/*���Ϊi���յ�Ϊp->adjvex��Ȩֵ��p->weight*/
				edges[k].begin = i;       
				edges[k].end = p->adjvex;
				edges[k].weight = p->weight;
				k++;
			}
		}
	}
	/*���߼����鰴Ȩ��С��������*/
	EdgesSort(edges, k);
	for (i = 0; i < GL.numVertexes; i++)
		/*��ʼ������ֵΪ0*/
		parent[i] = 0;
	/*ѭ��ÿһ����*/
	for (i = 0; i < GL.numEdges; i++)
	{
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);
		/*����n��m���ȣ�˵���˱�û���������������γɻ�·*/
		if (n != m)
		{
			/*���˱ߵĽ�β��������±�Ϊ����parent��*/
			/*��ʾ�˶����Ѿ���������������*/
			parent[n] = m;
			printf("(%c,%c),%d\n", GL.adjList[edges[i].begin].data, GL.adjList[edges[i].end].data, edges[i].weight);
		}
	}
}

/*����������*/
int main()
{
	GraphAdjList GL;
	CreateALGraph(&GL);
	GraphAdjList_MiniSpanTree_Kruskal(GL);
	return 0;
}