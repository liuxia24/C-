#include<iostream>
using namespace std;
//��װ���԰����� һ̨���Ե���������蹺��ͬ���̵����ʵ����װ  
//���������cpu   ����   �ڴ���  �ֱ�ʹ�ò�ͬ���̵Ĳ�Ʒ
//ʵ��һ����ܿ���ʹ�ò�ͬ���̵Ĳ�Ʒ  
class AbsCpu{  //���麯��������
public:
	virtual void work() = 0;
};
class AbsMainboard{  //���麯��������
public:
	virtual void work() = 0;
};
class Absmemorybank{  //���麯��������
public:
	virtual void work() = 0;
};

//Cpu���� ����ʵ��
class Intel :public AbsCpu{
protected:
	virtual void work() {
		cout << "Intel ���� �ȣ��죬���" << endl;
	}
};
class Amd :public AbsCpu{
protected:
	virtual void work() {
		cout << "Amd ���� ����,�Լ۱ȸ�" << endl;
	}
};

//���峧�� ����ʵ��
class Asus :public  AbsMainboard{
protected:
	virtual void work() {
		cout << "Asus����  ţ��" << endl;
	}
};

class Msi :public  AbsMainboard{
protected:
	virtual void work() {
		cout << "΢������  ��ţ��" << endl;
	}
};

//�ڴ�������ʵ��
class kinston :public Absmemorybank{
protected:
	virtual void work() {
		cout << "kinston�ڴ���  ̨����ţ�Ƴ���" << endl;
	}
};

class Sandisk :public Absmemorybank{
protected:
	virtual void work() {
		cout << "Sandisk�ڴ���  �й��о�" << endl;
	}
};

////////////////////////////////////////////////////////////
class computer{

public:
	computer(AbsCpu *cpu = NULL, AbsMainboard *board = NULL, Absmemorybank *memory = NULL)
		//Ĭ��ֵΪNULL�� �൱�����˸���ʼ��
	{
		this->m_Cpu = cpu;
		this->m_board = board;
		this->m_memory = memory;;
		//��ָ��ָ���ڴ��ַ��ֵ���ڲ�˽��ָ�����
	}
	bool work() const {  
		if (!m_Cpu || !m_board || !m_memory)
		{
			cout << "�豸��ʼ��ʧ��,���³�ʼ��!" << endl;
			return false;
		}
		this->m_Cpu->work();
		this->m_board->work();
		this->m_memory->work();
		//ͬһ��������ж�����̬�仯    ��̬�ı�����ʽ
		return true;
	}
private:
	AbsCpu *m_Cpu;
	AbsMainboard *m_board;
	Absmemorybank *m_memory;
	//��ֻ�Ǹ���ָ�����  �����ͷ��ڴ���� ֻ����Ϊһ�����ö���
};


//����ģʽ+����ģʽ���������    
class computerFac{
public:
	enum CPU{AMD,INTEL}; 
	enum MAINBOARD{ ASUS, MSI };
	enum MEMORYBANK{ KINSTON, SANDISK };
	//�����������޼�ѡ��һ��  ����Ҫʹ��ö������ ����ö��ֵ  
public:
	computerFac(CPU parts_one, MAINBOARD parts_two, MEMORYBANK parts_three)
		:m_Cpu(NULL), 
		m_board(NULL), 
		m_memory(NULL),
		com(NULL)
	{

		//ͨ��parts_one  ����ѡ��   instance  object  (CPU���̵�)
		switch (parts_one)
		{
		case computerFac::AMD:
			this->m_Cpu = new Amd;
			break;
		case computerFac::INTEL:
			this->m_Cpu = new Intel;
			break;
		}

		//ͨ��parts_two����ѡ��instance  object  �����峧�̵ģ�
		switch (parts_two)
		{
		case computerFac::ASUS:
			this->m_board = new Asus;
			break;
		case computerFac::MSI:
			this->m_board = new Msi;
			break;
		}

		//ͨ��parts_three����ѡ��instance  object  ���ڴ泧�̵ģ�
		switch (parts_three)
		{
		case computerFac::KINSTON:
			this->m_memory = new kinston;
			break;
		case computerFac::SANDISK:
			this->m_memory = new Sandisk;
			break;
		}

		this->com = new computer(this->m_Cpu, this->m_board, this->m_memory);
	}

	//���õײ�work  �ɹ�return true  ����return false
	bool Computer_work() const {
		if (!com){
			return false;
		}
		this->com->work();
		return true;
	}

	//�ͷŶ������ڴ�
	~computerFac(){	
		delete this->m_Cpu;
		delete this->m_board;
		delete this->m_memory;
		delete this->com;	
	}
private:
	computer *com;
	AbsCpu *m_Cpu;
	AbsMainboard *m_board;
	Absmemorybank *m_memory;
	//������ϵ
};

// ��һ����װ  Intel Cpu   MSI����   Sandisk�ڴ���
void test01(){
	//��ʱ��ֻ��Ҫ֪��Ҫѡ��ö�����ʹ����ʵ������,��computer�����ͺ�
	computerFac com(computerFac::INTEL, computerFac::MSI, computerFac::SANDISK);
	bool isok=com.Computer_work();
	if (isok){
		cout << "YES!" << endl; 
	}
	else{
		cout << "NO!" << endl;
	}
}

// �ڶ�����װ  AMD Cpu   ASUS����   Kinston�ڴ���
void test02(){
	//��ʱ��ֻ��Ҫ֪��Ҫѡ��ö�����ʹ����ʵ������,��computer�����ͺ�
	computerFac com(computerFac::AMD, computerFac::ASUS, computerFac::KINSTON);
	bool isok = com.Computer_work();
	if (isok){
		cout << "YES!" << endl;
	}
	else{
		cout << "NO!" << endl;
	}
}
int main()
{	
	cout << "��һ������:" << endl;
	test01();
	cout << endl;
	
	cout << "�ڶ�������:" << endl;
	test02();
	system("pause");
	return 0;
}
