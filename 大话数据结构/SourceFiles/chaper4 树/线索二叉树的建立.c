#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW 0

typedef char TElemType;
typedef int Status;

/*二叉树的二叉线索存储结构定义*/
/*Link = 0 表示指向左右孩子指针*/
/*Thread = 1 表示指向前驱或后继的线索*/
typedef enum
{
	Link, 
	Thread
}PointerTag;

/*二叉线索存储结点结构*/
typedef struct BiThrNode
{
	/*结点数据*/
	TElemType data;
	/*左右孩子指针*/
	struct BiThrNode* lchild, * rchild;
	/*左右标示*/
	PointerTag LTag, RTag;
}BiThrNode, * BiThrTree;

BiThrTree pre;   /*全局变量，始终指向刚刚访问过的结点*/
TElemType Nil = ' ';/*字符型以空格符为空*/

/*按前序遍历方式创建一棵二叉树*/
void CreateBiThrTree(BiThrTree* T)
{
	TElemType c;
	scanf("%c", &c);
	/*#表示空子树*/
	if (c == Nil)
	{
		*T = NULL;
	}
	else
	{
		*T = (BiThrTree)malloc(sizeof(BiThrNode));
		if (!(*T))
			exit(OVERFLOW);
		(*T)->data = c;
		CreateBiThrTree(&((*T)->lchild));
		/*有左孩子，线索为0，指向左孩子*/
		if ((*T)->lchild)
			(*T)->LTag = Link;
		CreateBiThrTree(&((*T)->rchild));
		/*有右孩子，线索为0，指向右孩子*/
		if ((*T)->rchild)
			(*T)->RTag = Link;
	}
}

/*中序遍历进行中序线索化*/
void InThreading(BiThrTree p)
{
	if (p)
	{
		/*递归左子树线索化*/
		InThreading(p->lchild);
		/*没有左孩子*/
		if (!p->lchild)
		{
			/*前驱线索*/
			p->LTag = Thread;
			/*左孩子指针指向前驱*/
			p->lchild = pre;
		}
		/*前驱无右孩子*/
		if (!pre->rchild)
		{
			/*后继线索*/
			pre->RTag = Thread;
			/*前驱右孩子指针指向后继（当前结点p）*/
			pre->rchild = p;
		}
		/*保持pre指向p的前驱*/
		pre = p;
		/*递归右子树线索化*/
		InThreading(p->rchild);
	}
}

void InOrderThreading(BiThrTree* p, BiThrTree T)
{
	/*建立头结点*/
	*p = (BiThrTree)malloc(sizeof(BiThrNode));
	if (!(*p))
		exit(OVERFLOW);
	/*标志左孩子为指针*/
	(*p)->LTag = Link;
	/*标志右孩子为线索*/
	(*p)->RTag = Thread;
	/*右指针回指*/
	(*p)->rchild = *p;
	/*若二叉树为空，则左指针回指*/
	if (!T)
		(*p)->lchild = *p;
	else
	{
		/*头结点左指针指向树的根*/
		(*p)->lchild = T;
		pre = *p;
		/*中序遍历进行中序线索化*/
		InThreading(T);
		/*最后一个结点线索化*/
		pre->RTag = Thread;
		pre->rchild = *p;
		(*p)->rchild = pre;
		
	}
}


/*T指向头结点，头结点左链lchild指向根结点*/
/*头结点右链rchild指向中序遍历的最后一个结点*/
/*中序遍历二叉线索链表表示的二叉树T*/
//Status InOrderTraverse_Thr(BiThrTree T)
//{
//	BiThrTree p;
//	/*p指向根结点*/
//	p = T->lchild;
//	/*空树或遍历结束时，p == T*/
//	while (p != T)
//	{
//		/*当LTab == 0时循环到中序序列第一个结点*/
//		while (p->LTag == Link)
//			p = p->lchild;
//		/*显示结点数据，可以更改为其他对结点操作*/
//		printf("%c", p->data);
//		while (p->RTag == Thread && p->rchild != T)
//		{
//			p = p->rchild;
//			printf("%c ", p->data);
//		}
//		/*p进至其右子树根*/
//		p = p->rchild;
//	}
//	return OK;
//}

//算法6.5 P134
//中序遍历二叉线索树T(头结点)的非递归算法。
int InOrderTraverse_Thr(BiThrTree T, int(*Visit)(TElemType))
{
	BiThrTree p;
	p = T->lchild; // p指向根结点
	while (p != T)
	{ // 空树或遍历结束时,p==T
		while (p->LTag == Link)
			p = p->lchild;
		if (!Visit(p->data)) // 访问其左子树为空的结点
			return 0;
		while (p->RTag == Thread && p->rchild != T)
		{
			p = p->rchild;
			Visit(p->data); // 访问后继结点
		}
		p = p->rchild;
	}
	return 1;
}
int vi(TElemType c)
{
	printf("%c ", c);
	return 1;
}

int main()
{
	BiThrTree P, T;
	printf("请按先序输入二叉树(如:ab三个空格,表示a为根结点,"
		"b为左子树的二叉树)\n");
	/*按前序产生二叉树*/
	CreateBiThrTree(&T);
	/*中序遍历，并中序线索化二叉树*/
	InOrderThreading(&P, T);
	printf("中序遍历输出结果：");
	/*中序遍历(输出)二叉线索树*/
	//InOrderTraverse_Thr(P);
	InOrderTraverse_Thr(P, vi);
	printf("\n");
	system("pause");
	return 0;
}