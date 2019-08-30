#include <iostream>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

//哈希函数的构造方法:除留取余法
//处理冲突机制:链地址法

typedef struct _NODE{
	int key;
	struct _NODE* next;
}_NODE; 

typedef struct Hash_Table{
	_NODE* pChainHash[13];
}Hash_Table;
//初始化哈希表

Hash_Table *InitHashTable(){
	Hash_Table *pHashTable =(Hash_Table*)malloc(sizeof(Hash_Table));
	memset(pHashTable,0,sizeof(Hash_Table));
	return pHashTable;
} 
//在哈希表中查找元素
_NODE* SearchHash(Hash_Table* pHashTable,int key){
	if(!pHashTable)
		return NULL;
	
	_NODE* pNode=NULL;
	if(!(pNode=pHashTable->pChainHash[key%13]))
		return NULL;
	while(pNode)
	{
		if(pNode->key==key)
			return pNode;
		pNode=pNode->next;
	}
	return NULL;
}
int  InsertDataToHash(Hash_Table* pHashTable,int key){
	if(!pHashTable)
		return FALSE; 
	if(SearchHash(pHashTable,key))
		return FALSE;

	_NODE* pNewNode=(_NODE*)malloc(sizeof(_NODE));
	memset(pNewNode,0,sizeof(_NODE));
	pNewNode->key=key;
	
	_NODE* pNode=NULL;
	pNode=pHashTable->pChainHash[key%13];
	if(!pNode)
		pHashTable->pChainHash[key%13]=pNewNode;
	else
	{
		while(pNode->next)
			pNode=pNode->next;
		pNode->next=pNewNode;
	}
	return TRUE;
}

int main(int argc, char** argv) {
	Hash_Table *pHashTable,*H; 
	pHashTable=InitHashTable();
	int n,e,i;
	_NODE* p;
	
	printf("请输入元素个数:\n");
	scanf("%d",&n);
	printf("请输入元素：\n");
//	19 14 23 1 68 20 84 27 55 11 10 79
	for(i=0;i<n;i++)
	{
		scanf("%d",&e); 
		InsertDataToHash(pHashTable,e);
	}
	H = pHashTable;
	printf("\n哈希表链地址法:\n\n");
	printf("索引\t值\n");
	for(int j = 0;j < n;j++){
		printf("%d\t",j); 
		while(H->pChainHash[j]){
			printf("-> %d",H->pChainHash[j]->key);
			H->pChainHash[j] = H->pChainHash[j]->next;
		}
		printf("\n");
	} 
	
//	while(1){ 
//		getchar();
//		printf("\n请输入查找的元素:\n");
//		scanf("%d",&e);
//		getchar(); 
//		p=SearchHash(pHashTable,e);
//		
//		if(p==NULL)
//			printf("该哈希表中没有这个元素\n");
//		else
//			printf("查找元素为%d已找到\n",p->key);
//	} 
	return 0;
}
