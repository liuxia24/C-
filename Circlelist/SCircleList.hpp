#ifndef SCIRCLELIST_H
#define SCIRCLELIST_H

template<typename T>
class Linknode
{
public:

	T data;//������
	Linknode *next;//ָ����
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
	//memset(this,0,sizeof(CircleList)); ��һ�������ε���  
}

template<typename T>
bool CircleList<T>::insertElement(T &data, int pos)
{
	if (pos<0 || pos>this->size||!data)
	{
		cout << "insert error!!!" << endl;
		return false;
	}
	Linknode<T> *currentnode = &this->head;//������ָ����� ָ��ͷ���
	Linknode<T> *p = new Linknode<T>;//����һ���½��  ����ѭ�������ڲ������� �����ֶ��ͷ��ڴ�
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
		this->iterator = currentnode->next;//�����α�λ��
	}
	this->size++;
	if (currentnode == &this->head)//���û��˵����ͷ������
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
	Linknode<T> *currentnode = &this->head;//������ָ����� ָ��ͷ���
	Linknode<T> *p = new Linknode<T>;//����һ���½��
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
		this->iterator = currentnode->next;//�����α�λ��
	}
	this->size++;
	if (currentnode == &this->head)//���û��˵����ͷ������
	{
		Linknode<T>  *last = this->getlastnode(this->getlength() - 1);
		last->next = currentnode->next;
	}
	return true;
}
template<typename T>
bool CircleList<T>::deleteElement(int pos)
{
	if (pos<0 || pos>this->size||this->size==0) //��ʵ�ҿ��Խ�����Ԫ�ظ�����һ������ �������ɾ��  ʹ�ײ��Ŀ����Ը�ǿ
		//�����Ƕ������ͱ���  
	{
		cout << "delete error sorry" << endl;
		return false;
	}
	Linknode<T> *currentnode = &this->head;
	Linknode<T> *last = NULL;
	//��һ��:�������ҵ�ɾ������ ǰ��
	for (int i = 0; i < pos; i++)
	{
		currentnode = currentnode->next;
	}
	//�ڶ���������ͷɾ��  ���ø���ָ����� ָ��β�����
	if (currentnode == &this->head)
	{
		last = getlastnode(this->size - 1);  //����ָ��ָ�����һ�����
	}
	Linknode<T> *freenode = currentnode->next;//��ɾ���Ľ�㱣�浽freenode��
	currentnode->next = freenode->next; //��ǰ�Ľ�����ӵ� ɾ�����ĺ��  
	//����������ɾ���Ľ����α��ָ��һ����ô �����α�ָ����һ�����
	if (freenode == this->iterator)
	{
		this->iterator = currentnode->next;
	}
	delete freenode; //�ͷ��ڶ�������Ľ��
	this->size--;
	if (last)
	{
		last->next = currentnode->next; //����β������ָ���һ�����
	}
	//���Ѿ�ɾ����  
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
		Linknode<T> *freenode = currentnode;//��Ҫ�ͷŵĽ�㱣����freenode
		currentnode = currentnode->next;//ָ����һ��  
		delete freenode;
		this->size--;
	}
	this->iterator = NULL;
	this->head.next = NULL;
}

template<typename T>
bool CircleList<T>::deletedata(T &data) //һ�������ö���
{
	if (this->size == 0)
	{
		cout << "delete data error!" << endl;
		return false;
	}
	Linknode<T> *currentnode = &this->head;
	Linknode<T> *last = NULL;
	Linknode<T> *freenode = NULL;
	for (int i = 0; i < this->getlength(); i++)//����Ԫ��
	{
		if (currentnode->next->data== data) //��������ҵ����ֵ
		{	
			if (currentnode == &this->head) //����ҵ���ֵ ������ͷɾ�� 
			{
				last = this->getlastnode(this->getlength() - 1);//�ҵ�β�����
			}
			freenode = currentnode->next;//��ɾ���Ľ�㱣������
			currentnode->next = freenode->next;//����ɾ�����ĺ��
			if (freenode == this->iterator)
			{
				this->iterator = freenode->next;
			}
			break;//..ֹͣѭ��
		}
		currentnode = currentnode->next;//�ƶ����
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
bool CircleList<T>::deletedata( T &&data)//һ��������Ԫ�� C++11���ӵ�
{
	if (this->size == 0)
	{
		cout << "delete data error!" << endl;
		return false;
	}
	Linknode<T> *currentnode = &this->head;
	Linknode<T> *last = NULL;
	Linknode<T> *freenode = NULL;
	for (int i = 0; i < this->getlength(); i++)//����Ԫ��
	{
		if (currentnode->next->data == data) //��������ҵ����ֵ
		{
			if (currentnode == &this->head) //����ҵ���ֵ ������ͷɾ�� 
			{
				last = this->getlastnode(this->getlength()-1);//�ҵ�β�����
				//--�����ȼ�����    ǰ������ �ټ�
			}
			freenode = currentnode->next;//��ɾ���Ľ�㱣������
			currentnode->next = freenode->next;//����ɾ�����ĺ��
			if (freenode == this->iterator)
			{
				this->iterator = freenode->next;
			}
			break;//..ֹͣѭ��
		}
		currentnode = currentnode->next;//�ƶ����
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
	//ɾ�����нڵ� 
	Linknode<T> *currentnode = this->head.next;
	while (this->size>0)
	{	
		Linknode<T> *freenode = currentnode;//��Ҫ�ͷŵĽ�㱣����freenode
		currentnode = currentnode->next;//ָ����һ��  
		delete freenode;
		printf("%d  ", this->size);
		this->size--;
	}
	this->iterator = NULL;
	this->head.next = NULL;
}
#endif