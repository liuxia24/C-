
#include"stdio.h"
#include<stdlib.h>
//����ȴ�����  ��ʵ�־���ϸ��
#define newNode  (pNode)malloc(sizeof(Node))
typedef struct Node  //���
{
	int data;//������  ������ݵ�
	Node *next;//ָ����
}*pNode; 

typedef struct List  //��װ���  ��һ�������  һ������
{
	int size;//ͳ������ǰ��Ԫ��
	pNode head;//��㱣����ָ�����������
}*pList;

List *CreatList()
{	
	//����һ����������	
	pList list =(pList)malloc(sizeof(List));
	if(NULL==list)//�ж���û�����ڴ�ɹ�
	{
		printf("CreatList errpr\n");
		return NULL;
	}
	list->size = 0;//������ʼ��Ϊ0
	list->head = NULL;//ͷ���ȸ���NULL
	pNode p = newNode;//����һ���ලԪ
	p->data = 0;
	p->next = list->head;//β�����ָ�������
	list->head = p;//ͷ��ָ��ලԪ
	return list;//����һ��list���
}/
int isempty(pList mlist)
{
	if (mlist->size==0)
	{
		return 0;//ture
	}
	return -1;//false
}//�п�
int getsize(pList mlist)
{
	return mlist->size; //����������ǰ�Ĵ�ŵ�Ԫ�ظ��� 
}
int DestoryList(List *mlist) //��Ϊ�Ҳ���Ҫ�ٿ�ָ���������ڴ�  ��Ҫ�ٿص���ָ��ָ����ڴ�ռ�
{
	if (mlist != NULL)//������Ѿ�ָ����һ����ַ  ��ô�����ͷ�
	{
		//���ͷŽṹ�������ڶ���������ڴ�   Ҳ���ǽ��
		while (mlist->head != NULL)//���ͷ����ָ��һ����˵�������ӽ��
		{
			pNode pfree = NULL;//���漴���ͷŵĽ��
			pfree = mlist->head;//Ҫ�ͷŵ��ڴ汣�浽pfree
			//free(pfree); error �ҽ�����ͷŵ���  ��һ��headָ�����ָ���������Ҳ�����������  ���Ǳ��Ұָ����
			mlist->head = mlist->head->next;//������һ�����	
			free(pfree);
		}
		mlist->size = NULL;
		free(mlist);//Ȼ�����ͷ�����������ڴ�
		return 0;//����ɹ��ͷ��ڴ�
	}
	return -1;//����ʧ��
}

int clearList(pList mlist)
{
	if (mlist!= NULL&&mlist->size!=0)//������Ѿ�ָ����һ����ַ ���ҵ�ǰ������Ԫ��  ��ô�������
	{
		//���ͷŽṹ�������ڶ���������ڴ�   Ҳ���ǽ��
		while (mlist->head->next!= NULL)//���ͷ����ָ��һ����˵�������ӽ��
		{
			pNode pfree = NULL;//���漴���ͷŵĽ��
			pfree = mlist->head->next;//Ҫ�ͷŵ��ڴ汣�浽pfree
			//free(pfree); error �ҽ�����ͷŵ���  ��һ��headָ�����ָ���������Ҳ�����������  ���Ǳ��Ұָ����
			pNode p = mlist->head->next;
			p = p->next;//�ƶ�����һ�����  //�൱��mlist->head->next->next;������û��ô����
			mlist->head->next =p;//������һ�����	
			free(pfree);
		}//��������û��ɾ���ලԪ ����ɾ���ලԪ�����Ľ��
		mlist->size = 0;	
		return 0;
	}

	return -1;
	//��Ȼ���ڵ�ȫ���ͷ��˰����ලԪ ��ô���ٸ���һ���ලԪ���ͺ�����

}

int  insertList_head(pList mlist,  const int data) //  data����Ҫ��ֵ��������  �������ͷ�����в���
{
	pNode p = newNode;//����һ���µĽ��
	if (p == NULL)
	{
		return -1;//�����ڴ�ʧ����
	}
	p->data = data;
	p->next = mlist->head->next;
	mlist->head->next = p;
	//���ӽ����	
	mlist->size++;//����ǰ���+1��
	return 0;
}

