//#pragma warning(disable:4996)
//#include<stdio.h>
//#include<stdlib.h>
//#define OVERFLOW 0
//
//typedef char TElemType;
//
//typedef struct BiTNode
//{
//	TElemType data;
//	struct BTiNode* lchild, * rchild;
//}* BiTree;
//
////����������
//void CreateBiTree(BiTree* T)
//{
//	TElemType ch;
//	scanf("%c", &ch);
//	if (ch == '#')
//		*T = NULL;
//	else 
//	{
//		*T = (BiTree)malloc(sizeof(BiTree));
//		/*���ɸ����*/
//		(*T)->data = ch;
//		/*����������*/
//		CreateBiTree(&((*T)->lchild));
//		/*����������*/
//		CreateBiTree(&((*T)->rchild));
//	}
//}
//
///*ǰ�����������*/
//void PreOrderTraverse(BiTree* T)
//{
//	if (!(*T))
//		return;
//	/*��ʾ������ݣ����Ը���Ϊ�����Խ�����*/
//	printf("%c", (*T)->data);
//	/*���������������*/
//	PreOrderTraverse(&(*T)->lchild);
//	/*����������������*/
//	PreOrderTraverse(&(*T)->rchild);
//}
//
///*��Ҷ�ӽ����*/
//int LeafCount(BiTree* T)
//{
//	if (!(*T))
//		return 0;
//	else if(!(&(*T)->lchild) && (!&(*T)->rchild))
//		return 1;
//	else
//		return (LeafCount(&(*T)->lchild) + LeafCount(&(*T)->rchild));
//	
//}
//
//int main()
//{
//	BiTree T;
//	int count;
//	printf("�밴ǰ�������˳�����������(#Ϊ�ý���µĿ�����)��");
//	CreateBiTree(&T);
//	printf("�������ı�����");
//	PreOrderTraverse(&T);
//	printf("\n");
//	count = LeafCount(&T);
//	printf("Ҷ�ӽ����Ϊ��%d\n", count);
//	system("pause");
//	return 0;
//}

#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiNode
{
    ElemType data; //����Ԫ��
    struct BiNode* lchild, * rchild;
}BiNode, * BiTree;

/*�������������ս����#����*/
void CreateBiTree(BiTree* T)
{
    char ch;
    ch = getchar();
    if (ch == '#')
        *T = NULL;
    else
    {
        *T = (BiTree)malloc(sizeof(BiNode));
        (*T)->data = ch;
        CreateBiTree(&((*T)->lchild));
        CreateBiTree(&((*T)->rchild));
    }
}

/*ǰ�����������*/
void PreOrderTraverse(BiTree T)
{
	if (!T)
		return;
	/*��ʾ������ݣ����Ը���Ϊ�����Խ�����*/
	printf("%c", T->data);
	/*���������������*/
	PreOrderTraverse(T->lchild);
	/*����������������*/
	PreOrderTraverse(T->rchild);
}

/*��Ҷ�ӽ����*/
int LeafCount(BiTree T)
{
	if (!T)
		return 0;
	else if(!T->lchild && !T->rchild)
		return 1;
	else
		return (LeafCount(T->lchild) + LeafCount(T->rchild));
	
}

///*ǰ�����������*/
//void PreOrderTraverse(BiTree* T)
//{
//	if (!(*T))
//		return;
//	/*��ʾ������ݣ����Ը���Ϊ�����Խ�����*/
//	printf("%c", (*T)->data);
//	/*���������������*/
//	PreOrderTraverse(&(*T)->lchild);
//	/*����������������*/
//	PreOrderTraverse(&(*T)->rchild);
//}
//
///*��Ҷ�ӽ����*/
//int LeafCount(BiTree* T)
//{
//	if (!(*T))
//		return 0;
//	else if (!(&(*T)->lchild) && (!&(*T)->rchild))
//		return 1;
//	else
//		return (LeafCount(&(*T)->lchild) + LeafCount(&(*T)->rchild));
//
//}

//int main()
//{
//	BiTree T;
//	int count;
//	printf("�밴ǰ�������˳�����������(#Ϊ�ý���µĿ�����)��");
//	CreateBiTree(&T);
//	printf("�������ı�����");
//	PreOrderTraverse(&T);
//	printf("\n");
//	count = LeafCount(&T);
//	printf("Ҷ�ӽ����Ϊ��%d\n", count);
//	system("pause");
//	return 0;
//}

int main()
{
	BiTree T;
	int count;
	printf("�밴ǰ�������˳�����������(#Ϊ�ý���µĿ�����)��");
	CreateBiTree(&T);
	printf("�������ı�����");
	PreOrderTraverse(T);
	printf("\n");
	count = LeafCount(T);
	printf("Ҷ�ӽ����Ϊ��%d\n", count);
	system("pause");
	return 0;
}