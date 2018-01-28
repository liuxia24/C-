#ifndef CONSLE_COUNT_H
#define CONSLE_COUNT_H
#include<stdlib.h>
#include<string.h>
#include<memory.h>

typedef void Consle;

typedef unsigned int(*facoper)(Consle *Con);  //函数指针类型  

facoper factoryoperator(Consle*, char);
typedef  struct Consle_Count
{
    unsigned int a;//number
    unsigned int b;//number
    char op;//+ - * /

	facoper coper;//函数指针类型

    unsigned int result;//保存结果
    // result=number a  op  number b;  之所以用无符号因其数值范围更大
}TConsle;


Consle *Consle_Creater()//创建一个句柄
{
    //初始化底层结构体的属性 并返回一个句柄给上层使用
    TConsle *con=(TConsle *)malloc(sizeof(TConsle));
    if(!con)//判断是否malloc 成功 否则return NULL
    {
         printf("Consle_Creater()NULL error!!!\n");
         return NULL;
    }
    memset(con,0,sizeof(TConsle));//做一个负责任的人  给属性初始化为0
    return (void *)con;//返回一个句柄address
}

//第一步输入数字和符号
int  Consle_SetoperatorNum(Consle *Con,unsigned int firstNum,unsigned int secondNum)//提供firstNum 和secondNum接口
{
       if(!Con)
       {
           printf("Consle_Inputoperator()NULL error!!!\n");
           return -1;//代表exception
       }
       TConsle *Tcon=(TConsle *)Con;//底层知道句柄的类型
       Tcon->a=firstNum;
       Tcon->b=secondNum;
       return 0;
}


//第二步开始业务计算结果
int Consle_conunt_start(Consle *Con,char str)//提供operator接口
{
    if(!Con)
    {
        printf("Consle_conunt_start()NULL error!!!\n");
        return -1;//代表exception
    }
    TConsle *Tcon=(TConsle *)Con;//底层知道句柄的类型
	Tcon->coper = factoryoperator(Con, str);
	if (Tcon->coper!=NULL)//如果不等于空，那么将实现函数调用
	{
	Tcon->result= Tcon->coper(Con);//根据回调函数返回的业务函数入口地址，实现调用  参生多态.
	}
	else
	{
		printf("No count Result,return -1\n");
		Tcon->result = -1;
	}
	
    return 0;

    //Q：如果需要添加业务 例如添加一个 平方根的求解  那么只需要在Switch分支添加就好了，可添加的越来越多,显然我并不希望上层应用调用底层业务时把其他业务也
    //进行编译起来.为了使代码更具扩展性,这里只使用了封装。那么为了使代码更可维护和可扩展，就需使用设计模式工厂模式.

    //将拥有共同点的业务  抽象出来一个抽象类，而operator共有的特性就是求解  通过多态的效果求解/.
}

//打印出结果
unsigned int Consle_Outputresult(Consle *Con)
{
    if(!Con)
    {
        printf("Consle_Outputresult()NULL error!!!\n");
        return -1;//代表exception
    }
    TConsle *Tcon=(TConsle *)Con;//底层知道句柄的类型
    return Tcon->result;
}

//以下是业务     以后要添加业务直接在底层  写好业务函数就可以了----------------------------------------------------------------------------
//但必须按照提前约定好的返回值和参数类型写    一个符合规定的业务函数()
unsigned int  operator_add(Consle *Con)
{
	unsigned int result;
    if(!Con)
    {
        printf("operator_add()NULL error!!!\n");
        return -1;//代表exception
    }
    TConsle *Tcon=(TConsle *)Con;//底层知道句柄的类型
    result=Tcon->a+Tcon->b;
    return result;
}

unsigned int  operator_minus(Consle *Con)
{
	unsigned  int result;
    if(!Con)
    {
        printf("operator_minus()NULL error!!!\n");
        return -1;//代表exception
    }
    TConsle *Tcon=(TConsle *)Con;//底层知道句柄的类型
    result=Tcon->a-Tcon->b;
    return result;
}

unsigned int  operator_divid(Consle *Con)
{	
	unsigned int result;
    if(!Con)
    {
        printf("operator_divid()NULL error!!!\n");
        return -1;//代表exception
    }
    TConsle *Tcon=(TConsle *)Con;//底层知道句柄的类型
	if (Tcon->a != 0) //除数不为0的情况
		result = Tcon->a / Tcon->b;
	else
		result = 0;
    return result;
}

unsigned int operator_multiy(Consle *Con)
{
	unsigned int result;
    if(!Con)
    {
        printf("operator_multiy()NULL error!!!\n");
        return -1;//代表exception
    }
    TConsle *Tcon=(TConsle *)Con;//底层知道句柄的类型
    result=Tcon->a*Tcon->b;
    return result;
}



//----------------------------------------------------------------------------以下是调用相关业务的   工厂模式（实例化哪个对象）进行封装
//设置工厂模式  封装业务在一起  通过工厂返回函数的入口地址 

//添加业务在Switch分支此添加就可以了   不用直接接触到各个operator的算法(要是不小心修改弄错了，可会造成整个程序爆炸)
facoper factoryoperator(Consle *Con,char ch)
{
	unsigned int(*p)(Consle *Con) = NULL;//这是一个函数指针变量  可以接受相同类型的函数入口地址
	switch (ch)//根据传入的operator  决定函数的入口地址
	{
	case'+':
		p = operator_add;
		break;
	case'-':
		p = operator_minus;
		break;
	case'*':
		p = operator_multiy;
		break;
	case'/':
		p = operator_divid;
		break;
	default:
		printf("you  input operator 参数 error!\n");
		break;
	}
	return p;//返回函数的入口地址
}

//释放计算器控制台程序 申请的内存
void Consle_Destory(Consle *Con)
{
   if(!Con)
   {
       free(Con);
   }
}



#endif // CONSLE_COUNT_H


//以后添加业务只要按照规定写好自己的operator业务函数，然后在工厂factory添加分支就可以使用计算了。
//此时的优点：并不会像之前那样添加业务的时候直接和 其他什么add  minus .....业务算法接触
//优点：此框架的添加和删除根本不会影响到别的业务，也不用担心  (不小心修改到别的业务细节算法的事情) 因为根本不可能.