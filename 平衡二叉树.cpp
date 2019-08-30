#include <iostream>
#include<stdlib.h>
#include<stdio.h> 
#define EH 0 //�ȸ�
#define LH 1 //���
#define RH -1 //�Ҹ�

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define FALSE 0
#define TRUE 1

//�������ؼ��ֱȽ�Լ��Ϊ���µĺ궨��
#define EQ( a,b ) ( (a) == (b) )
#define LT( a,b ) ( (a) < (b) )
#define LQ( a,b ) ( (a) <= (b) )

typedef int Status;
//�ؼ���Ϊ����
typedef int KeyType;	

//����Ԫ������
typedef struct	{
   KeyType key; 	//�ؼ�����
   //... 	 //������
}ElemType;

typedef struct BSTNode{
	ElemType data;
	int bf;				//ƽ������ 
	struct BSTNode* lchild;
	struct BSTNode* rchild;
}BSTNode,*BSTree;

//---------------------------------��ʼ�����ұ�-------------------------------------------- 
Status InitDSTable(BSTree *DT)
{ /* �������: ����һ���յĶ�̬���ұ�DT */
   *DT=NULL;
   return OK;
}
 
//---------------------------------���ٲ��ұ�---------------------------------------------- 
Status DestroyDSTable(BSTree &DT){ 				/* ��ʼ����: ��̬���ұ�DT���ڡ��������: ���ٶ�̬���ұ�DT */
	if(DT) 									/* �ǿ��� */
	{	
		if(DT->lchild) 						/* ������ */
			DestroyDSTable(DT->lchild); 	/* ������������ */
		if(DT->rchild) 						/* ���Һ��� */
			DestroyDSTable(DT->rchild);		/* �����Һ������� */
		free(DT); 								/* �ͷŸ���� */
		DT=NULL;								/* ��ָ�븳0 */
	}
	return OK;
}

//---------------------------------------���Ҳ���------------------------------------------------- 
int SearchAve(BSTree &T,KeyType key){ 
	/* �ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ� */
   /* �����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ��,���򷵻ؿ�ָ�롣 */
	if(!T){
		printf("�����Կգ�");
		return ERROR;
	}
	else if(EQ(key,T->data.key))
		return T->data.key; 							/* ���ҽ��� */
	else if LT(key,T->data.key) 						/* ���������м������� */
		SearchAve(T->lchild,key);
	else
		SearchAve(T->rchild,key); 						/* ���������м������� */
}

Status Delete(BSTree &p){
	//�Ӷ�����������ɾ�����p�����ؽ��������������
	BSTree q,s;
	if(!p){
		printf("�ö����������ѿգ�");
		return FALSE;
	}
	else{
		if(!p->rchild){				//ֻ���ؽ����������� 
			q=p;
			p=p->lchild;
			free(q);
		} 
		else if(!p->lchild){		//ֻ���ؽ����������� 
			q=p;
			p=p->rchild;
			free(q);
		}
		else{						//�������������� 
			q=p;
			s=p->lchild; 
			while(s->rchild){		//ת��Ȼ�����ҵ���ͷ 
				q=s;
				s=s->rchild;
			}
			p->data.key=s->data.key;		//sָ��ɾ���ġ�ǰ����
			if(q!=p)
				q->rchild=s->lchild;	//�ؽ�*q�ĵ������� 
			else
				q->lchild=s->lchild; 	//�ؽ�*q�ĵ������� 
			free(s); 
		}
		return TRUE;	
	} 
} 

Status DeleteAve(BSTree &T,KeyType key){
	if(!T){
		return FALSE;
	}
	else{
		if(EQ(key,T->data.key)){
			return Delete(T);
		}
		else if(LT(key,T->data.key)){
			return DeleteAve(T->lchild,key);
		}
		else{
			return DeleteAve(T->rchild,key);
		}
	}
}

//------------------------------------------��������--------------------------------------------------- 
void L_Rotate(BSTree &p)
{ 	/* ����*pΪ���Ķ�����������������������֮��pָ���µ�������㣬����ת */
	/* ����֮ǰ���������ĸ���㡣 */
	BSTree rc;
	rc=p->rchild; 							/* rcָ��p������������� */
	p->rchild=rc->lchild; 					/* rc���������ҽ�Ϊp�������� */
	rc->lchild=p;
	p=rc; 									/* pָ���µĸ���� */
}
 
 //-------------------------------------------��������---------------------------------------------------- 
