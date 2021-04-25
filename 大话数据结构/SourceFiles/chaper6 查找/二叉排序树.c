#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Status;

/*�������Ķ���������ṹ����*/
/*���ṹ*/
typedef struct BiTNode
{
	/*�������*/
	int data;
	/*���Һ���ָ��*/
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;


/*��ǰ�������˳����һ��������*/
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

/*�����������������*/
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
	printf("�����������Ϊ��");
	InOrderTraverse(T);
	printf("\n");
}


int last = 0;
Status flag = TRUE;

/*�ж϶������Ƿ��Ƕ������������Ƿ���TRUE�����Ƿ���FALSE*/
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


/*�ݹ���Ҷ���������T���Ƿ����key*/
/*ָ��fָ��T��˫�ף����ʼ����ֵΪNULL*/
/*�����ҳɹ�����ָ��pָ�������Ԫ�ؽ�㣬������TRUE*/
/*����ָ��pָ�����·���Ϸ��ʵ����һ����㣬������FALSE*/
Status SearchBST(BiTree T, int key, BiTree f, BiTree* p)
{
	/*���Ҳ��ɹ�*/
	if (!T)
	{
		*p = f;
		return FALSE;
	}
	/*���ҳɹ�*/
	else if (key == T->data)
	{
		*p = T;
		return TRUE;
	}
	else if (key < T->data)
		/*����������������*/
		return SearchBST(T->lchild, key, T, p);
	else
		/*����������������*/
		return SearchBST(T->rchild, key, T, p);
}

/*������������T�в����ڹؼ��ֵ���key������Ԫ��ʱ��*/
/*����key������TRUE�����򷵻�FALSE*/
Status InsertBST(BiTree* T, int key)
{
	BiTree p, s;
	/*���Ҳ��ɹ�*/
	if (!SearchBST(*T, key, NULL, &p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p)
			/*����sΪ�µĸ����*/
			*T = s;
		else if (key < p->data)
			/*����sΪ����*/
			p->lchild = s;
		else
			/*����sΪ�Һ���*/
			p->rchild = s;
		return TRUE;
	}
	else
		/*�������йؼ�����ͬ�Ľ�㣬���ٲ���*/
		return FALSE;
}


Status Delete(BiTree* p)
{
	BiTree q, s;
	/*����������ֻ���ؽ�����������*/
	if ((*p)->rchild == NULL)
	{
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	/*����������ֻ���ؽ�����������*/
	else if ((*p)->lchild == NULL)
	{
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	/*��������������*/
	else
	{
		q = *p;
		s = (*p)->lchild;
		/*ת��Ȼ�����ҵ���ͷ(�Ҵ�ɾ����ǰ��)*/
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		/*sָ��ɾ����ֱ��ǰ��*/
		(*p)->data = s->data;
		if (q != *p)
			/*�ؽ�q��������*/
			q->rchild = s->lchild;
		else
			/*�ؽ�q��������*/
			q->lchild = s->lchild;
		free(s);
	}
	return TRUE;
}

/*������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ��*/
/*��ɾ��������Ԫ�ؽ��*/
/*������TRUE�����򷵻�FALSE*/
Status DeleteBST(BiTree* T, int key)
{
	/*�����ڹؼ��ֵ���key������Ԫ��*/
	if (!*T)
		return FALSE;
	else
	{
		/*�ҵ��ؼ��ֵ���key������Ԫ��*/
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
		printf("�Ƕ�����������\n");
	else
		printf("���Ƕ�����������\n");
	Status FindResult = InsertBST(&T, 12);
	if (FindResult == TRUE)
		printf("����ɹ���");
	else
		printf("����ʧ�ܣ�");
	Traverse(T);
	Status DeleteResult = DeleteBST(&T, 12);
	if(DeleteResult == TRUE)
		printf("ɾ���ɹ���");
	else
		printf("ɾ��ʧ�ܣ�");
	Traverse(T);
	system("pause");
	return 0;
}