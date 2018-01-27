#pragma once//防止重复定义

// 这是一个结点
template<typename T>
class LinkNode
{
public:
	LinkNode *prior;//指向前驱
	T	data;//数据域
	LinkNode *next;//指向后继
};



//双向链表
template<typename T>
class DoublyList
{	
	template<typename T>
	friend bool sortdoublyList(DoublyList<T> *plist, bool(*cmp)(T &a, T &b)); 
	//声明友元函数  可以访问的私有变量
	
public://提供外界使用的API

	DoublyList();//构造函数
	~DoublyList();//析构函数
	bool insertElement(T &pnode, int pos);
	bool insertElement(T &&pnode, int pos);
	bool deleteElement(int pos);
	bool deleteElement(T &pnode);
	int getlength()const;
	void Traversal(bool ispositive = true);
	
private://仅在该类中使用的  私有的
	LinkNode<T> head;
	LinkNode<T> last;
	int size;
	//head为头部监督元   last为尾部监督元 这样子双向链表就不用去判断头插尾插  一套业务逻辑就够了(也就是空间换时间)
};

template<typename T>
DoublyList<T>::DoublyList()
{
	this->size = 0;
	this->head.prior = NULL; //头的前驱为NULL
	this->last.next = NULL;//尾的后继为NULL 
	this->head.next = &this->last;
	this->last.prior = &this->head;
}

template<typename T>
bool DoublyList<T>::insertElement(T &pnode, int pos)
{
	//可能出现的异常情况     传入的下标不合法
	if (pos<0 || pos>this->size)
	{
		cout << "insert Element  error  sorry！！！" << endl;
		return false;
	}
	
	LinkNode<T> *newcode = new LinkNode<T>; //生成新的结点
	newcode->data = pnode;  //数据的拷贝是值语义  要注意深拷贝和浅拷贝的问题   以免指向同一块内存 重复析构释放
	
	LinkNode<T> *currentnode = &this->head;//头部监督元地址给了 辅助指针遍历 currentnode
	
	
	//提高算法:因为尾部也有监督元  当前位置大于size/2的时候 从尾部开始跳进行插入(效率更快)
	
	for (int i = 0; i < pos; i++)//移动到当前位置   
	{
		currentnode = currentnode->next;
	}
	
	LinkNode<T> *ret = currentnode->next;//保存当前的后继结点 
	newcode->next = currentnode->next;
	currentnode->next = newcode;
	//连接了newnode next的前驱和后继
	
	newcode->prior = ret->prior;
	ret->prior = newcode;
	//连接了newnode prior的后继和前驱
	
	
	this->size++;//元素+1	
	return true;
}
template<typename T>
bool DoublyList<T>::insertElement(T &&pnode, int pos)
{
	//可能出现的异常情况     传入的下标不合法
	if (pos<0 || pos>this->size)
	{
		cout << "insert Element  error  sorry！！！" << endl;
		return false;
	}
	LinkNode<T> *newcode = new LinkNode<T>; //生成新的结点
	
	newcode->data = pnode;  //数据的拷贝  要注意深拷贝和浅拷贝的问题   以免指向同一块内存 重复释放
	LinkNode<T> *currentnode = &this->head;//头部监督元地址给了 辅助指针遍历 currentnode
	
	for (int i = 0; i < pos; i++)
	{
		currentnode = currentnode->next;
	}
	LinkNode<T> *ret = currentnode->next;//保存当前的后继结点 
	newcode->next = currentnode->next;
	currentnode->next = newcode;
	
	//连接了newnode next的前驱和后继
	newcode->prior = ret->prior;
	ret->prior = newcode;
	
	//连接了newnode prior的后继和前驱
	this->size++;//元素+1	
	return true;
}

