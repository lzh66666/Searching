#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW -2
#define FALSE 0
#define TRUE 1

typedef int Status;
//关键字为整型
typedef int KeyType;	

//数据元素类型
typedef struct	{
	KeyType key; 	//关键字域
	//... 	 //其他域
}SElemType;

//对两个关键字比较约定为如下的宏定义
#define EQ( a,b ) ( (a) == (b) )
#define LT( a,b ) ( (a) < (b) )
#define LQ( a,b ) ( (a) <= (b) )

//---------------静态查找表的顺序存储结构---------
typedef struct 	{
	SElemType* elem; 	//数据元素存储空间基址，建表时按实际长度分配，0号单元不用
	int length;	 //表长
}SSTable;

/*	操作结果：构造一个含n个数据元素的静态查找表ST
	函数： Create
*/
Status Create( SSTable& ST, int n ){
	ST.elem = (SElemType*)malloc( (n+1)*sizeof(SElemType) );
	if(!ST.elem)
		exit(OVERFLOW);
	printf("请任意输入%d个整数，以空格分开:", n );
	int i = 0;
	for( i = 1; i <= n; i++ )
	{
		scanf("%d",&(ST.elem[i]) );
	}
	ST.length = n;
	return TRUE;
}


/*初始条件：静态查找表存在
操作结果：销毁表ST*/

Status Destroy( SSTable& ST ){
	free(ST.elem);
	ST.elem = NULL;
	ST.length = 0;
	return TRUE;
}


/*
初始条件：静态查找表存在,key为为关键字类型相
同的给定值
操作结果：若ST中存在其关键字等于key的数据元素
则函数值为该元素在表中的位置,否则为
 0
*/
//原始版 
int Search_Seq1(const SSTable &ST, const KeyType &key ){
	int i=1;
	while(i<=ST.length && !EQ(ST.elem[i].key,key))
		++i;
	if(i<=ST.length)
		return i;
	else
		return 0;
} 

//改进版 
int Search_Seq2(const SSTable& ST, const KeyType& key ){
	ST.elem[0].key = key; //0号位置设置一个"哨兵"
	int i = 0;
	for ( i = ST.length; !EQ( ST.elem[i].key, key); --i );//从后往前找
	return i; //找不到时返回0
}


/*=============================================
* 初始条件：静态查找表存在
* 操作结果：将表中的元素按升序排列
*=============================================*/
Status AscElem(SSTable &ST){
	SElemType temp; //中间变量
	int i = 0;
	int j = 0;
	for ( i = 1; i <= ST.length; i++ ){
		int index = i;
		for ( j = i+1; j <= ST.length; j++ )
			if ( ST.elem[index].key > ST.elem[j].key )
				index = j;
		if ( index != i )
		{
			temp = ST.elem[i];
			ST.elem[i] = ST.elem[index];
			ST.elem[index] = temp;
		}
	}
	return TRUE;
}


/*=============================================
* 初始条件：静态查找表存在
* 操作结果：折半查找
*=============================================*/

int Search_Bin( const SSTable& ST, KeyType key ){
	int low = 1;
	int high = ST.length;
	int mid =0;
	while( low <= high )
	{
		mid = (low + high )/2;
		if ( EQ(key, ST.elem[mid].key ))
		{
			return mid;
		}
		else if (LT(key, ST.elem[mid].key))
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return 0;
}

/*=============================================
?*函数功能：打印元素
?*=============================================*/
Status VisitElem( const SElemType& elem ){
	printf("%d", elem );
	return TRUE;
}


/*=============================================
*函数功能：打印静态查找表中的元素
*=============================================*/

Status Traverse(const SSTable& ST, Status (*Visit)( const SElemType&) ){
	int i = 0;
	for ( i = 1; i <= ST.length; i++ )
	{
		if(!Visit(ST.elem[i]))
		{
			return FALSE;
		}
		printf("\n");
	}
	return TRUE;
}

/*==============================================
*函数功能：操作菜单
*==============================================*/

void Menu(void){
	//界面设计仅作测试使用
	//system("COLOR 77");
	printf("\t\t             =======================         \n");
	printf("\t\t            |                       |        \n");
	printf("\t\t   |--------|   顺序静态查找表操作  |-------|\n");
	printf("\t\t   |        |                       |       |\n");
	printf("\t\t   |         =======================        |\n");
	printf("\t\t   |                                        |\n");
	printf("\t\t   |         请选择你的操作：               |\n");
	printf("\t\t   |         [1]创建静态查找表              |\n");
	printf("\t\t   |         [2]销毁静态查找表              |\n");
	printf("\t\t   |         [3]顺序查找(原始版)            |\n");
	printf("\t\t   |         [4]顺序查找(改进版)            |\n");
	printf("\t\t   |         [5]折半查找                    |\n");
	printf("\t\t   |         [6]查看表元素                  |\n");
	printf("\t\t   |         [7]退出                        |\n");
	printf("\t\t   |-======================================-|\n");
	printf("\t\t   |                 欢迎修改               |\n");
	printf("\t\t   |-======================================-|\n");
	printf("请选择你要进行的操作(1/2/3/4/5/6/7):");
}

int main(int argc,char **argv){
	Menu();
	int i = 0;
	int n = 0; //要创建的元素个数
	int index;  //记录查询函数返回的索引
	SSTable ST;
	KeyType key; //查找关键字
	scanf("%d",&i);
	while( i != 7)
	{
		switch( i )
		{
			case 1:
				printf("请输入创建表中的元素个数:");
				scanf("%d",&n);
				if(Create(ST, n))
					printf("创建成功!\n");
				Menu();
				break;
			case 2:
				if(Destroy(ST))
					printf("销毁成功！\n");
				Menu();
				break;
			case 3:
				printf("请输入查找关键字:");
				scanf("%d", &key);
				index = Search_Seq1(ST, key);
				if (index)
					printf("查找成功!这是第%d条记录\n", index);
				else
					printf("表中无此元素\n");
				Menu();
				break; 
			case 4:
				printf("请输入查找关键字:");
				scanf("%d", &key);
				index = Search_Seq2(ST, key);
				if (index)
					printf("查找成功!这是第%d条记录\n", index);
				else
					printf("表中无此元素\n");
				Menu();
				break;
			case 5:
				AscElem(ST); //先将表中的元素按升序排列
				printf("表中的元素已按升序排列\n");
				printf("请输入查找关键字:");
				scanf("%d", &key);
				index = Search_Bin(ST, key);
				if (index )
					printf("查找成功!这是第%d条记录\n", index);
				else
					printf("表中无此元素\n");
				Menu();
				break;
			case 6:
				printf("表中的元素：\n");
				Traverse(ST,VisitElem);
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
}

