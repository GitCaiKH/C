#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW 0

typedef char TElemType;
typedef int Status;

/*�������Ķ��������洢�ṹ����*/
/*Link = 0 ��ʾָ�����Һ���ָ��*/
/*Thread = 1 ��ʾָ��ǰ�����̵�����*/
typedef enum
{
	Link, 
	Thread
}PointerTag;

/*���������洢���ṹ*/
typedef struct BiThrNode
{
	/*�������*/
	TElemType data;
	/*���Һ���ָ��*/
	struct BiThrNode* lchild, * rchild;
	/*���ұ�ʾ*/
	PointerTag LTag, RTag;
}BiThrNode, * BiThrTree;

BiThrTree pre;   /*ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľ��*/
TElemType Nil = ' ';/*�ַ����Կո��Ϊ��*/

/*��ǰ�������ʽ����һ�ö�����*/
void CreateBiThrTree(BiThrTree* T)
{
	TElemType c;
	scanf("%c", &c);
	/*#��ʾ������*/
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
		/*�����ӣ�����Ϊ0��ָ������*/
		if ((*T)->lchild)
			(*T)->LTag = Link;
		CreateBiThrTree(&((*T)->rchild));
		/*���Һ��ӣ�����Ϊ0��ָ���Һ���*/
		if ((*T)->rchild)
			(*T)->RTag = Link;
	}
}

/*���������������������*/
void InThreading(BiThrTree p)
{
	if (p)
	{
		/*�ݹ�������������*/
		InThreading(p->lchild);
		/*û������*/
		if (!p->lchild)
		{
			/*ǰ������*/
			p->LTag = Thread;
			/*����ָ��ָ��ǰ��*/
			p->lchild = pre;
		}
		/*ǰ�����Һ���*/
		if (!pre->rchild)
		{
			/*�������*/
			pre->RTag = Thread;
			/*ǰ���Һ���ָ��ָ���̣���ǰ���p��*/
			pre->rchild = p;
		}
		/*����preָ��p��ǰ��*/
		pre = p;
		/*�ݹ�������������*/
		InThreading(p->rchild);
	}
}

void InOrderThreading(BiThrTree* p, BiThrTree T)
{
	/*����ͷ���*/
	*p = (BiThrTree)malloc(sizeof(BiThrNode));
	if (!(*p))
		exit(OVERFLOW);
	/*��־����Ϊָ��*/
	(*p)->LTag = Link;
	/*��־�Һ���Ϊ����*/
	(*p)->RTag = Thread;
	/*��ָ���ָ*/
	(*p)->rchild = *p;
	/*��������Ϊ�գ�����ָ���ָ*/
	if (!T)
		(*p)->lchild = *p;
	else
	{
		/*ͷ�����ָ��ָ�����ĸ�*/
		(*p)->lchild = T;
		pre = *p;
		/*���������������������*/
		InThreading(T);
		/*���һ�����������*/
		pre->RTag = Thread;
		pre->rchild = *p;
		(*p)->rchild = pre;
		
	}
}


/*Tָ��ͷ��㣬ͷ�������lchildָ������*/
/*ͷ�������rchildָ��������������һ�����*/
/*��������������������ʾ�Ķ�����T*/
//Status InOrderTraverse_Thr(BiThrTree T)
//{
//	BiThrTree p;
//	/*pָ������*/
//	p = T->lchild;
//	/*�������������ʱ��p == T*/
//	while (p != T)
//	{
//		/*��LTab == 0ʱѭ�����������е�һ�����*/
//		while (p->LTag == Link)
//			p = p->lchild;
//		/*��ʾ������ݣ����Ը���Ϊ�����Խ�����*/
//		printf("%c", p->data);
//		while (p->RTag == Thread && p->rchild != T)
//		{
//			p = p->rchild;
//			printf("%c ", p->data);
//		}
//		/*p��������������*/
//		p = p->rchild;
//	}
//	return OK;
//}

//�㷨6.5 P134
//�����������������T(ͷ���)�ķǵݹ��㷨��
int InOrderTraverse_Thr(BiThrTree T, int(*Visit)(TElemType))
{
	BiThrTree p;
	p = T->lchild; // pָ������
	while (p != T)
	{ // �������������ʱ,p==T
		while (p->LTag == Link)
			p = p->lchild;
		if (!Visit(p->data)) // ������������Ϊ�յĽ��
			return 0;
		while (p->RTag == Thread && p->rchild != T)
		{
			p = p->rchild;
			Visit(p->data); // ���ʺ�̽��
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
	printf("�밴�������������(��:ab�����ո�,��ʾaΪ�����,"
		"bΪ�������Ķ�����)\n");
	/*��ǰ�����������*/
	CreateBiThrTree(&T);
	/*���������������������������*/
	InOrderThreading(&P, T);
	printf("���������������");
	/*�������(���)����������*/
	//InOrderTraverse_Thr(P);
	InOrderTraverse_Thr(P, vi);
	printf("\n");
	system("pause");
	return 0;
}