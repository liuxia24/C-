#include <stdio.h>
#include"consle_count.h"

int main(void)
{
    /*
    char *ch="hello";
    printf("%s",ch);
    */
    Consle *consle=NULL;
    consle=Consle_Creater();
    if(!consle)
    {
        printf("Consle_Creater() malloc  error!!!\n");
        return 0;
    }


    int ret;
	ret = Consle_SetoperatorNum(consle, 100, 100);
    if(ret!=0)//如果输入的符号和数字  出现异常底层将会返回-1
    { 
         printf("Consle_Inputoperator() error!!!\n");
         return 0;
    }

	Consle_conunt_start(consle, '-');//此时我需要知道回调函数和Consle结构体
	//返回业务功能的入口地址

    unsigned int result= Consle_Outputresult(consle);//结果通过返回值返回出来
    printf("The last result=%d",result);

    Consle_Destory(consle);

    return 0;
}
