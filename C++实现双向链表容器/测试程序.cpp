#include<iostream>
#include"DoublyList.h"
using namespace std;

class Student
{
	friend ostream& operator<<(ostream &out, Student &stu)
	{
		out << "Name:" <<stu.m_name<< "   Age:" << stu.m_age << "   " << endl;
		return out;
	}
public:
	Student() :m_age(0)
	{
		strcpy(this->m_name, "  ");
	}
	Student(int age,char *name)
	{
		this->m_age = age;
		strcpy(m_name, name);
	}
	//因为我并没在堆区申请内存所以不会出现深拷贝问题   所以就使用默认的拷贝构造吧 
	//打印信息
	void show()
	{
		cout << "Name:" << this->m_name << "   Age:" << this->m_age << "   " << endl;
	}

	//currentnode->next->data == pnode;重载operator==号操作符
	bool operator==(Student &stu)
	{
		if (this->m_age == stu.m_age&&strcmp(this->m_name, stu.m_name)==0)
		{
			return true;
		}
		return false;
	}
	
	//stu.operator>(stu2);
	bool operator>(Student& stu)
	{
		if (this->m_age > stu.m_age)//按年龄来排序吧
		{
			return true;
		}
		return false;
	}
	bool operator<(Student& stu)
	{
		if (this->m_age < stu.m_age)//按年龄来排序吧
		{
			return true;
		}
		return false;
	}
private:
	int m_age;
	char m_name[32];
};

//回调函数
bool cmpStudent(Student &stu1, Student &stu2)
{
	if (stu1 < stu2)//如果stu1> stu2 返回真  否则返回假
	{
		return true;
	}
	return false;
}
int main()
{
	Student stu1(24, "kobebryant"), stu2(23, "james"), stu3(15, "Antony"),
		stu4(32, "oneal"), stu5(35, "durant"), stu6(0, "kuzima");

	Student stu7(10, "haha");
	DoublyList<Student>  dlist;
	dlist.insertElement(stu1, dlist.getlength());
	dlist.insertElement(stu2, dlist.getlength());
	dlist.insertElement(stu3, dlist.getlength());
	dlist.insertElement(stu4, dlist.getlength());
	dlist.insertElement(stu5, dlist.getlength());
	dlist.insertElement(stu6, dlist.getlength());
	//每次都在尾部插入
	
	//dlist.insertElement(stu7, 0);
	//dlist.deleteElement(3);
	/*
	dlist.deleteElement(stu1);
	dlist.deleteElement(stu3);*/
	//sortdoublyList()
	sortdoublyList<Student>(&dlist,cmpStudent); //回调函数入口地址放入进去
	dlist.Traversal(true);//默认是正向遍历  传入false代表逆向遍历
	system("pause");
	return 0;
}
