#include<iostream>
using namespace std;
//组装电脑案例： 一台电脑的三个配件需购买不同厂商的配件实现组装  
//三个配件：cpu   主板   内存条  分别使用不同厂商的产品
//实现一个框架可以使用不同厂商的产品  
class AbsCpu{  //纯虚函数抽象类
public:
	virtual void work() = 0;
};
class AbsMainboard{  //纯虚函数抽象类
public:
	virtual void work() = 0;
};
class Absmemorybank{  //纯虚函数抽象类
public:
	virtual void work() = 0;
};

//Cpu厂商 具体实现
class Intel :public AbsCpu{
protected:
	virtual void work() {
		cout << "Intel 厂商 稳，快，舒服" << endl;
	}
};
class Amd :public AbsCpu{
protected:
	virtual void work() {
		cout << "Amd 厂商 便宜,性价比高" << endl;
	}
};

//主板厂商 具体实现
class Asus :public  AbsMainboard{
protected:
	virtual void work() {
		cout << "Asus主板  牛逼" << endl;
	}
};

class Msi :public  AbsMainboard{
protected:
	virtual void work() {
		cout << "微星主板  更牛逼" << endl;
	}
};

//内存条厂商实现
class kinston :public Absmemorybank{
protected:
	virtual void work() {
		cout << "kinston内存条  台湾最牛逼厂商" << endl;
	}
};

class Sandisk :public Absmemorybank{
protected:
	virtual void work() {
		cout << "Sandisk内存条  中规中矩" << endl;
	}
};

////////////////////////////////////////////////////////////
class computer{

public:
	computer(AbsCpu *cpu = NULL, AbsMainboard *board = NULL, Absmemorybank *memory = NULL)
		//默认值为NULL的 相当于做了个初始化
	{
		this->m_Cpu = cpu;
		this->m_board = board;
		this->m_memory = memory;;
		//将指针指向内存地址赋值给内部私有指针变量
	}
	bool work() const {  
		if (!m_Cpu || !m_board || !m_memory)
		{
			cout << "设备初始化失败,重新初始化!" << endl;
			return false;
		}
		this->m_Cpu->work();
		this->m_board->work();
		this->m_memory->work();
		//同一调用语句有多种形态变化    多态的表现形式
		return true;
	}
private:
	AbsCpu *m_Cpu;
	AbsMainboard *m_board;
	Absmemorybank *m_memory;
	//这只是辅助指针变量  不做释放内存管理 只是作为一个引用而已
};


//策略模式+工厂模式的设计理念    
class computerFac{
public:
	enum CPU{AMD,INTEL}; 
	enum MAINBOARD{ ASUS, MSI };
	enum MEMORYBANK{ KINSTON, SANDISK };
	//若是想在有限集选择一个  则需要使用枚举类型 定义枚举值  
public:
	computerFac(CPU parts_one, MAINBOARD parts_two, MEMORYBANK parts_three)
		:m_Cpu(NULL), 
		m_board(NULL), 
		m_memory(NULL),
		com(NULL)
	{

		//通过parts_one  参数选择   instance  object  (CPU厂商的)
		switch (parts_one)
		{
		case computerFac::AMD:
			this->m_Cpu = new Amd;
			break;
		case computerFac::INTEL:
			this->m_Cpu = new Intel;
			break;
		}

		//通过parts_two参数选择instance  object  （主板厂商的）
		switch (parts_two)
		{
		case computerFac::ASUS:
			this->m_board = new Asus;
			break;
		case computerFac::MSI:
			this->m_board = new Msi;
			break;
		}

		//通过parts_three参数选择instance  object  （内存厂商的）
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

	//调用底层work  成功return true  否则return false
	bool Computer_work() const {
		if (!com){
			return false;
		}
		this->com->work();
		return true;
	}

	//释放堆区的内存
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
	//关联关系
};

// 第一套组装  Intel Cpu   MSI主板   Sandisk内存条
void test01(){
	//此时我只需要知道要选择枚举类型代表的实力对象,和computer这个类就好
	computerFac com(computerFac::INTEL, computerFac::MSI, computerFac::SANDISK);
	bool isok=com.Computer_work();
	if (isok){
		cout << "YES!" << endl; 
	}
	else{
		cout << "NO!" << endl;
	}
}

// 第二套组装  AMD Cpu   ASUS主板   Kinston内存条
void test02(){
	//此时我只需要知道要选择枚举类型代表的实力对象,和computer这个类就好
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
	cout << "第一套配置:" << endl;
	test01();
	cout << endl;
	
	cout << "第二套配置:" << endl;
	test02();
	system("pause");
	return 0;
}
