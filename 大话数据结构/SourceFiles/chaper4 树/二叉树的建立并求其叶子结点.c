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
////建立二叉树
//void CreateBiTree(BiTree* T)
//{
//	TElemType ch;
//	scanf("%c", &ch);
//	if (ch == '#')
//		*T = NULL;
//	else 
//	{
//		*T = (BiTree)malloc(sizeof(BiTree));
//		/*生成根结点*/
//		(*T)->data = ch;
//		/*构造左子树*/
//		CreateBiTree(&((*T)->lchild));
//		/*构造右子树*/
//		CreateBiTree(&((*T)->rchild));
//	}
//}
//
///*前序遍历二叉树*/
//void PreOrderTraverse(BiTree* T)
//{
//	if (!(*T))
//		return;
//	/*显示结点数据，可以更改为其他对结点操作*/
//	printf("%c", (*T)->data);
//	/*再先序遍历左子树*/
//	PreOrderTraverse(&(*T)->lchild);
//	/*最后先序遍历右子树*/
//	PreOrderTraverse(&(*T)->rchild);
//}
//
///*求叶子结点数*/
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
//	printf("请按前序遍历的顺序输入二叉树(#为该结点下的空子树)：");
//	CreateBiTree(&T);
//	printf("二叉树的遍历：");
//	PreOrderTraverse(&T);
//	printf("\n");
//	count = LeafCount(&T);
//	printf("叶子结点数为：%d\n", count);
//	system("pause");
//	return 0;
//}

#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiNode
{
    ElemType data; //数据元素
    struct BiNode* lchild, * rchild;
}BiNode, * BiTree;

/*建立二叉树，空结点用#代替*/
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

/*前序遍历二叉树*/
void PreOrderTraverse(BiTree T)
{
	if (!T)
		return;
	/*显示结点数据，可以更改为其他对结点操作*/
	printf("%c", T->data);
	/*再先序遍历左子树*/
	PreOrderTraverse(T->lchild);
	/*最后先序遍历右子树*/
	PreOrderTraverse(T->rchild);
}

/*求叶子结点数*/
int LeafCount(BiTree T)
{
	if (!T)
		return 0;
	else if(!T->lchild && !T->rchild)
		return 1;
	else
		return (LeafCount(T->lchild) + LeafCount(T->rchild));
	
}

///*前序遍历二叉树*/
//void PreOrderTraverse(BiTree* T)
//{
//	if (!(*T))
//		return;
//	/*显示结点数据，可以更改为其他对结点操作*/
//	printf("%c", (*T)->data);
//	/*再先序遍历左子树*/
//	PreOrderTraverse(&(*T)->lchild);
//	/*最后先序遍历右子树*/
//	PreOrderTraverse(&(*T)->rchild);
//}
//
///*求叶子结点数*/
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
//	printf("请按前序遍历的顺序输入二叉树(#为该结点下的空子树)：");
//	CreateBiTree(&T);
//	printf("二叉树的遍历：");
//	PreOrderTraverse(&T);
//	printf("\n");
//	count = LeafCount(&T);
//	printf("叶子结点数为：%d\n", count);
//	system("pause");
//	return 0;
//}

int main()
{
	BiTree T;
	int count;
	printf("请按前序遍历的顺序输入二叉树(#为该结点下的空子树)：");
	CreateBiTree(&T);
	printf("二叉树的遍历：");
	PreOrderTraverse(T);
	printf("\n");
	count = LeafCount(T);
	printf("叶子结点数为：%d\n", count);
	system("pause");
	return 0;
}