#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OVERFLOW -2
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef int IndexOfKey;

#define STR_MAX_SIZE 25 //�ַ�������󴮳�

//�ؼ���Ϊ�ַ�����
typedef char KeyType[STR_MAX_SIZE];

//����Ԫ������
typedef struct
{
	KeyType key; //�ؼ�����
	//... //������
}ElemType;

//�������ؼ��ֱȽ�Լ��Ϊ���µĺ궨��
#define EQ( a,b ) ( !strcmp( (a),(b) ) )
#define LT( a,b ) ( strcmp( (a),(b) ) < 0 )
#define LQ( a,b ) ( strcmp( (a),(b) ) <= 0 )

//---------------��̬���ұ����������洢�ṹ---------
typedef struct LNode
{
	ElemType elem; //����
	struct LNode* next;
}LNode,*LSTable;

//��Ĵ���
Status Create(LSTable& ST,int n)
{
	printf("������%d���ַ���,ÿ���ַ����Իس�����!\n",n);
	getchar();
	int i;
	ST = (LSTable)malloc(sizeof(LNode)); //����ͷ���
	if (!ST)
		return FALSE;
	ST->next = NULL;
	
	LSTable p = ST; //����ָʾ�������һ�����
	LSTable q = NULL;
	for(i=0;i<n;i++)
	{
		q=(LSTable)malloc(sizeof(LNode)); //�½����
		if(!q)
			return FALSE;
		//��β���뷨
		gets(q->elem.key);
		p->next=q;
		q->next=NULL;
		p=q;
	}
	
	return TRUE;
}

//���ٱ�
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

//˳�����,�ɲ���result���ز�ѯ������ݣ���ѯ���ɹ�������һ����ֵ
Status Search_Seq(const LSTable &ST,KeyType key,ElemType &result )
{
	LSTable p = ST->next; //pָ���һ�����
	
	//�ӵ�һ����㿪ʼ����
	while(p)
	{
		if(EQ( p->elem.key, key))
		{
			result = p->elem;
			return TRUE; //���ҳɹ�
		}
		p=p->next;
	}
	memset(result.key, 0, STR_MAX_SIZE); //����ֵ
	return FALSE; //����ʧ��
}
//��ӡ���е�����
Status Traverse(const LSTable &ST )
{
	LSTable p = ST->next; //ָ���һ������
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
	printf("�����봴���ַ�����ĸ�����\n");
	scanf("%d",&n);
	if(Create(ST,n))
		printf("�����ɹ�!\n");
	
	printf("���е�����Ϊ��\n");
	Traverse(ST);
	
	KeyType key;
	ElemType result;
	printf("��������ҹؼ���:\n");
	gets(key);
	
	if(Search_Seq(ST,key,result))
	{
		printf("���ҳɹ�!\n");
		printf("���ҵļ�¼Ϊ:%s\n", result.key );
	}
	else
		printf("����ʧ��"); 
	if(Destroy(ST))
		printf("�������!\n");
	
	return 0;
}
