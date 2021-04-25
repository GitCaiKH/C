#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define LH +1  /*���*/
#define EH 0   /*�ȸ�*/
#define RH -1  /*�Ҹ�*/

typedef int Status;

/*�������Ķ���������ṹ����*/
/*���ṹ*/
typedef struct BiTNode
{
	/*�������*/
	int data;
	/*����ƽ������*/
	int bf;
	/*���Һ���ָ��*/
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

/*�����������������*/
void InOrderTraverse_bf(BiTree T)
{
	if (T == NULL)
		return;
	else
	{
		InOrderTraverse_bf(T->lchild);
		printf("%d\n", T->data);
		InOrderTraverse_bf(T->rchild);
	}
}

void Traverse(BiTree T)
{
	printf("\n������������������Ϊ��");
	InOrderTraverse_bf(T);
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

/*����pΪ���Ķ�������������������*/
/*����֮��pָ���µ�������㣬����ת����֮ǰ
  ���������ĸ����0*/
void L_Rotate(BiTree* P)
{
	BiTree R;
	/*Rָ��P�������������*/
	R = (*P)->rchild;
	/*R���������ҽ�ΪP��������*/
	(*P)->rchild = R->lchild;
	R->lchild = (*P);
	/*Pָ���µĸ����*/
	*P = R;
}

/*����pΪ���Ķ�������������������*/
/*����֮��pָ���µ�������㣬����ת����֮ǰ
  ���������ĸ����*/
void R_Rotate(BiTree* P)
{
	BiTree L;
	/*Lָ��P�������������*/
	L = (*P)->lchild;
	/*L���������ҽ�ΪP��������*/
	(*P)->lchild = L->rchild;
	L->rchild = (*P);
	/*Pָ���µĸ����*/
	*P = L;
}

/*����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����*/
/*���㷨���ʱ��ָ��Tָ���µĸ����*/
void LeftBalance(BiTree* T)
{
	BiTree L, Lr;
	/*Lָ��T�������������*/
	L = (*T)->lchild;
	switch (L->bf)
	{
	/*���T����������ƽ��ȣ�������Ӧƽ�⴦��*/
	/*�½�������T�����Ӻ��������ϣ�Ҫ������������*/
	case LH:
		(*T)->bf = L->bf = EH;
		R_Rotate(T);
		break;
	/*�½�������T�����ӵ��������ϣ�Ҫ��˫������*/
	case RH:
		/*Lrָ��T�����ӵ���������*/
		Lr = L->rchild;
		/*�޸�T�������ӵ�ƽ������*/
		switch (Lr->bf)
		{
		case LH:
			(*T)->bf = RH;
			L->bf = EH;
			break;
		case EH:
			(*T)->bf = L->bf = EH;
			break;
		case RH:
			(*T)->bf = EH;
			L->bf = LH;
			break;
		}
		Lr->bf = EH;
		/*��T��������������ƽ�⴦��*/
		L_Rotate(&(*T)->lchild);
		/*��T������ƽ�⴦��*/
		R_Rotate(T);
	}
}

/*����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����*/
/*���㷨���ʱ��ָ��Tָ���µĸ����*/

void RightBalance(BiTree* T)
{
	BiTree R, Rl;
	/*Rָ��T�������������*/
	R = (*T)->rchild;
	switch (R->bf)
	{
	/*���T����������ƽ��ȣ�������Ӧƽ�⴦��*/
	/*�½�������T���Һ��Ӻ��������ϣ�Ҫ������������*/
	case RH:
		(*T)->bf = R->bf = EH;
		L_Rotate(T);
		break;
	/*�½�������T���Һ��ӵ��������ϣ�Ҫ��˫������*/
	case LH:
		/*Rlָ��T���Һ��ӵ���������*/
		Rl = R->lchild;
		/*�޸�T�����Һ��ӵ�ƽ������*/
		switch (Rl->bf)
		{
		case RH:
			(*T)->bf = LH;
			R->bf = EH;
			break;
		case EH:
			(*T)->bf = R->bf = EH;
			break;
		case LH:
			(*T)->bf = EH;
			R->bf = RH;
			break;
		}
		Rl->bf = EH;
		/*��T��������������ƽ�⴦��*/
		R_Rotate(&(*T)->rchild);
		/*��T������ƽ�⴦��*/
		L_Rotate(T);
	}
}

/*����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ��*/
/*����Ԫ��Ϊe���½�㲢����1�����򷵻�0����������ʹ����������ʧȥƽ�⣬*/
/*����ƽ����ת������������taller��ӳT�������*/
Status InsertAVL(BiTree* T, int e, Status* taller)
{
	if (!*T)
	{
		/*�����½�㣬�������ߡ�����tallerΪTRUE*/
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}
	else
	{
		if (e == (*T)->data)
		{
			/*�����Ѵ��ں�e����ͬ�ؼ��ֵĽ�����ٲ���*/
			*taller = FALSE;
			return FALSE;
		}
		if (e < (*T)->data)
		{
			/*�ͼ�����T���������н�������*/
			/*δ����*/
			if (!InsertAVL(&(*T)->lchild, e, taller))
				return FALSE;
			/*�Ѳ��뵽T�����������������������ߡ�*/
			if (*taller)
			{
				/*���T��ƽ���*/
				switch ((*T)->bf)
				{
				/*ԭ�����������������ߣ���Ҫ����ƽ�⴦��*/
				case LH:
					LeftBalance(T);
					*taller = FALSE;
					break;
				/*ԭ�����������ȸߣ��������������߶�������*/
				case EH:
					(*T)->bf = LH;
					*taller = TRUE;
					break;
				/*ԭ�����������������ߣ������������ȸ�*/
				case RH:
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				}
			}
		}
		else
		{
			/*�ͼ�����T���������н�������*/
			/*δ����*/
			if (!InsertAVL(&(*T)->rchild, e, taller))
				return FALSE;
			/*�Ѳ��뵽T���������������������ߡ�*/
			if (*taller)
			{
				/*���T��ƽ���*/
				switch ((*T)->bf)
				{
				/*ԭ�����������������ߣ������������ȸ�*/
				case LH:
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				/*ԭ�����������ȸߣ��������������Ӷ�������*/
				case EH:
					(*T)->bf = RH;
					*taller = TRUE;
					break;
				/*ԭ�����������������ߣ���Ҫ����ƽ�⴦��*/
				case RH:
					RightBalance(T);
					*taller = FALSE;
					break;
				}
			}
		}
	}
	return TRUE;
}

int main()
{
	int i;
	int a[10] = { 3, 2, 1, 4, 5, 6, 7, 10, 9, 8 };
	BiTree T = NULL;
	Status taller;
	for (i = 0; i < 10; i++)
	{
		InsertAVL(&T, a[i], &taller);
	}
	Traverse(T);
	system("pause");
	return 0;
}