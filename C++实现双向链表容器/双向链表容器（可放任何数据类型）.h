#pragma once//��ֹ�ظ�����

// ����һ�����
template<typename T>
class LinkNode
{
public:
	LinkNode *prior;//ָ��ǰ��
	T	data;//������
	LinkNode *next;//ָ����
};



//˫������
template<typename T>
class DoublyList
{	
	template<typename T>
	friend bool sortdoublyList(DoublyList<T> *plist, bool(*cmp)(T &a, T &b)); 
	//������Ԫ����  ���Է��ʵ�˽�б���
	
public://�ṩ���ʹ�õ�API

	DoublyList();//���캯��
	~DoublyList();//��������
	bool insertElement(T &pnode, int pos);
	bool insertElement(T &&pnode, int pos);
	bool deleteElement(int pos);
	bool deleteElement(T &pnode);
	int getlength()const;
	void Traversal(bool ispositive = true);
	
private://���ڸ�����ʹ�õ�  ˽�е�
	LinkNode<T> head;
	LinkNode<T> last;
	int size;
	//headΪͷ���ලԪ   lastΪβ���ලԪ ������˫������Ͳ���ȥ�ж�ͷ��β��  һ��ҵ���߼��͹���(Ҳ���ǿռ任ʱ��)
};

template<typename T>
DoublyList<T>::DoublyList()
{
	this->size = 0;
	this->head.prior = NULL; //ͷ��ǰ��ΪNULL
	this->last.next = NULL;//β�ĺ��ΪNULL 
	this->head.next = &this->last;
	this->last.prior = &this->head;
}

template<typename T>
bool DoublyList<T>::insertElement(T &pnode, int pos)
{
	//���ܳ��ֵ��쳣���     ������±겻�Ϸ�
	if (pos<0 || pos>this->size)
	{
		cout << "insert Element  error  sorry������" << endl;
		return false;
	}
	
	LinkNode<T> *newcode = new LinkNode<T>; //�����µĽ��
	newcode->data = pnode;  //���ݵĿ�����ֵ����  Ҫע�������ǳ����������   ����ָ��ͬһ���ڴ� �ظ������ͷ�
	
	LinkNode<T> *currentnode = &this->head;//ͷ���ලԪ��ַ���� ����ָ����� currentnode
	
	
	//����㷨:��Ϊβ��Ҳ�мලԪ  ��ǰλ�ô���size/2��ʱ�� ��β����ʼ�����в���(Ч�ʸ���)
	
	for (int i = 0; i < pos; i++)//�ƶ�����ǰλ��   
	{
		currentnode = currentnode->next;
	}
	
	LinkNode<T> *ret = currentnode->next;//���浱ǰ�ĺ�̽�� 
	newcode->next = currentnode->next;
	currentnode->next = newcode;
	//������newnode next��ǰ���ͺ��
	
	newcode->prior = ret->prior;
	ret->prior = newcode;
	//������newnode prior�ĺ�̺�ǰ��
	
	
	this->size++;//Ԫ��+1	
	return true;
}
template<typename T>
bool DoublyList<T>::insertElement(T &&pnode, int pos)
{
	//���ܳ��ֵ��쳣���     ������±겻�Ϸ�
	if (pos<0 || pos>this->size)
	{
		cout << "insert Element  error  sorry������" << endl;
		return false;
	}
	LinkNode<T> *newcode = new LinkNode<T>; //�����µĽ��
	
	newcode->data = pnode;  //���ݵĿ���  Ҫע�������ǳ����������   ����ָ��ͬһ���ڴ� �ظ��ͷ�
	LinkNode<T> *currentnode = &this->head;//ͷ���ලԪ��ַ���� ����ָ����� currentnode
	
	for (int i = 0; i < pos; i++)
	{
		currentnode = currentnode->next;
	}
	LinkNode<T> *ret = currentnode->next;//���浱ǰ�ĺ�̽�� 
	newcode->next = currentnode->next;
	currentnode->next = newcode;
	
	//������newnode next��ǰ���ͺ��
	newcode->prior = ret->prior;
	ret->prior = newcode;
	
	//������newnode prior�ĺ�̺�ǰ��
	this->size++;//Ԫ��+1	
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
	
	LinkNode<T> *freenode = currentnode->next;//ɾ����λ�ý�� �ø���ָ��ָ��
	LinkNode<T> *ret = freenode->next;
	currentnode->next = ret;//����ɾ�����ĺ�� 
	ret->prior = currentnode;
	//��������prior�� ע��������һ��˫������
	
	delete freenode;//�ͷ�ɾ�������ڴ�ռ�
	
	this->size--;
	return true;
}

template<typename T>
bool DoublyList<T>::deleteElement(T &pnode)
{
	if (this->size == 0)//���û��Ԫ���ǻ�ɾ����ʲô����
	{
		cout << "delete error  sorry!" << endl;
		return false;
	}
	
	LinkNode<T> *currentnode = &this->head;
	LinkNode<T> *freenode = NULL;
	
	while (currentnode != &this->last)//������β��
	{
		if (currentnode->next->data == pnode)//����ҵ�����ͬ������
		{
			freenode = currentnode->next;//ɾ����λ�ý�� �ø���ָ��ָ��
			LinkNode<T> *ret = freenode->next;
			currentnode->next = ret;//����ɾ�����ĺ�� 
			ret->prior = currentnode;
			break;
		}
		currentnode = currentnode->next;//�ƶ�����һ�����
	}
	if (freenode)//����ҵ���
	{
		cout << "�ҵ��ˣ���ɾ���˸�����Ϣ:" << freenode->data;
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
	if (ispositive)//���Ϊtrue Ĭ��������� ���
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
		//�ͷŽ���ڶ���������ڴ�ͺ���
	LinkNode<T> *currentnode = this->head.next;
	while (currentnode != &this->last)
	{
		LinkNode<T> *freenode = currentnode;
		currentnode = currentnode->next;//�ƶ�����һ�����
		delete freenode;
	}
	this->size = 0;
}
//֪ʶ��:
//����ָ������������ ��ǰԼ�����˷���ֵ�Ͳ������� 
//�ṩһ���ӿ� ��ܱ��ֲ���������  ������д�ĺ�����ڵ�ַ������  ����ֱ�ӵ���
template<typename T>
bool sortdoublyList(DoublyList<T> *plist, bool(*cmp)(T &a, T &b))
{
	//���û��Ԫ�ػ���ֻ��һ��Ԫ�ز����ڶԱ���������
	if ( 0== plist->size ||  1== plist->size)
	{
		cout << "sort error sorry" << endl;
		return false;
	}
	bool exchange=true;
	for (int i = 0; (i < plist->size)&&(exchange); i++)//ѭ�����������Ϊ��ʱ
	{	
		LinkNode<T> *firstnode = plist->head.next;//��һ�����
		LinkNode<T> *secondnode = firstnode->next;
		LinkNode<T> *cmplast = &plist->last;
		exchange=false;
		//���õ���ð������ ��������Ԫ�ؽ��бȽ�(���㷨�����Խ����Ż�������һ��ѭ�����ٽ��н���Ԫ���ˣ���ô�����������)
		while (secondnode !=cmplast )//��secondnode Ϊlast˵���Աȵ����һ�������
		{
			if (cmp(firstnode->data, secondnode->data))//����true˵��stu1>stu2 ǰһ����ں�һ��
			{
				T temp = firstnode->data;  //ֵ����
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