void TravelesList(pList mlist)
{
	if (mlist->size == 0)//���û��Ԫ�ؾͲ�������
	{
		return;
	}
	printf("��ǰ��Ԫ�ظ���Ϊ:%d\n", mlist->size);
	pNode p = mlist->head->next;//����ָ��ָ���׵�һ�����
	while (p != NULL)//pû�б�����β��ʱ  ����
	{
		printf("%d    ",p->data);//��ӡ
		p = p->next;//�ƶ�����һ�����
	}
}
void deleteList_head(pList mlist)//���� ÿ��ɾ��һ�����
{
	if (mlist->size == 0)//���û��Ԫ�� ��û�б�Ҫɾ����
	{
		return;
	}
	pNode freenode = mlist->head->next;
	pNode p = mlist->head->next;
	p = p->next;
	mlist->head->next = p;
	free(freenode);//�ͷű���Ľ���������ڴ�й©
	mlist->size--;
}

int insertList_pos(pList mlist, int data, const int pos)//����:��ĳ��λ��pos����
{
	if(!mlist||pos<0||pos>mlist->size)//�ж��쳣
	{
		return -1;
	}
	pNode currentnode=mlist->head;//����ָ��ָ��ͷ�����
	for(int i=0;i<pos;i++)//����posλ�õ�ǰ�����
	{
		currentnode=currentnode->next;
	}
	pNode p = newNode;//����һ���µĽ��
	p->data=data;//������ֵ
	
	//����ǰ���ͺ�̽��
	p->next=currentnode->next;
	currentnode->next=p;
	
	mlist->size++;
	return 0;
}

int deleteList_pos(pList mlist, const  int pos)//����:ɾ��ĳ��posλ�õ�Ԫ��
{
	if(!mlist||pos<0||pos>mlist->size)//�ж��쳣
	{
		return -1;
	}
	pNode currentnode=mlist->head;//����ָ��ָ��ͷ�����
	for(int i=0;i<pos;i++)//����posλ�õ�ǰ�����
	{
		currentnode=currentnode->next;
	}
	//����freenode�ĺ�̽�� 
	pnode freenode=currentnode->next;
	currentnode->next=freenode->next;
	
	free(freenode);//�ͷŽ��
	mlist->size--;
	return 0;
	
}
int main()
{
	pList Mylist=NULL;
	Mylist=CreatList();//����һ��������

	insertList_head(Mylist, 10);
	insertList_head(Mylist, 20);
	insertList_head(Mylist, 30);
	insertList_head(Mylist, 40);
	insertList_head(Mylist, 50);


	deleteList_head(Mylist);


	//int ret2 = clearList(Mylist);

	TravelesList(Mylist);

	int ret1 = isempty(Mylist);
	if (ret1 != 0)
	{
		printf("mlist��Ϊ��\n");
	}
	else
	{
		printf("NULL\n");
	}
	int ret=DestoryList(Mylist);//�ͷ���Դ
	if (ret != 0)
	{
		printf("�ͷ��ڴ�ʧ����\n");
	}
	else
	{
		printf("�ͷ��ڴ�ɹ���\n");
	}
	
	return 0;
}
#include<stdio.h>
#include<stdlib.h>

#if NULL

void CreatList1(int  *plist)
{
	plist = (int *)malloc(sizeof(int));//�����ڴ�
	//��ֻ�ǽ�ԭ����NULL���ڴ�ռ�  ���βζ�̬����һ���ڴ��ַ����û��ʵ�ʲٿص�main�������mlistָ�������
}
void CreatList2(int **plist)
{
	*plist = (int *)malloc(sizeof(int));//�����ڴ�
}

int main()
{
	int *mlist = NULL;//ָ�������ʼ��ָ���ڴ�ռ�ΪNULL  ����Ұָ��ĳ���
 //	CreatList1(mlist);//�������mlistָ����ڴ�ռ�
	CreatList2(&mlist);//�������ָ��������ڴ��ַ   
	return 0;
}
#endif
