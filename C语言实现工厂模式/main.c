#include <stdio.h>
#include"consle_count.h"

int main(void)
{
    Consle *consle=NULL;
    consle=Consle_Creater();
    if(!consle)
    {
        printf("Consle_Creater() malloc  error!!!\n");
        return 0;
    }

    int ret;
	ret = Consle_SetoperatorNum(consle, 100, 100);
    if(ret!=0)//  出现异常底层将会返回-1
    { 
         printf("Consle_Inputoperator() error!!!\n");
         return 0;
    }

	Consle_conunt_start(consle, '-');//上层应用需知道 如何传入参数，参数有什么功能


    unsigned int result= Consle_Outputresult(consle);//结果通过返回值返回出来
    printf("The last result=%d",result);

    Consle_Destory(consle);//释放资源

    return 0;
}
