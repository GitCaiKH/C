#include<stdio.h>
#include<stdlib.h>

#define MAXVEX 20
#define MAXEDGE 20
#define INFINITY 65535
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef char VertexType;
typedef int EdgeType;

/*�߱���*/
typedef struct EdgeNode
{
	/*�ڽӵ��򣬴洢�ö����Ӧ���±�*/
	int adjvex;
	/*���ڴ洢Ȩֵ�� ���ڷ���ͼ���Բ���Ҫ*/
	int weight;
	/*����ָ����һ���ڽӵ�*/
	struct EdgeNode* next;
}EdgeNode;

/*�������*/
typedef struct VertexNode
{
	/*�������*/
	int in;
	/*�����򣬴洢������Ϣ*/
	int data;
	/*�߱�ͷָ��*/
	EdgeNode* firstedge;
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	/*ͼ�е�ǰ�������ͱ���*/
	int numVertexes, numEdges;
}graphAdjList, * GraphAdjList;

/*����ͼ���ڽӱ�ṹ*/
void CreateALGraph(graphAdjList* G)
{
	int i, j, k;
	EdgeNode* e;
	printf("���붥�����ͱ�����\n");
	/*���붥�����ͱ���*/
	scanf("%d,%d", &G->numVertexes, &G->numEdges);
	/*���붥����Ϣ�����������*/
	for (i = 0; i < G->numVertexes; i++)
	{
		/*���붥����Ϣ*/
		scanf("%d", &G->adjList[i].data);
		/*���߱� �ÿ�*/
		G->adjList[i].firstedge = NULL;
		/*����i�������0*/
		G->adjList[i].in = 0;
	}

	/*�����߱�*/
	for (k = 0; k < G->numEdges; k++)
	{
		printf("�����(Vi,Vj)�ϵĶ�����ţ�\n");
		/*�����(Vi,Vj)�ϵĶ������*/
		scanf("%d,%d", &i, &j);

		/*���ڴ�����ռ�*/
		/*���ɱ߱���*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*�ڽ����Ϊj*/
		e->adjvex = j;
		/*��eָ��ָ��ǰ����ָ��Ľ��*/
		e->next = G->adjList[i].firstedge;
		/*����j��ȼ�1 */
		G->adjList[j].in++;
		/*����ǰ�����ָ��ָ��e*/
		G->adjList[i].firstedge = e;
	}
}

Status TopologicalSort(GraphAdjList GL)
{
	EdgeNode* e;
	int i, k, gettop;
	/*����ջָ���±�*/
	int top = 0;
	/*����ͳ���������ĸ���*/
	int count = 0;
	/*��ջ�������洢���Ϊ0�Ķ���*/
	int* stack;
	stack = (int*)malloc(sizeof(int) * GL->numVertexes);
	for (i = 0; i < GL->numVertexes; i++)
	{
		if (GL->adjList[i].in == 0)
			/*�����Ϊ0�Ķ�����ջ*/
			stack[++top] = i;
	}
	while (top != 0)
	{
		/*��ջ*/
		gettop = stack[top--];
		/*��ӡ�˶���*/
		printf("%d -> ", GL->adjList[gettop].data);
		/*ͳ�����������*/
		count++;
		/*�Դ˶��㻡�����*/
		for (e = GL->adjList[gettop].firstedge; e; e = e->next)
		{
			k = e->adjvex;
			/*��k�Ŷ����ڽӵ����ȼ�1 */
			if (!(GL->adjList[k].in))
				/*��Ϊ0����ջ���Ա����´�ѭ�����*/
				stack[++top] = k;
		}
	}
	/*���countС�ڶ�������˵�����ڻ�*/
	if (count < GL->numVertexes)
		return ERROR;
	else
		return OK;
}