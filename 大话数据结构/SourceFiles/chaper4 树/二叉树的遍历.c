#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW 0

typedef char TElemType;

typedef struct BiTNode
{
	/*�������*/
	TElemType data;
	/*���Һ���ָ��*/
	struct BiTNode* lchild, * rchild;
}BiTNode, *BiTree;

//ǰ�����
void PreOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	/*��ʾ������ݣ����Ը���Ϊ�����Խ�����*/
	printf("%c", T->data);
	/*���������������*/
	PreOrderTraverse(T->lchild);
	/*����������������*/
	PreOrderTraverse(T->rchild);
}

//�������
void InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	/*�������������*/
	InOrderTraverse(T->lchild);
	/*��ʾ������ݣ����Ը���Ϊ�����Խ�����*/
	printf("%c", T->data);
	/*����������������*/
	InOrderTraverse(T->rchild);
}

//�������
void PostOrderTraverse(BiTree T)
{
	if(T == NULL)
		return;
	/*�Ⱥ������������*/
	PostOrderTraverse(T->lchild);
	/*�ٺ������������*/
	PostOrderTraverse(T->rchild);
	/*��ʾ������ݣ����Ը���Ϊ������������*/
	printf("%c", T->data);
}

//��ǰ������������������
void CreateBiTree(BiTree* T)
{
	TElemType ch;
	scanf("%c", &ch);
	if (ch == '#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!*T)
			exit(OVERFLOW);
		/*���ɸ����*/
		(*T)->data = ch;
		/*����������*/
		CreateBiTree(&(*T)->lchild);//�ȼ���&((*T)->lchild)
		/*����������*/
		CreateBiTree(&(*T)->rchild);
	}
}