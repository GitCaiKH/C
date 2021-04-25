#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Status;

/*二叉树的二叉链表结点结构定义*/
/*结点结构*/
typedef struct BiTNode
{
	/*结点数据*/
	int data;
	/*左右孩子指针*/
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;


/*以前序遍历的顺序建立一个二叉树*/
void PreOrderCreateBiTree(BiTree* T)
{
	int e;
	scanf("%d", &e);
	if (e == -1)
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTree)malloc(sizeof(struct BiTNode));
		(*T)->data = e;
		PreOrderCreateBiTree(&((*T)->lchild));
		PreOrderCreateBiTree(&((*T)->rchild));
	}
}

/*中序遍历二叉排序树*/
void InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	else
	{
		InOrderTraverse(T->lchild);
		printf("%d ", T->data);
		InOrderTraverse(T->rchild);
	}
}

void Traverse(BiTree T)
{
	printf("操作后二叉树为：");
	InOrderTraverse(T);
	printf("\n");
}


int last = 0;
Status flag = TRUE;

/*判断二叉树是否是二叉排序树，是返回TRUE，不是返回FALSE*/
Status Is_BSTree(BiTree T)
{
	if (flag && T->lchild)
		Is_BSTree(T->lchild);
	if (last > T->data)
		flag = FALSE;
	last = T->data;
	if (flag && T->rchild)
		Is_BSTree(T->rchild);
	return flag;
}


/*递归查找二叉排序树T中是否存在key*/
/*指针f指向T的双亲，其初始调用值为NULL*/
/*若查找成功，则指针p指向该数据元素结点，并返回TRUE*/
/*否则指针p指向查找路径上访问的最后一个结点，并返回FALSE*/
Status SearchBST(BiTree T, int key, BiTree f, BiTree* p)
{
	/*查找不成功*/
	if (!T)
	{
		*p = f;
		return FALSE;
	}
	/*查找成功*/
	else if (key == T->data)
	{
		*p = T;
		return TRUE;
	}
	else if (key < T->data)
		/*在左子树继续查找*/
		return SearchBST(T->lchild, key, T, p);
	else
		/*在右子树继续查找*/
		return SearchBST(T->rchild, key, T, p);
}

/*当二叉排序树T中不存在关键字等于key的数据元素时，*/
/*插入key并返回TRUE，否则返回FALSE*/
Status InsertBST(BiTree* T, int key)
{
	BiTree p, s;
	/*查找不成功*/
	if (!SearchBST(*T, key, NULL, &p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p)
			/*插入s为新的根结点*/
			*T = s;
		else if (key < p->data)
			/*插入s为左孩子*/
			p->lchild = s;
		else
			/*插入s为右孩子*/
			p->rchild = s;
		return TRUE;
	}
	else
		/*树中已有关键字相同的结点，不再插入*/
		return FALSE;
}


Status Delete(BiTree* p)
{
	BiTree q, s;
	/*右子树空则只需重接它的左子树*/
	if ((*p)->rchild == NULL)
	{
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	/*左子树空则只需重接它的右子树*/
	else if ((*p)->lchild == NULL)
	{
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	/*左右子树均不空*/
	else
	{
		q = *p;
		s = (*p)->lchild;
		/*转左，然后向右到尽头(找待删结点的前驱)*/
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		/*s指向被删结点的直接前驱*/
		(*p)->data = s->data;
		if (q != *p)
			/*重接q的右子树*/
			q->rchild = s->lchild;
		else
			/*重接q的左子树*/
			q->lchild = s->lchild;
		free(s);
	}
	return TRUE;
}

/*若二叉排序树T中存在关键字等于key的数据元素时，*/
/*则删除该数据元素结点*/
/*并返回TRUE，否则返回FALSE*/
Status DeleteBST(BiTree* T, int key)
{
	/*不存在关键字等于key的数据元素*/
	if (!*T)
		return FALSE;
	else
	{
		/*找到关键字等于key的数据元素*/
		if (key == (*T)->data)
			return Delete(T);
		else if (key < (*T)->data)
			return DeleteBST(&((*T)->lchild), key);
		else
			return DeleteBST(&((*T)->rchild), key);
	}
}

int main()
{
	BiTree T;
	PreOrderCreateBiTree(&T);
	Traverse(T);
	flag = Is_BSTree(T);
	if (flag == TRUE && T)
		printf("是二叉排序树！\n");
	else
		printf("不是二叉排序树！\n");
	Status FindResult = InsertBST(&T, 12);
	if (FindResult == TRUE)
		printf("插入成功！");
	else
		printf("插入失败！");
	Traverse(T);
	Status DeleteResult = DeleteBST(&T, 12);
	if(DeleteResult == TRUE)
		printf("删除成功！");
	else
		printf("删除失败！");
	Traverse(T);
	system("pause");
	return 0;
}