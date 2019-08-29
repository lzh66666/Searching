#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OVERFLOW -2
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef int IndexOfKey;

#define STR_MAX_SIZE 25 //字符串的最大串长

//关键字为字符串型
typedef char KeyType[STR_MAX_SIZE];

//数据元素类型
typedef struct
{
	KeyType key; //关键字域
	//... //其他域
}ElemType;

//对两个关键字比较约定为如下的宏定义
#define EQ( a,b ) ( !strcmp( (a),(b) ) )
#define LT( a,b ) ( strcmp( (a),(b) ) < 0 )
#define LQ( a,b ) ( strcmp( (a),(b) ) <= 0 )

//---------------静态查找表的线性链表存储结构---------
typedef struct LNode
{
	ElemType elem; //数据
	struct LNode* next;
}LNode,*LSTable;

//表的创建
Status Create(LSTable& ST,int n)
{
	printf("请输入%d个字符串,每个字符串以回车结束!\n",n);
	getchar();
	int i;
	ST = (LSTable)malloc(sizeof(LNode)); //创建头结点
	if (!ST)
		return FALSE;
	ST->next = NULL;
	
	LSTable p = ST; //用于指示表中最后一个结点
	LSTable q = NULL;
	for(i=0;i<n;i++)
	{
		q=(LSTable)malloc(sizeof(LNode)); //新建结点
		if(!q)
			return FALSE;
		//表尾插入法
		gets(q->elem.key);
		p->next=q;
		q->next=NULL;
		p=q;
	}
	
	return TRUE;
}

//销毁表
Status Destroy(LSTable& ST)
{
	LSTable p=NULL;
	LSTable q=NULL;
	p=q=ST;
	while(q)
	{
		p=q;
		q=p->next;
		free(p);
		p=NULL;
	}
	return TRUE;
}

//顺序查找,由参数result带回查询结果数据，查询不成功，带回一个空值
Status Search_Seq(const LSTable &ST,KeyType key,ElemType &result )
{
	LSTable p = ST->next; //p指向第一个结点
	
	//从第一个结点开始搜索
	while(p)
	{
		if(EQ( p->elem.key, key))
		{
			result = p->elem;
			return TRUE; //查找成功
		}
		p=p->next;
	}
	memset(result.key, 0, STR_MAX_SIZE); //赋空值
	return FALSE; //查找失败
}
//打印表中的内容
Status Traverse(const LSTable &ST )
{
	LSTable p = ST->next; //指向第一个表结点
	while(p)
	{
		printf("%s\n", p->elem.key);
		p=p->next;
	}
	return TRUE;
}

int main(int argc,char **argv){
	LSTable ST;
	int n;
	printf("请输入创建字符串表的个数：\n");
	scanf("%d",&n);
	if(Create(ST,n))
		printf("创建成功!\n");
	
	printf("表中的内容为：\n");
	Traverse(ST);
	
	KeyType key;
	ElemType result;
	printf("请输入查找关键字:\n");
	gets(key);
	
	if(Search_Seq(ST,key,result))
	{
		printf("查找成功!\n");
		printf("查找的记录为:%s\n", result.key );
	}
	else
		printf("查找失败"); 
	if(Destroy(ST))
		printf("清理完毕!\n");
	
	return 0;
}
