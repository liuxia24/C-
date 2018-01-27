#ifndef SCIRCLELIST_H
#define SCIRCLELIST_H

template<typename T>
class Linknode
{
public:

	T data;//数据域
	Linknode *next;//指针域
};

template<typename T>
class CircleList
{
public:
	CircleList();
	bool insertElement(T &data, int pos);
	bool insertElement(T &&data, int pos);
	 int getlength() const;
	T& getElement (int pos);
	bool deleteElement(int pos);
	bool deletedata(T &data);
	bool deletedata(T &&data);
	void ClearList();
	~CircleList();
private:
	Linknode<T> *getlastnode(int pos);
private:
	int size;
	Linknode<T> head;
	Linknode<T> *iterator;
};

template<typename T>
CircleList<T>::CircleList()
{
	this->size = 0;
	this->head.next = NULL;
	this->iterator = NULL;
	//memset(this,0,sizeof(CircleList)); 做一个负责任的人  
}

template<typename T>
bool CircleList<T>::insertElement(T &data, int pos)
{
	if (pos<0 || pos>this->size||!data)
	{
		cout << "insert error!!!" << endl;
		return false;
	}
	Linknode<T> *currentnode = &this->head;//将辅助指针变量 指向头结点
	Linknode<T> *p = new Linknode<T>;//生成一个新结点  若在循环链表内部管理结点 则需手动释放内存
	Linknode<T>  *ret = NULL;
	for (int i = 0; i < pos; i++)
	{
		currentnode = currentnode->next;
	}
	ret= currentnode->next;
	p->data = data;
	p->next = ret;
	currentnode->next = p;
	if (this->size == 0)
	{
		this->iterator = currentnode->next;//设置游标位置
	}
	this->size++;
	if (currentnode == &this->head)//如果没跳说明在头部插入
	{
		Linknode<T> *last = this->getlastnode(this->getlength() - 1);
		last->next = currentnode->next;
	}
	return true;
}

template<typename T>
bool CircleList<T>:: insertElement(T &&data, int pos)
{
	if (pos<0 || pos>this->size||!data)
	{
		cout << "insert error!!!" << endl;
		return false;
	}
	Linknode<T> *currentnode = &this->head;//将辅助指针变量 指向头结点
	Linknode<T> *p = new Linknode<T>;//生成一个新结点
	Linknode<T>  *ret = NULL;
	for (int i = 0; i < pos; i++)
	{
		currentnode = currentnode->next;
	}
	
	ret= currentnode->next;
	p->data = data;
	p->next = ret;
	currentnode->next = p;
	if (this->size == 0)
	{
		this->iterator = currentnode->next;//设置游标位置
	}
	this->size++;
	if (currentnode == &this->head)//如果没跳说明在头部插入
	{
		Linknode<T>  *last = this->getlastnode(this->getlength() - 1);
		last->next = currentnode->next;
	}
	return true;
}
template<typename T>
bool CircleList<T>::deleteElement(int pos)
{
	if (pos<0 || pos>this->size||this->size==0) //其实我可以将大于元素个数作一个修正 让其可以删除  使底层库的可用性更强
		//而不是动不动就报错  
	{
		cout << "delete error sorry" << endl;
		return false;
	}
	Linknode<T> *currentnode = &this->head;
	Linknode<T> *last = NULL;
	//第一步:跳到能找到删除结点的 前驱
	for (int i = 0; i < pos; i++)
	{
		currentnode = currentnode->next;
	}
	//第二步：若是头删法  则让辅助指针变量 指向尾部结点
	if (currentnode == &this->head)
	{
		last = getlastnode(this->size - 1);  //辅助指针指向最后一个结点
	}
	Linknode<T> *freenode = currentnode->next;//将删除的结点保存到freenode中
	currentnode->next = freenode->next; //当前的结点连接到 删除结点的后继  
	//第三步：若删除的结点和游标的指向一致那么 将其游标指向下一个结点
	if (freenode == this->iterator)
	{
		this->iterator = currentnode->next;
	}
	delete freenode; //释放在堆区申请的结点
	this->size--;
	if (last)
	{
		last->next = currentnode->next; //设置尾部重新指向第一个结点
	}
	//若已经删光了  
	if (this->size == 0)
	{
		this->head.next = NULL;
		this->iterator = NULL;
	}
	return true;

}
template<typename T>
 int CircleList<T>::getlength() const
{
	return this->size;
}

