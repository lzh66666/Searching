#include <iostream>
#include<stdlib.h>
#include<stdio.h> 
#define EH 0 //等高
#define LH 1 //左高
#define RH -1 //右高

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define FALSE 0
#define TRUE 1

//对两个关键字比较约定为如下的宏定义
#define EQ( a,b ) ( (a) == (b) )
#define LT( a,b ) ( (a) < (b) )
#define LQ( a,b ) ( (a) <= (b) )

typedef int Status;
//关键字为整型
typedef int KeyType;	

//数据元素类型
typedef struct	{
   KeyType key; 	//关键字域
   //... 	 //其他域
}ElemType;

typedef struct BSTNode{
	ElemType data;
	int bf;				//平衡因子 
	struct BSTNode* lchild;
	struct BSTNode* rchild;
}BSTNode,*BSTree;

//---------------------------------初始化查找表-------------------------------------------- 
Status InitDSTable(BSTree *DT)
{ /* 操作结果: 构造一个空的动态查找表DT */
   *DT=NULL;
   return OK;
}
 
//---------------------------------销毁查找表---------------------------------------------- 
Status DestroyDSTable(BSTree &DT){ 				/* 初始条件: 动态查找表DT存在。操作结果: 销毁动态查找表DT */
	if(DT) 									/* 非空树 */
	{	
		if(DT->lchild) 						/* 有左孩子 */
			DestroyDSTable(DT->lchild); 	/* 销毁左孩子子树 */
		if(DT->rchild) 						/* 有右孩子 */
			DestroyDSTable(DT->rchild);		/* 销毁右孩子子树 */
		free(DT); 								/* 释放根结点 */
		DT=NULL;								/* 空指针赋0 */
	}
	return OK;
}

//---------------------------------------查找操作------------------------------------------------- 
int SearchAve(BSTree &T,KeyType key){ 
	/* 在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素， */
   /* 若查找成功，则返回指向该数据元素结点的指针,否则返回空指针。 */
	if(!T){
		printf("该树以空！");
		return ERROR;
	}
	else if(EQ(key,T->data.key))
		return T->data.key; 							/* 查找结束 */
	else if LT(key,T->data.key) 						/* 在左子树中继续查找 */
		SearchAve(T->lchild,key);
	else
		SearchAve(T->rchild,key); 						/* 在右子树中继续查找 */
}

