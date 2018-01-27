#include<stdio.h>

#include"linuxlinklist.h"

typedef  struct Teacher  //  every one object Are all is node.
{
    Linknode node;//next pointer
    int age;//data
}Teacher;

void TravelsList(Linklist *plist) // ����
{
	for (int i = 0; i < plist->Link_size; i++)
	{
		Teacher *temp = (Teacher*)List_getelement(plist, i);
		if (!temp)
		{
			return;
		}
		printf("age:%d", temp->age);
	}
}

//�ص�:
//��Ϊstruct�ĵ�ַ���ǵ�һ�������ĵ�ַ  ����Ҫ������ҵ��ĵ�ַ�غϣ�Ҳ����˵ͨ������ַ�Ϳ����ҵ�ҵ��
//����linux�ں������ʵ��  ����ҵ��������  Ȼ��ͨ��һ�׵ײ�linklist api������Щҵ��Ľ�����������γ�����
//ԭ�ȵ�Teacher�������t1 t2 t3 t4 t5�����໥֮�䶼������ϵ��
//ͨ��linklist�������ӣ�ʹ��ÿ����㶼��ǰ����̣�����ͷ��β��,�γ���һ���߼��ϵ�˳���������(�洢)������Ҫһ��
//��һ����ʽ�洢�ṹ.
int main(int argc, char *argv[])
{
	
    Linklist  *list=NULL;
    list=CreatList();
    Teacher t1,t2,t3,t4,t5;
    t1.age=10;
     t2.age=20;
      t3.age=30;
       t4.age=40;
        t5.age=50;
		Teacher t6;
		t6.age = 60;
        int len=List_getlength(list);//current Listnode size?	

        List_insert(list,(Linknode*)&t1,0);//1.list handle(address)  2.node(jiedian)  3.pos(location)
		List_insert(list,(Linknode*)&t2,0);
          List_insert(list,(Linknode*)&t3,0);
           List_insert(list,(Linknode*)&t4,0);
             List_insert(list,(Linknode*)&t5,0);

			 List_insert(list, (Linknode*)&t6, 1);

				 List_delete(list, 5);
			

           for(int i=0;i<List_getlength(list);i++)
           {
                Teacher *temp=(Teacher *)List_getelement(list,i);
                if(!temp)
                {
                        return 0;
                }
                printf("age:%d",temp->age);
           }
		  TravelsList(list);
		   
 /*
		   while (List_getlength(list)>0)
		   {
			   List_delete(list, 0);//delete 0 location
		   }
*/
		   //CleanList(list);
		  // printf("%d", List_getlength(list));
		   Destorylist(list);//free  memory
		 return 0;
}
