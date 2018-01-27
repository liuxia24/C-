
#include"stdio.h"
#include<stdlib.h>
//框架先搭起来  再实现具体细节
#define newNode  (pNode)malloc(sizeof(Node))
typedef struct Node  //结点
{
	int data;//数据域  存放数据的
	Node *next;//指针域
}*pNode; 

typedef struct List  //封装结点  成一个链表的  一个对象
{
	int size;//统计链表当前的元素
	pNode head;//结点保存着指针域和数据域
}*pList;

List *CreatList()
{	
	//创建一个链表对象吧	
	pList list =(pList)malloc(sizeof(List));
	if(NULL==list)//判断有没申请内存成功
	{
		printf("CreatList errpr\n");
		return NULL;
	}
	list->size = 0;//容器初始化为0
	list->head = NULL;//头部先赋予NULL
	pNode p = newNode;//生成一个监督元
	p->data = 0;
	p->next = list->head;//尾部结点指针域赋予空
	list->head = p;//头部指向监督元
	return list;//返回一个list句柄
}/
int isempty(pList mlist)
{
	if (mlist->size==0)
	{
		return 0;//ture
	}
	return -1;//false
}//判空
int getsize(pList mlist)
{
	return mlist->size; //返回容器当前的存放的元素个数 
}
int DestoryList(List *mlist) //因为我不需要操控指针来申请内存  我要操控的是指针指向的内存空间
{
	if (mlist != NULL)//如果是已经指向了一个地址  那么进行释放
	{
		//先释放结构体内所在堆区申请的内存   也就是结点
		while (mlist->head != NULL)//如果头部不指向一个空说明有连接结点
		{
			pNode pfree = NULL;//保存即将释放的结点
			pfree = mlist->head;//要释放的内存保存到pfree
			//free(pfree); error 我将结点释放掉了  下一条head指向结点的指针域岂不是找不到这个结点了  不是变成野指针了
			mlist->head = mlist->head->next;//连接下一个结点	
			free(pfree);
		}
		mlist->size = NULL;
		free(mlist);//然后再释放链表申请的内存
		return 0;//代表成功释放内存
	}
	return -1;//代表失败
}

int clearList(pList mlist)
{
	if (mlist!= NULL&&mlist->size!=0)//如果是已经指向了一个地址 并且当前容器有元素  那么进行清空
	{
		//先释放结构体内所在堆区申请的内存   也就是结点
		while (mlist->head->next!= NULL)//如果头部不指向一个空说明有连接结点
		{
			pNode pfree = NULL;//保存即将释放的结点
			pfree = mlist->head->next;//要释放的内存保存到pfree
			//free(pfree); error 我将结点释放掉了  下一条head指向结点的指针域岂不是找不到这个结点了  不是变成野指针了
			pNode p = mlist->head->next;
			p = p->next;//移动到下一个结点  //相当于mlist->head->next->next;看起来没这么混乱
			mlist->head->next =p;//连接下一个结点	
			free(pfree);
		}//这样做我没有删除监督元 而是删除监督元后加入的结点
		mlist->size = 0;	
		return 0;
	}

	return -1;
	//既然将节点全部释放了包括监督元 那么我再给他一个监督元不就好了吗

}

int  insertList_head(pList mlist,  const int data) //  data代表要赋值的数据域  在链表的头部进行插入
{
	pNode p = newNode;//生成一个新的结点
	if (p == NULL)
	{
		return -1;//申请内存失败了
	}
	p->data = data;
	p->next = mlist->head->next;
	mlist->head->next = p;
	//连接结点了	
	mlist->size++;//代表当前结点+1次
	return 0;
}

void TravelesList(pList mlist)
{
	if (mlist->size == 0)//如果没有元素就不遍历了
	{
		return;
	}
	printf("当前的元素个数为:%d\n", mlist->size);
	pNode p = mlist->head->next;//辅助指针指向首第一个结点
	while (p != NULL)//p没有遍历到尾部时  迭代
	{
		printf("%d    ",p->data);//打印
		p = p->next;//移动到下一个结点
	}
}
void deleteList_head(pList mlist)//正向 每次删除一个结点
{
	if (mlist->size == 0)//如果没有元素 就没有必要删除了
	{
		return;
	}
	pNode freenode = mlist->head->next;
	pNode p = mlist->head->next;
	p = p->next;
	mlist->head->next = p;
	free(freenode);//释放保存的结点避免造成内存泄漏
	mlist->size--;
}

int insertList_pos(pList mlist, int data, const int pos)//功能:在某个位置pos插入
{
	if(!mlist||pos<0||pos>mlist->size)//判断异常
	{
		return -1;
	}
	pNode currentnode=mlist->head;//辅助指针指向头部结点
	for(int i=0;i<pos;i++)//跳到pos位置的前驱结点
	{
		currentnode=currentnode->next;
	}
	pNode p = newNode;//生成一个新的结点
	p->data=data;//数据域赋值
	
	//连接前驱和后继结点
	p->next=currentnode->next;
	currentnode->next=p;
	
	mlist->size++;
	return 0;
}

int deleteList_pos(pList mlist, const  int pos)//功能:删除某个pos位置的元素
{
	if(!mlist||pos<0||pos>mlist->size)//判断异常
	{
		return -1;
	}
	pNode currentnode=mlist->head;//辅助指针指向头部结点
	for(int i=0;i<pos;i++)//跳到pos位置的前驱结点
	{
		currentnode=currentnode->next;
	}
	//连接freenode的后继结点 
	pnode freenode=currentnode->next;
	currentnode->next=freenode->next;
	
	free(freenode);//释放结点
	mlist->size--;
	return 0;
	
}
int main()
{
	pList Mylist=NULL;
	Mylist=CreatList();//创建一个空链表

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
		printf("mlist不为空\n");
	}
	else
	{
		printf("NULL\n");
	}
	int ret=DestoryList(Mylist);//释放资源
	if (ret != 0)
	{
		printf("释放内存失败了\n");
	}
	else
	{
		printf("释放内存成功了\n");
	}
	
	return 0;
}
#include<stdio.h>
#include<stdlib.h>

#if NULL

void CreatList1(int  *plist)
{
	plist = (int *)malloc(sizeof(int));//申请内存
	//（只是将原本的NULL的内存空间  给形参动态申请一个内存地址，并没有实际操控到main函数里的mlist指针变量）
}
void CreatList2(int **plist)
{
	*plist = (int *)malloc(sizeof(int));//申请内存
}

int main()
{
	int *mlist = NULL;//指针变量初始化指向内存空间为NULL  避免野指针的出现
 //	CreatList1(mlist);//传入的是mlist指向的内存空间
	CreatList2(&mlist);//传入的是指针变量的内存地址   
	return 0;
}
#endif
