#include<stdio.h>

#include"linuxlinklist.h"

typedef  struct Teacher  //  every one object Are all is node.
{
    Linknode node;//next pointer
    int age;//data
}Teacher;

void TravelsList(Linklist *plist) // 遍历
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

//重点:
//因为struct的地址就是第一个变量的地址  所以要将结点和业务的地址重合，也就是说通过结点地址就可以找到业务
//所以linux内核链表的实现  是让业务包含结点  然后通过一套底层linklist api来将这些业务的结点连接起来形成链表。
//原先的Teacher所定义的t1 t2 t3 t4 t5对象相互之间都毫无联系，
//通过linklist将其连接，使得每个结点都有前驱后继（除了头和尾）,形成了一套逻辑上的顺序表，物理上(存储)并不需要一致
//的一套链式存储结构.
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
