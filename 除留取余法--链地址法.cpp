#include <iostream>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

//��ϣ�����Ĺ��췽��:����ȡ�෨
//�����ͻ����:����ַ��

typedef struct _NODE{
	int key;
	struct _NODE* next;
}_NODE; 

typedef struct Hash_Table{
	_NODE* pChainHash[13];
}Hash_Table;
//��ʼ����ϣ��

Hash_Table *InitHashTable(){
	Hash_Table *pHashTable =(Hash_Table*)malloc(sizeof(Hash_Table));
	memset(pHashTable,0,sizeof(Hash_Table));
	return pHashTable;
} 
//�ڹ�ϣ���в���Ԫ��
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
	
	printf("������Ԫ�ظ���:\n");
	scanf("%d",&n);
	printf("������Ԫ�أ�\n");
//	19 14 23 1 68 20 84 27 55 11 10 79
	for(i=0;i<n;i++)
	{
		scanf("%d",&e); 
		InsertDataToHash(pHashTable,e);
	}
	H = pHashTable;
	printf("\n��ϣ������ַ��:\n\n");
	printf("����\tֵ\n");
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
//		printf("\n��������ҵ�Ԫ��:\n");
//		scanf("%d",&e);
//		getchar(); 
//		p=SearchHash(pHashTable,e);
//		
//		if(p==NULL)
//			printf("�ù�ϣ����û�����Ԫ��\n");
//		else
//			printf("����Ԫ��Ϊ%d���ҵ�\n",p->key);
//	} 
	return 0;
}
