#ifndef LINUXLINKLIST_H
#define LINUXLINKLIST_H
#include<stdlib.h>
#include<memory.h>
 typedef  struct node 
{
     struct node *next;  //指针域
}Linknode;

typedef struct linux_Linklist  
{
	     int Link_size;
		 Linknode head;  
}Linklist,*pLinklist;



Linklist* CreatList()
{
	//第一种：pLinklist tmp = (pLinklist)malloc(sizeof(Linklist));
	pLinklist tmp = NULL;
	tmp = (pLinklist)malloc(sizeof(Linklist));
	if (tmp == NULL)
	{
		printf("sorry，malloc memory error!\n");
		return NULL;
	}
	//第二种和第一种的区别就是:使用这种方法的好处是可以判断有没成功给tmp分配内存(堆区).

	memset(tmp, 0, sizeof(Linklist));
	//函数原型：void *  __cdecl memset(_Out_writes_bytes_all_(_Size) void * _Dst, _In_ int _Val, _In_ size_t _Size);
	/*
	功能：为新申请的内存做初始化工作。  参数：1.需要初始化的内存空间（地址）  2.初始化的char ch,  3.块的大小
	printf("%d", tmp->Link_size);
	printf("%d", tmp->head);//都初始化为0了
	if (tmp->head == NULL)
	{
		printf("已经将指针变量保存的地址初始化为0了");
	}
*/
	tmp->Link_size = 0;
	tmp->head.next = NULL;
	return tmp; //返回一个地址(句柄)   外部拿到了句柄可以通过传入地址使用底层实现的API函数
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
	//循环找前驱
	while (len < pos)
	{
		currentnode = currentnode->next;//移动到下一个结点
		len++;
	}
	pnode->next = currentnode->next;
	currentnode->next = pnode;
	plist->Link_size++;//
	return 0;
}
int List_getlength(Linklist *plist)
{
	return plist->Link_size;//返回长度
}
Linklist* List_getelement(Linklist *plist,int pos)
{	
	int len = 0;
	Linknode *currentnode = plist->head.next;
	while (len < pos )
	{
		currentnode = currentnode->next;//移动到下一个结点
		len++;
	}
	return (Linklist *)currentnode; //结点node的地址就是Teacher对象的地址  （每一个Teacher对象就是一个结点）
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
		currentnode = currentnode->next;//移动到下一个结点
		len++;
	}
	//Linknode *freenode = currentnode->next;
	currentnode->next = currentnode->next->next;
	plist->Link_size--;
	//free(freenode);  
	//不能也不需要释放 因为这个结点是main函数在栈区申请的结点 只可释放堆区  只要断开结点之间的连接就好
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
	//之所以不需要去删除一个个结点，是因为我的底层链表只实现链接结点    不生成结点，
	//结点由使用链表的人传入一个结点(地址)进来。
}


void Destorylist(Linklist *plist)//释放资源
{
	if (!plist)
	{
		printf("Destory error\n");
	}
	free(plist);
	plist = NULL;
}

#endif // LINUXLINKLIST_H
