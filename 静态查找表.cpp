#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW -2
#define FALSE 0
#define TRUE 1

typedef int Status;
//�ؼ���Ϊ����
typedef int KeyType;	

//����Ԫ������
typedef struct	{
	KeyType key; 	//�ؼ�����
	//... 	 //������
}SElemType;

//�������ؼ��ֱȽ�Լ��Ϊ���µĺ궨��
#define EQ( a,b ) ( (a) == (b) )
#define LT( a,b ) ( (a) < (b) )
#define LQ( a,b ) ( (a) <= (b) )

//---------------��̬���ұ��˳��洢�ṹ---------
typedef struct 	{
	SElemType* elem; 	//����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
	int length;	 //��
}SSTable;

/*	�������������һ����n������Ԫ�صľ�̬���ұ�ST
	������ Create
*/
Status Create( SSTable& ST, int n ){
	ST.elem = (SElemType*)malloc( (n+1)*sizeof(SElemType) );
	if(!ST.elem)
		exit(OVERFLOW);
	printf("����������%d���������Կո�ֿ�:", n );
	int i = 0;
	for( i = 1; i <= n; i++ )
	{
		scanf("%d",&(ST.elem[i]) );
	}
	ST.length = n;
	return TRUE;
}


/*��ʼ��������̬���ұ����
������������ٱ�ST*/

Status Destroy( SSTable& ST ){
	free(ST.elem);
	ST.elem = NULL;
	ST.length = 0;
	return TRUE;
}


/*
��ʼ��������̬���ұ����,keyΪΪ�ؼ���������
ͬ�ĸ���ֵ
�����������ST�д�����ؼ��ֵ���key������Ԫ��
����ֵΪ��Ԫ���ڱ��е�λ��,����Ϊ
 0
*/
//ԭʼ�� 
int Search_Seq1(const SSTable &ST, const KeyType &key ){
	int i=1;
	while(i<=ST.length && !EQ(ST.elem[i].key,key))
		++i;
	if(i<=ST.length)
		return i;
	else
		return 0;
} 

//�Ľ��� 
int Search_Seq2(const SSTable& ST, const KeyType& key ){
	ST.elem[0].key = key; //0��λ������һ��"�ڱ�"
	int i = 0;
	for ( i = ST.length; !EQ( ST.elem[i].key, key); --i );//�Ӻ���ǰ��
	return i; //�Ҳ���ʱ����0
}


/*=============================================
* ��ʼ��������̬���ұ����
* ��������������е�Ԫ�ذ���������
*=============================================*/
Status AscElem(SSTable &ST){
	SElemType temp; //�м����
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
* ��ʼ��������̬���ұ����
* ����������۰����
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
?*�������ܣ���ӡԪ��
?*=============================================*/
Status VisitElem( const SElemType& elem ){
	printf("%d", elem );
	return TRUE;
}


/*=============================================
*�������ܣ���ӡ��̬���ұ��е�Ԫ��
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
*�������ܣ������˵�
*==============================================*/

void Menu(void){
	//������ƽ�������ʹ��
	//system("COLOR 77");
	printf("\t\t             =======================         \n");
	printf("\t\t            |                       |        \n");
	printf("\t\t   |--------|   ˳��̬���ұ����  |-------|\n");
	printf("\t\t   |        |                       |       |\n");
	printf("\t\t   |         =======================        |\n");
	printf("\t\t   |                                        |\n");
	printf("\t\t   |         ��ѡ����Ĳ�����               |\n");
	printf("\t\t   |         [1]������̬���ұ�              |\n");
	printf("\t\t   |         [2]���پ�̬���ұ�              |\n");
	printf("\t\t   |         [3]˳�����(ԭʼ��)            |\n");
	printf("\t\t   |         [4]˳�����(�Ľ���)            |\n");
	printf("\t\t   |         [5]�۰����                    |\n");
	printf("\t\t   |         [6]�鿴��Ԫ��                  |\n");
	printf("\t\t   |         [7]�˳�                        |\n");
	printf("\t\t   |-======================================-|\n");
	printf("\t\t   |                 ��ӭ�޸�               |\n");
	printf("\t\t   |-======================================-|\n");
	printf("��ѡ����Ҫ���еĲ���(1/2/3/4/5/6/7):");
}

int main(int argc,char **argv){
	Menu();
	int i = 0;
	int n = 0; //Ҫ������Ԫ�ظ���
	int index;  //��¼��ѯ�������ص�����
	SSTable ST;
	KeyType key; //���ҹؼ���
	scanf("%d",&i);
	while( i != 7)
	{
		switch( i )
		{
			case 1:
				printf("�����봴�����е�Ԫ�ظ���:");
				scanf("%d",&n);
				if(Create(ST, n))
					printf("�����ɹ�!\n");
				Menu();
				break;
			case 2:
				if(Destroy(ST))
					printf("���ٳɹ���\n");
				Menu();
				break;
			case 3:
				printf("��������ҹؼ���:");
				scanf("%d", &key);
				index = Search_Seq1(ST, key);
				if (index)
					printf("���ҳɹ�!���ǵ�%d����¼\n", index);
				else
					printf("�����޴�Ԫ��\n");
				Menu();
				break; 
			case 4:
				printf("��������ҹؼ���:");
				scanf("%d", &key);
				index = Search_Seq2(ST, key);
				if (index)
					printf("���ҳɹ�!���ǵ�%d����¼\n", index);
				else
					printf("�����޴�Ԫ��\n");
				Menu();
				break;
			case 5:
				AscElem(ST); //�Ƚ����е�Ԫ�ذ���������
				printf("���е�Ԫ���Ѱ���������\n");
				printf("��������ҹؼ���:");
				scanf("%d", &key);
				index = Search_Bin(ST, key);
				if (index )
					printf("���ҳɹ�!���ǵ�%d����¼\n", index);
				else
					printf("�����޴�Ԫ��\n");
				Menu();
				break;
			case 6:
				printf("���е�Ԫ�أ�\n");
				Traverse(ST,VisitElem);
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
}