template<typename T>
T& CircleList<T>::getElement(int pos)
{
	Linknode<T> *currentnode = this->head.next;
	for (int i = 0; i < pos; i++)
	{
		currentnode = currentnode->next;
	}
	return currentnode->data;
}

template<typename T>
Linknode<T> *CircleList<T>::getlastnode(int pos)
{
	Linknode<T> *currentlastnode = &this->head;
	for (int i = 0; i < pos; i++)
	{
		currentlastnode = currentlastnode->next;
	}
	return currentlastnode->next;
}

template<typename T>
void    CircleList<T>::ClearList()
{
	if (this->size == 0)
	{
		cout << "container   No any  Element ,Clear error" << endl;
		return;
	}
	Linknode<T> *currentnode = this->head.next;
	while (this->size>0)
	{
		Linknode<T> *freenode = currentnode;//将要释放的结点保存在freenode
		currentnode = currentnode->next;//指向下一个  
		delete freenode;
		this->size--;
	}
	this->iterator = NULL;
	this->head.next = NULL;
}

template<typename T>
bool CircleList<T>::deletedata(T &data) //一个是引用对象
{
	if (this->size == 0)
	{
		cout << "delete data error!" << endl;
		return false;
	}
	Linknode<T> *currentnode = &this->head;
	Linknode<T> *last = NULL;
	Linknode<T> *freenode = NULL;
	for (int i = 0; i < this->getlength(); i++)//遍历元素
	{
		if (currentnode->next->data== data) //如果遍历找到这个值
		{	
			if (currentnode == &this->head) //如果找到了值 并且是头删法 
			{
				last = this->getlastnode(this->getlength() - 1);//找到尾部结点
			}
			freenode = currentnode->next;//将删除的结点保存在这
			currentnode->next = freenode->next;//连接删除结点的后继
			if (freenode == this->iterator)
			{
				this->iterator = freenode->next;
			}
			break;//..停止循环
		}
		currentnode = currentnode->next;//移动结点
	}
	if (last!=NULL)
	{
		last->next = currentnode->next;
	}
	if (freenode)
	{
		cout << "find  this :" << freenode->data <<"can   delete  sucessful"<< endl;
		delete freenode;
		this->size--;   
		if (this->size == 0)
		{
			this->head.next = NULL;
			this->iterator = NULL;
		}
		return true;
	}
	else
	{
		cout << " Don't find this data sorry" << endl;
		return false;
	}
	
}
template<typename T>
bool CircleList<T>::deletedata( T &&data)//一个是引用元素 C++11增加的
{
	if (this->size == 0)
	{
		cout << "delete data error!" << endl;
		return false;
	}
	Linknode<T> *currentnode = &this->head;
	Linknode<T> *last = NULL;
	Linknode<T> *freenode = NULL;
	for (int i = 0; i < this->getlength(); i++)//遍历元素
	{
		if (currentnode->next->data == data) //如果遍历找到这个值
		{
			if (currentnode == &this->head) //如果找到了值 并且是头删法 
			{
				last = this->getlastnode(this->getlength()-1);//找到尾部结点
				//--后置先减再用    前置先用 再减
			}
			freenode = currentnode->next;//将删除的结点保存在这
			currentnode->next = freenode->next;//连接删除结点的后继
			if (freenode == this->iterator)
			{
				this->iterator = freenode->next;
			}
			break;//..停止循环
		}
		currentnode = currentnode->next;//移动结点
	}
	if (last != NULL)
	{
		last->next = currentnode->next;
	}
	if (freenode)
	{
		cout << "find  this :" << freenode->data << "can   delete  sucessful" << endl;
		delete freenode;
		this->size--;
		if (this->size == 0)
		{
			this->head.next = NULL;
			this->iterator = NULL;
		}
		return true;
	}
	else
	{
		cout << " Don't find this data sorry" << endl;
		return false;
	}

}
template<typename T>
CircleList<T>::~CircleList()
{
	//删除所有节点 
	Linknode<T> *currentnode = this->head.next;
	while (this->size>0)
	{	
		Linknode<T> *freenode = currentnode;//将要释放的结点保存在freenode
		currentnode = currentnode->next;//指向下一个  
		delete freenode;
		printf("%d  ", this->size);
		this->size--;
	}
	this->iterator = NULL;
	this->head.next = NULL;
}
#endif