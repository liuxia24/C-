#include<iostream>
#include"corporator.hpp"
#include<map>
enum Enumcor  //枚举类型   枚举成员  S代表销售部   D代表技术部   F代表财务部
{
	S=1,D,F
};
//自定义数据类型 的别名
typedef multimap<Enumcor, corporator*>::value_type mvt;
typedef pair<Enumcor, corporator*> pec;
using namespace std;
//Multimap 案例 :
//1个key值可以对应多个valude =分组
//公司有销售部 sale （员工2名）、技术研发部 development （1人）、财务部 Financial （2人）
//人员信息有：姓名，年龄，电话、工资等组成
//通过 multimap进行 信息的插入、保存、显示
//分部门显示员工信息

//因为multimap是可以重复出现key值的  是一个红黑树平衡二叉树的数据结构
//思路:将键值为1设置为 销售部门   键值为2的设置为技术部    键值为3的设置为财务部

void printf01(multimap<Enumcor, corporator*> &m)
{
	m.insert(pec(D, new development("xiaoan", 19, "22222", 8000)));
	m.insert(pec(D, new development("xiaoliu", 15, "33333", 9000)));
}

void printsamedepartment(multimap<Enumcor, corporator*>  &m, Enumcor department)
//功能根据key键值查找相同部门的人  并且打印信息
{
	multimap<Enumcor, corporator*> ::iterator it=m.find(department);  //  return  ? end():where iterator;
	int num=m.count(department);//搜索相同key值的个数   返回int的数量
	int tag = 0;
	switch (department)
	{
	case S:
		cout << "查找的销售部人员信息:" <<num<<"个人"<< endl;
		break;
	case D:
		cout << "查找的技术部人员信息:" << num << "个人" << endl;
		break;
	case F:
		cout << "查找的财务部人员信息:" << num << "个人" << endl;
		break;
	}
	while (it != m.end()&&tag<num)//如果返回的不是end()说明找到了这个部门的人
	{
		it->second->show();
		it++;
		tag++;
	}
}

//查找  某个部门department  的 人的名字name   并且修改信息 
bool Modifymemberimformation(multimap<Enumcor, corporator*>  &m, char *name, Enumcor department)//修改个人信息
{
	multimap<Enumcor, corporator*>::iterator it = m.find(department);
	int num = m.count(department);//搜索相同key值的个数   返回int的数量
	int tag = 0;
	
	while (it != m.end()&&tag < num)//如果返回的不是end()说明找到了这个部门的人
	{
		if (!strcmp(it->second->m_name,name))//用字符串比较api相等返回0   不相等返回1
		{
			//*it->second->m_name = "xiaoxiao";
			strcpy(it->second->m_name, "xiaoxiao");
			return true;
		}
		it++;
		tag++;
	}
	return false;
}
//测试程序
int test02()
{
	multimap<Enumcor, corporator*> m;//默认是根据键值从小到大进行排序
	//1  销售部
	m.insert(mvt(S, new saleperson("kobe", 24, "18819", 2500)));
	m.insert(mvt(S, new saleperson("james", 23, "10000", 2000)));

	//2  技术部
	m.insert(pec(D, new development("xiaoan", 19, "22222", 8000)));
	m.insert(pec(D, new development("xiaoliu", 15, "33333", 9000)));
	m.insert(pec(D, new development("xiaoma", 12, "88888", 5000)));

	//3  财务部
	m.insert(make_pair<Enumcor, corporator*>(F, new Finanical("dandan", 18, "28498978", 3500)));
	m.insert(make_pair<Enumcor, corporator*>(F, new Finanical("kaka", 18, "7878", 6000)));

	printsamedepartment(m, D);

	Modifymemberimformation(m, "xiaoma", D);

	for (multimap<Enumcor, corporator*>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << "    ";//out put key 
		it->second->show();//use  show() API
	}
	return 0;
}
int main()
{
	test02();
	return 0;
}