void R_Rotate(BSTree &p){ 			/*����*pΪ���Ķ�����������������������֮��pָ���µ�������㣬����ת����֮ǰ���������ĸ����*/
	BSTree lc;
	lc=p->lchild; 							/* lcָ��p������������� */
	p->lchild=lc->rchild; 					/* lc���������ҽ�Ϊp�������� */
	lc->rchild=p;
	p=lc; 									/* pָ���µĸ���� */
}

//--------------------------------------------��ƽ����ת����------------------------------------------------ 
void LeftBalance(BSTree &T){ 			/* ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת�������㷨����ʱ��ָ��Tָ���µĸ���㡣*/
	BSTree lc,rd;
	lc=T->lchild;						/* lcָ��*T������������� */
	switch(lc->bf){ 					/* ���*T����������ƽ��ȣ�������Ӧƽ�⴦�� */
		case LH:						/* �½�������*T�����ӵ��������ϣ�Ҫ������������ */
			T->bf=lc->bf=EH;
			R_Rotate(T);
			break;
		case RH: 						/* �½�������*T�����ӵ��������ϣ�Ҫ��˫������ */
			rd=lc->rchild; 				/* rdָ��*T�����ӵ��������� */
			switch(rd->bf){ 			/* �޸�*T�������ӵ�ƽ������ */
				case LH: 
					T->bf=RH;
					lc->bf=EH;
					break;
				case EH: T->bf=lc->bf=EH;
					break;
				case RH: 
					T->bf=EH;
					lc->bf=LH;
					break;
			}
			rd->bf=EH;
			L_Rotate(T->lchild); 			/* ��*T��������������ƽ�⴦�� */
			R_Rotate(T); 					/* ��*T������ƽ�⴦�� */
	}
}

//-----------------------------------------------��ƽ����ת����----------------------------------------------------- 
void RightBalance(BSTree &T){			/* ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת�������㷨����ʱ��ָ��Tָ���µĸ���� */
	BSTree rc,rd;
	rc=T->rchild; 						/* rcָ��*T������������� */
	switch(rc->bf){ 					/* ���*T����������ƽ��ȣ�������Ӧƽ�⴦�� */
		case RH: 						/* �½�������*T���Һ��ӵ��������ϣ�Ҫ������������ */
			T->bf=rc->bf=EH;
			L_Rotate(T);
			break;
		case LH: 						/* �½�������*T���Һ��ӵ��������ϣ�Ҫ��˫������ */
			rd=rc->lchild;				/* rdָ��*T���Һ��ӵ��������� */
			switch(rd->bf){ 			/* �޸�*T�����Һ��ӵ�ƽ������ */
				case RH: 
					T->bf=LH;
					rc->bf=EH;
					break; 
				case EH:
					T->bf=rc->bf=EH;
					break;
				case LH: 
					T->bf=EH;
					rc->bf=RH;
					break;
			}
			rd->bf=EH;
			R_Rotate(T->rchild); 				/* ��*T��������������ƽ�⴦�� */
			L_Rotate(T); 						/* ��*T������ƽ�⴦�� */
	}
}