Status Delete(BSTree &p){
	//从二叉排序树中删除结点p，并重接它的左或右子树
	BSTree q,s;
	if(!p){
		printf("该二叉排序树已空！");
		return FALSE;
	}
	else{
		if(!p->rchild){				//只需重接它的左子树 
			q=p;
			p=p->lchild;
			free(q);
		} 
		else if(!p->lchild){		//只需重接它的右子树 
			q=p;
			p=p->rchild;
			free(q);
		}
		else{						//左右子树均不空 
			q=p;
			s=p->lchild; 
			while(s->rchild){		//转左，然后向右到尽头 
				q=s;
				s=s->rchild;
			}
			p->data.key=s->data.key;		//s指向被删结点的“前驱”
			if(q!=p)
				q->rchild=s->lchild;	//重接*q的的右子树 
			else
				q->lchild=s->lchild; 	//重接*q的的左子树 
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

//------------------------------------------左旋操作--------------------------------------------------- 
void L_Rotate(BSTree &p)
{ 	/* 对以*p为根的二叉排序树作左旋处理，处理之后p指向新的树根结点，即旋转 */
	/* 处理之前的右子树的根结点。 */
	BSTree rc;
	rc=p->rchild; 							/* rc指向p的右子树根结点 */
	p->rchild=rc->lchild; 					/* rc的左子树挂接为p的右子树 */
	rc->lchild=p;
	p=rc; 									/* p指向新的根结点 */
}
 
 //-------------------------------------------右旋操作---------------------------------------------------- 
void R_Rotate(BSTree &p){ 			/*对以*p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点*/
	BSTree lc;
	lc=p->lchild; 							/* lc指向p的左子树根结点 */
	p->lchild=lc->rchild; 					/* lc的右子树挂接为p的左子树 */
	lc->rchild=p;
	p=lc; 									/* p指向新的根结点 */
}

//--------------------------------------------左平衡旋转操作------------------------------------------------ 
void LeftBalance(BSTree &T){ 			/* 对以指针T所指结点为根的二叉树作左平衡旋转处理，本算法结束时，指针T指向新的根结点。*/
	BSTree lc,rd;
	lc=T->lchild;						/* lc指向*T的左子树根结点 */
	switch(lc->bf){ 					/* 检查*T的左子树的平衡度，并作相应平衡处理 */
		case LH:						/* 新结点插入在*T的左孩子的左子树上，要作单右旋处理 */
			T->bf=lc->bf=EH;
			R_Rotate(T);
			break;
		case RH: 						/* 新结点插入在*T的左孩子的右子树上，要作双旋处理 */
			rd=lc->rchild; 				/* rd指向*T的左孩子的右子树根 */
			switch(rd->bf){ 			/* 修改*T及其左孩子的平衡因子 */
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
			L_Rotate(T->lchild); 			/* 对*T的左子树作左旋平衡处理 */
			R_Rotate(T); 					/* 对*T作右旋平衡处理 */
	}
}

//-----------------------------------------------右平衡旋转操作----------------------------------------------------- 
void RightBalance(BSTree &T){			/* 对以指针T所指结点为根的二叉树作右平衡旋转处理，本算法结束时，指针T指向新的根结点 */
	BSTree rc,rd;
	rc=T->rchild; 						/* rc指向*T的右子树根结点 */
	switch(rc->bf){ 					/* 检查*T的右子树的平衡度，并作相应平衡处理 */
		case RH: 						/* 新结点插入在*T的右孩子的右子树上，要作单左旋处理 */
			T->bf=rc->bf=EH;
			L_Rotate(T);
			break;
		case LH: 						/* 新结点插入在*T的右孩子的左子树上，要作双旋处理 */
			rd=rc->lchild;				/* rd指向*T的右孩子的左子树根 */
			switch(rd->bf){ 			/* 修改*T及其右孩子的平衡因子 */
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
			R_Rotate(T->rchild); 				/* 对*T的右子树作右旋平衡处理 */
			L_Rotate(T); 						/* 对*T作左旋平衡处理 */
	}
}

//---------------------------------------------插入操作------------------------------------------------------- 
Status InsertAVL(BSTree &T,ElemType e,Status &taller){
	/* 若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个 */ 
    /* 数据元素为e的新结点，并返回1，否则返回0。若因插入而使二叉排序树 */
    /* 失去平衡，则作平衡旋转处理，变量taller反映T长高与否。 */
	if(!T){ 					/* 插入新结点，树“长高”，置taller为TRUE */
		T=(BSTree)malloc(sizeof(BSTNode));
		T->data.key=e.key;
		T->lchild=T->rchild=NULL;
		T->bf=EH;
		taller=TRUE;
	}
	else{
		if EQ(e.key,T->data.key){ 						/* 树中已存在和e有相同关键字的结点则不再插入 */
			taller=FALSE;
			return FALSE;
		}
		if LT(e.key,T->data.key){ 						/* 应继续在*T的左子树中进行搜索 */
			if(!InsertAVL(T->lchild,e,taller)) 			/* 未插入 */
				return FALSE;
			if(taller) 									/*  已插入到*T的左子树中且左子树“长高” */
				switch(T->bf) 							/* 检查*T的平衡度 */
				{
					case LH: 							/* 原本左子树比右子树高，需要作左平衡处理 */
					    LeftBalance(T);
					    taller=FALSE;
					    break;
					case EH: 							/* 原本左、右子树等高，现因左子树增高而使树增高 */
					    T->bf=LH;
					    taller=TRUE;
					    break;
					case RH: 
						T->bf=EH; 						/* 原本右子树比左子树高，现左、右子树等高 */
					    taller=FALSE;
					    break;
				}
		}
		else{ 									/* 应继续在*T的右子树中进行搜索 */
		    if(!InsertAVL(T->rchild,e,taller)) 			/* 未插入 */
		     	return FALSE;
		    if(taller)							/* 已插入到T的右子树且右子树“长高” */
		     	switch(T->bf){ 					/* 检查T的平衡度 */
			       	case LH: 					/* 原本左子树比右子树高，现左、右子树等高 */
					   	T->bf=EH; 
			            taller=FALSE;
			            break;
			       	case EH: 					/* 原本左、右子树等高，现因右子树增高而使树增高 */
			            T->bf=RH;
			            taller=TRUE;
			        	break;
			   		case RH: 					/* 原本右子树比左子树高，需要作右平衡处理 */
				        RightBalance(T);
				        taller=FALSE;
				        break;
				}
	    }
	}
	return TRUE;
}

//中序遍历 
void InOrderTraverse(BSTree T)
/*中序遍历二叉排序树的递归实现*/
{
    if(T)                               	/*如果二叉排序树不为空*/
    {
        InOrderTraverse(T->lchild);     	/*中序遍历左子树*/
        printf("%4d",T->data.key);          /*访问根结点*/
        InOrderTraverse(T->rchild);         /*中序遍历右子树*/
    }
}

Status CreateAVL(BSTree &T)
{
	ElemType e;
	Status taller=0;
	int n;
	printf("请输入二叉排序树的关键字个数：\n");
	scanf("%d",&n);
	printf("请输入二叉排序树的关键字(元素之间用空格隔开)\n");
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
	printf("\t\t   |--------|     平衡二叉树操作    |-------|\n");
	printf("\t\t   |        |                       |       |\n");
	printf("\t\t   |         ========================       |\n");
	printf("\t\t   |                                        |\n");
	printf("\t\t   |         请选择你的操作：               |\n");
	printf("\t\t   |         [1]创建平衡二叉树              |\n");
	printf("\t\t   |         [2]平衡二叉树插入              |\n");
	printf("\t\t   |         [3]平衡二叉树删除              |\n");
	printf("\t\t   |         [4]平衡二叉树查找              |\n");
	printf("\t\t   |         [5]中序遍历平衡二叉树          |\n");
	printf("\t\t   |         [6]销毁平衡二叉树              |\n");
	printf("\t\t   |         [7]退出                        |\n");
	printf("\t\t   |-======================================-|\n");
	printf("\t\t   |                 欢迎修改               |\n");
	printf("\t\t   |-======================================-|\n");
	printf("请选择你要进行的操作(1/2/3/4/5/6/7):");
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
					printf("创建成功！\n"); 
				}
			    Menu();
			    break;
			case 2:
				printf("请输入你要插入的元素：\n");
				scanf("%d",&e.key);
				if(!InsertAVL(T,e,taller)){
					printf("插入失败，该二叉排序树中已有该关键字!\n"); 
				}
				else
					printf("插入成功！");
				Menu();
			    break;
			case 3:
				printf("请输入要删除的二叉树的关键字：\n");
				scanf("%d",&key);
				if(DeleteAve(T,key)){
					printf("删除成功！"); 
				}
				Menu();
			    break;
			case 4:
				printf("请输入要查找的关键字");
				scanf("%d",&key); 
				n=SearchAve(T,key);
				if(n) {
					printf("查找成功！\n关键字为：%d",n);
				}
				Menu();
			    break;
			case 5:
				printf("中序遍历结果为：\n");
				InOrderTraverse(T);
				Menu();
			    break;
			case 6:
				if(DestroyDSTable(T))
				{
					printf("销毁成功！\n");
				}
				Menu();
				break;
		    default:
				printf("输入有误,请重新输入!\n");
				Menu();
				break;
		}
		scanf("%d",&i);
	}
	return 0;
 	
	return 0;
}
