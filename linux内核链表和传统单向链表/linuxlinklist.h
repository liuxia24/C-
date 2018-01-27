#ifndef LINUXLINKLIST_H
#define LINUXLINKLIST_H
#include<stdlib.h>
#include<memory.h>
 typedef  struct node 
{
     struct node *next;  //ָ����
}Linknode;

typedef struct linux_Linklist  
{
	     int Link_size;
		 Linknode head;  
}Linklist,*pLinklist;



Linklist* CreatList()
{
	//��һ�֣�pLinklist tmp = (pLinklist)malloc(sizeof(Linklist));
	pLinklist tmp = NULL;
	tmp = (pLinklist)malloc(sizeof(Linklist));
	if (tmp == NULL)
	{
		printf("sorry��malloc memory error!\n");
		return NULL;
	}
	//�ڶ��ֺ͵�һ�ֵ��������:ʹ�����ַ����ĺô��ǿ����ж���û�ɹ���tmp�����ڴ�(����).

	memset(tmp, 0, sizeof(Linklist));
	//����ԭ�ͣ�void *  __cdecl memset(_Out_writes_bytes_all_(_Size) void * _Dst, _In_ int _Val, _In_ size_t _Size);
	/*
	���ܣ�Ϊ��������ڴ�����ʼ��������  ������1.��Ҫ��ʼ�����ڴ�ռ䣨��ַ��  2.��ʼ����char ch,  3.��Ĵ�С
	printf("%d", tmp->Link_size);
	printf("%d", tmp->head);//����ʼ��Ϊ0��
	if (tmp->head == NULL)
	{
		printf("�Ѿ���ָ���������ĵ�ַ��ʼ��Ϊ0��");
	}
*/
	tmp->Link_size = 0;
	tmp->head.next = NULL;
	return tmp; //����һ����ַ(���)   �ⲿ�õ��˾������ͨ�������ַʹ�õײ�ʵ�ֵ�API����
}

int List_insert(Linklist *plist,Linknode *pnode,int pos)
{
	Linknode *currentnode = &plist->head;
	if (!plist || !pnode || pos > plist->Link_size || pos<0)
	{
		printf("insert error!!!\n");
		return -1;
	}
	int len = 0;
	//ѭ����ǰ��
	while (len < pos)
	{
		currentnode = currentnode->next;//�ƶ�����һ�����
		len++;
	}
	pnode->next = currentnode->next;
	currentnode->next = pnode;
	plist->Link_size++;//
	return 0;
}
int List_getlength(Linklist *plist)
{
	return plist->Link_size;//���س���
}
Linklist* List_getelement(Linklist *plist,int pos)
{	
	int len = 0;
	Linknode *currentnode = plist->head.next;
	while (len < pos )
	{
		currentnode = currentnode->next;//�ƶ�����һ�����
		len++;
	}
	return (Linklist *)currentnode; //���node�ĵ�ַ����Teacher����ĵ�ַ  ��ÿһ��Teacher�������һ����㣩
}

void List_delete(Linklist *plist,int pos)
{
	if (!plist || pos<0 || pos>=plist->Link_size||plist->Link_size==0)
	{
		printf("delete error!!!\n");
		return;
	}
	int len = 0;
	Linknode *currentnode = &plist->head;
	while (len < pos)
	{
		currentnode = currentnode->next;//�ƶ�����һ�����
		len++;
	}
	//Linknode *freenode = currentnode->next;
	currentnode->next = currentnode->next->next;
	plist->Link_size--;
	//free(freenode);  
	//����Ҳ����Ҫ�ͷ� ��Ϊ��������main������ջ������Ľ�� ֻ���ͷŶ���  ֻҪ�Ͽ����֮������Ӿͺ�
}
void CleanList(Linklist *plist)
{
	if (!plist)
	{
		printf("clean error");
		return;
	}
	plist->Link_size = 0;
	plist->head.next = NULL;
	return;
	//֮���Բ���Ҫȥɾ��һ������㣬����Ϊ�ҵĵײ�����ֻʵ�����ӽ��    �����ɽ�㣬
	//�����ʹ��������˴���һ�����(��ַ)������
}


void Destorylist(Linklist *plist)//�ͷ���Դ
{
	if (!plist)
	{
		printf("Destory error\n");
	}
	free(plist);
	plist = NULL;
}

#endif // LINUXLINKLIST_H