//---------------------------------------------�������------------------------------------------------------- 
Status InsertAVL(BSTree &T,ElemType e,Status &taller){
	/* ����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ�� */ 
    /* ����Ԫ��Ϊe���½�㣬������1�����򷵻�0����������ʹ���������� */
    /* ʧȥƽ�⣬����ƽ����ת��������taller��ӳT������� */
	if(!T){ 					/* �����½�㣬�������ߡ�����tallerΪTRUE */
		T=(BSTree)malloc(sizeof(BSTNode));
		T->data.key=e.key;
		T->lchild=T->rchild=NULL;
		T->bf=EH;
		taller=TRUE;
	}
	else{
		if EQ(e.key,T->data.key){ 						/* �����Ѵ��ں�e����ͬ�ؼ��ֵĽ�����ٲ��� */
			taller=FALSE;
			return FALSE;
		}
		if LT(e.key,T->data.key){ 						/* Ӧ������*T���������н������� */
			if(!InsertAVL(T->lchild,e,taller)) 			/* δ���� */
				return FALSE;
			if(taller) 									/*  �Ѳ��뵽*T�����������������������ߡ� */
				switch(T->bf) 							/* ���*T��ƽ��� */
				{
					case LH: 							/* ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
					    LeftBalance(T);
					    taller=FALSE;
					    break;
					case EH: 							/* ԭ�����������ȸߣ��������������߶�ʹ������ */
					    T->bf=LH;
					    taller=TRUE;
					    break;
					case RH: 
						T->bf=EH; 						/* ԭ�����������������ߣ������������ȸ� */
					    taller=FALSE;
					    break;
				}
		}
		else{ 									/* Ӧ������*T���������н������� */
		    if(!InsertAVL(T->rchild,e,taller)) 			/* δ���� */
		     	return FALSE;
		    if(taller)							/* �Ѳ��뵽T���������������������ߡ� */
		     	switch(T->bf){ 					/* ���T��ƽ��� */
			       	case LH: 					/* ԭ�����������������ߣ������������ȸ� */
					   	T->bf=EH; 
			            taller=FALSE;
			            break;
			       	case EH: 					/* ԭ�����������ȸߣ��������������߶�ʹ������ */
			            T->bf=RH;
			            taller=TRUE;
			        	break;
			   		case RH: 					/* ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
				        RightBalance(T);
				        taller=FALSE;
				        break;
				}
	    }
	}
	return TRUE;
}

//������� 
void InOrderTraverse(BSTree T)
/*������������������ĵݹ�ʵ��*/
{
    if(T)                               	/*���������������Ϊ��*/
    {
        InOrderTraverse(T->lchild);     	/*�������������*/
        printf("%4d",T->data.key);          /*���ʸ����*/
        InOrderTraverse(T->rchild);         /*�������������*/
    }
}

Status CreateAVL(BSTree &T)
{
	ElemType e;
	Status taller=0;
	int n;
	printf("����������������Ĺؼ��ָ�����\n");
	scanf("%d",&n);
	printf("����������������Ĺؼ���(Ԫ��֮���ÿո����)\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&e.key);
		InsertAVL(T,e,taller);
	}
	return TRUE;
}
void Menu(void)
{
	printf("\t\t             ========================        \n");
	printf("\t\t            |                       |        \n");
	printf("\t\t   |--------|     ƽ�����������    |-------|\n");
	printf("\t\t   |        |                       |       |\n");
	printf("\t\t   |         ========================       |\n");
	printf("\t\t   |                                        |\n");
	printf("\t\t   |         ��ѡ����Ĳ�����               |\n");
	printf("\t\t   |         [1]����ƽ�������              |\n");
	printf("\t\t   |         [2]ƽ�����������              |\n");
	printf("\t\t   |         [3]ƽ�������ɾ��              |\n");
	printf("\t\t   |         [4]ƽ�����������              |\n");
	printf("\t\t   |         [5]�������ƽ�������          |\n");
	printf("\t\t   |         [6]����ƽ�������              |\n");
	printf("\t\t   |         [7]�˳�                        |\n");
	printf("\t\t   |-======================================-|\n");
	printf("\t\t   |                 ��ӭ�޸�               |\n");
	printf("\t\t   |-======================================-|\n");
	printf("��ѡ����Ҫ���еĲ���(1/2/3/4/5/6/7):");
}

int main(int argc,char **argv)
{
 	Menu();
	int i,taller,n;
	BSTree T;
	ElemType e;
	KeyType key;
	scanf("%d",&i);
	while(i!=7){
		switch(i){
			case 1:
				InitDSTable(&T);
				if(CreateAVL(T)){
					printf("�����ɹ���\n"); 
				}
			    Menu();
			    break;
			case 2:
				printf("��������Ҫ�����Ԫ�أ�\n");
				scanf("%d",&e.key);
				if(!InsertAVL(T,e,taller)){
					printf("����ʧ�ܣ��ö��������������иùؼ���!\n"); 
				}
				else
					printf("����ɹ���");
				Menu();
			    break;
			case 3:
				printf("������Ҫɾ���Ķ������Ĺؼ��֣�\n");
				scanf("%d",&key);
				if(DeleteAve(T,key)){
					printf("ɾ���ɹ���"); 
				}
				Menu();
			    break;
			case 4:
				printf("������Ҫ���ҵĹؼ���");
				scanf("%d",&key); 
				n=SearchAve(T,key);
				if(n) {
					printf("���ҳɹ���\n�ؼ���Ϊ��%d",n);
				}
				Menu();
			    break;
			case 5:
				printf("����������Ϊ��\n");
				InOrderTraverse(T);
				Menu();
			    break;
			case 6:
				if(DestroyDSTable(T))
				{
					printf("���ٳɹ���\n");
				}
				Menu();
				break;
		    default:
				printf("��������,����������!\n");
				Menu();
				break;
		}
		scanf("%d",&i);
	}
	return 0;
 	
	return 0;
}
