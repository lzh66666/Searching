#include <iostream>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 13
#define NULLKEY 0xffffffff/2

typedef struct{
	int* elem;
	int count;
}HashTable;

typedef int Status;

//��ʼ����ϣ��
Status InitHashTable(HashTable *pHashTable){
	if(!pHashTable)
		return UNSUCCESS;
	pHashTable->count=0;
	pHashTable->elem = new int[HASHSIZE];

	for(int i=0;i<HASHSIZE;++i)
		pHashTable->elem[i]=NULLKEY;
	return SUCCESS;
} 

//��ϣ����
int Hash(int key){
	return key%HASHSIZE;
	//����ȡ�෨������ǰ���ǵľ��飬����ϣ��ΪM����ȡ������PΪС��
    //����ڱ�����ýӽ�M������С�����򲻰���С��20�����ӵĺ��� 
} 
//����ؼ��ֵ���ϣ��
Status InsertHashTable(HashTable* pHashTable,int key){
	if(!pHashTable)
		return UNSUCCESS;
	
	int addr=Hash(key);//���ϣ��ַ
	while(pHashTable->elem[addr]!=NULLKEY)//��Ϊ�����ͻ�� 
		addr=(addr+1)%HASHSIZE;//���Ŷ�ַ��:����̽�� 
	
	pHashTable->elem[addr]=key;
	pHashTable->count++;
	return SUCCESS; 
} 
//�ڹ�ϣ���в��ҹؼ��ּ�¼
Status SearchHashTable(HashTable* pHashTable,int key,int *addr){
	if(!pHashTable)
		return UNSUCCESS;
	 
	*addr=Hash(key);
	while(pHashTable->elem[*addr]!=key)
	{
		*addr=(*addr+1)%HASHSIZE;//���Ŷ�ַ��:����̽��
		if(pHashTable->elem[*addr]==NULLKEY||*addr==Hash(key))
			return UNSUCCESS;
	}
	return SUCCESS;
} 
int main(int argc, char** argv) {
	HashTable _HashTable;
	InitHashTable( &_HashTable );
	int a,n;
	printf("������Ԫ�ظ���:\n");
	scanf("%d",&n);
	printf("������Ԫ��:\n");
//	19 14 23 1 68 20 84 27 55 11 10 79
	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&a);
		InsertHashTable( &_HashTable, a);
	}
 
	int addr;
//	while(1){
//		printf("���������Ԫ�ص�ֵ:\n");
//		scanf("%d",&a);
//		if (!SearchHashTable(&_HashTable, a, &addr )){
//			printf("�������,����������!\n"); 
//		}
//		printf("Ԫ�ص�����Ϊ%d\n",addr);
//	}

//	���� 0  1 2  3  4  5  6  7  8  9 10 11 12 13 14 15
//	Ԫ��   14 1 68 27 55 19 20 84 79 23 11 10

	printf("Ԫ��\t����\n"); 
	for(int i = 0;i < _HashTable.count;i++){
		SearchHashTable(&_HashTable,_HashTable.elem[i+1],&addr);
		printf("%d\t%d\n",_HashTable.elem[i+1],addr);	
	}
	return 0;
}