template<typename T>
bool DoublyList<T>::deleteElement(int pos)
{
	if (pos<0 || pos>this->size || this->size == 0)
	{
		cout << "delete error  sorry!" << endl;
		return false;
	}
	LinkNode<T> *currentnode = &this->head;
	for (int i = 0; i < pos; i++)
	{
		currentnode = currentnode->next;
	}
	
	LinkNode<T> *freenode = currentnode->next;//删除的位置结点 用辅助指针指向
	LinkNode<T> *ret = freenode->next;
	currentnode->next = ret;//连接删除结点的后继 
	ret->prior = currentnode;
	//忘记连接prior了 注意了这是一个双向链表
	
	delete freenode;//释放删除结点的内存空间
	
	this->size--;
	return true;
}

template<typename T>
bool DoublyList<T>::deleteElement(T &pnode)
{
	if (this->size == 0)//如果没有元素那还删除个什么劲呢
	{
		cout << "delete error  sorry!" << endl;
		return false;
	}
	
	LinkNode<T> *currentnode = &this->head;
	LinkNode<T> *freenode = NULL;
	
	while (currentnode != &this->last)//遍历到尾部
	{
		if (currentnode->next->data == pnode)//如果找到了相同的数据
		{
			freenode = currentnode->next;//删除的位置结点 用辅助指针指向
			LinkNode<T> *ret = freenode->next;
			currentnode->next = ret;//连接删除结点的后继 
			ret->prior = currentnode;
			break;
		}
		currentnode = currentnode->next;//移动到下一个结点
	}
	if (freenode)//如果找到了
	{
		cout << "找到了，并删除此个人信息:" << freenode->data;
		delete freenode;
		this->size--;
		return true;
	}
	cout << "delete error  sorry!" << endl;
	return false;
}
template<typename T>
int DoublyList<T>::getlength()const
{
	return this->size;
}


template<typename T>
void DoublyList<T>::Traversal(bool ispositive = true)
{
	LinkNode<T> *currentheadnode = this->head.next;
	LinkNode<T> *currentlastnode = this->last.prior;
	if (ispositive)//如果为true 默认正向遍历 输出
	{
		for (int i = 0; i < this->size; i++)
		{
			cout << currentheadnode->data;
			currentheadnode = currentheadnode->next;
		}
	}
	else
	{
		for (int i = 0; i < this->size; i++)
		{
			cout << currentlastnode->data;
			currentlastnode = currentlastnode->prior;
		}
	}
}
template<typename T>
DoublyList<T>::~DoublyList()
{
		//释放结点在堆区申请的内存就好了
	LinkNode<T> *currentnode = this->head.next;
	while (currentnode != &this->last)
	{
		LinkNode<T> *freenode = currentnode;
		currentnode = currentnode->next;//移动到下一个结点
		delete freenode;
	}
	this->size = 0;
}
//知识点:
//函数指针作函数参数 提前约定好了返回值和参数类型 
//提供一个接口 框架保持不变的情况下  后来人写的函数入口地址丢进来  可以直接调用
template<typename T>
bool sortdoublyList(DoublyList<T> *plist, bool(*cmp)(T &a, T &b))
{
	//如果没有元素或者只有一个元素不存在对比年龄排序
	if ( 0== plist->size ||  1== plist->size)
	{
		cout << "sort error sorry" << endl;
		return false;
	}
	bool exchange=true;
	for (int i = 0; (i < plist->size)&&(exchange); i++)//循环条件当两项都为真时
	{	
		LinkNode<T> *firstnode = plist->head.next;//第一个结点
		LinkNode<T> *secondnode = firstnode->next;
		LinkNode<T> *cmplast = &plist->last;
		exchange=false;
		//采用的是冒泡排序法 相邻两个元素进行比较(该算法还可以进行优化，若下一轮循环不再进行交换元素了，那么就是排序好了)
		while (secondnode !=cmplast )//当secondnode 为last说明对比到最后一个结点了
		{
			if (cmp(firstnode->data, secondnode->data))//返回true说明stu1>stu2 前一项大于后一项
			{
				T temp = firstnode->data;  //值拷贝
				firstnode->data = secondnode->data;
				secondnode->data = temp;
				exchange=true;
			}
			firstnode = firstnode->next;
			secondnode = secondnode->next;
		}
		cmplast = cmplast->prior;
	}
	return true;
}