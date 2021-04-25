#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW 0

typedef char TElemType;

typedef struct BiTNode
{
	/*结点数据*/
	TElemType data;
	/*左右孩子指针*/
	struct BiTNode* lchild, * rchild;
}BiTNode, *BiTree;

//前序遍历
void PreOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	/*显示结点数据，可以更改为其他对结点操作*/
	printf("%c", T->data);
	/*再先序遍历左子树*/
	PreOrderTraverse(T->lchild);
	/*最后先序遍历右子树*/
	PreOrderTraverse(T->rchild);
}

//中序遍历
void InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	/*中序遍历左子树*/
	InOrderTraverse(T->lchild);
	/*显示结点数据，可以更改为其他对结点操作*/
	printf("%c", T->data);
	/*最后中序遍历右子树*/
	InOrderTraverse(T->rchild);
}

//后序遍历
void PostOrderTraverse(BiTree T)
{
	if(T == NULL)
		return;
	/*先后序遍历左子树*/
	PostOrderTraverse(T->lchild);
	/*再后序遍历右子树*/
	PostOrderTraverse(T->rchild);
	/*显示结点数据，可以更改为对其他结点操作*/
	printf("%c", T->data);
}

//用前序输入来创建二叉树
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
		/*生成根结点*/
		(*T)->data = ch;
		/*构造左子树*/
		CreateBiTree(&(*T)->lchild);//等价于&((*T)->lchild)
		/*构造右子树*/
		CreateBiTree(&(*T)->rchild);
	}
}