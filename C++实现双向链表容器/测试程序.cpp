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
	//��Ϊ�Ҳ�û�ڶ��������ڴ����Բ�������������   ���Ծ�ʹ��Ĭ�ϵĿ�������� 
	//��ӡ��Ϣ
	void show()
	{
		cout << "Name:" << this->m_name << "   Age:" << this->m_age << "   " << endl;
	}

	//currentnode->next->data == pnode;����operator==�Ų�����
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
		if (this->m_age > stu.m_age)//�������������
		{
			return true;
		}
		return false;
	}
	bool operator<(Student& stu)
	{
		if (this->m_age < stu.m_age)//�������������
		{
			return true;
		}
		return false;
	}
private:
	int m_age;
	char m_name[32];
};

//�ص�����
bool cmpStudent(Student &stu1, Student &stu2)
{
	if (stu1 < stu2)//���stu1> stu2 ������  ���򷵻ؼ�
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
	//ÿ�ζ���β������
	
	//dlist.insertElement(stu7, 0);
	//dlist.deleteElement(3);
	/*
	dlist.deleteElement(stu1);
	dlist.deleteElement(stu3);*/
	//sortdoublyList()
	sortdoublyList<Student>(&dlist,cmpStudent); //�ص�������ڵ�ַ�����ȥ
	dlist.Traversal(true);//Ĭ�����������  ����false�����������
	system("pause");
	return 0;
}
