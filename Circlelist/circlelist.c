#include"circlelist.h"

/*
typedef struct Linknode
{
    struct Linknode *next;// pointer domain
}Linknode;

typedef struct tag_CircleList
{
    int size;//how many this List hava Element?
    Linknode head;//PY:jianduyuan
    Linknode *iterator;//  PY:you biao
}TCircleList;
*/

CircleList* CircleList_Create()
{
    TCircleList * TList=NULL;
   TList=( TCircleList *)malloc(sizeof(TCircleList));
   if(!TList)
   {
       printf("List malloc heap memory error\n");
       return NULL;
   }
    TList->head.next=NULL;
    TList->size=0;
    TList->iterator=NULL;
   return TList;//return the one handle for User

}//intil  List

Linknode *getListElement(CircleList *plist,int pos)
{
    TCircleList *TList=( TCircleList *)plist;
    if(!plist||pos<0)
    {
        printf("this plist address is NULL error\n");
        return NULL;
    }
    Linknode *currentnode=&TList->head;
    for(int i=0;i<pos;i++)
    {
        currentnode=currentnode->next;
    }
    return currentnode->next;

}//current pos location Element .

const int getListlength(CircleList *plist)
{
    TCircleList *TList=( TCircleList *)plist;
    if(!plist)
    {
        printf("this plist address is NULL error\n");
        return -1;
    }
    return TList->size;
}//current this list Element number

int CircleList_insert(CircleList *plist,Linknode *pnode,int pos)
{
    TCircleList *TList=( TCircleList *)plist;
    if(!plist||!pnode||pos<0||pos>TList->size)
    {
           printf("insert error\n");
           return -1;
    }
    Linknode * currentnode=&TList->head;
    for(int i=0;i<pos;i++)
    {
        currentnode=currentnode->next;
    }
    pnode->next=currentnode->next;
    currentnode->next=pnode;
    if(TList->size==0)
    {
        TList->iterator=pnode;
    }
    TList->size++;
    //if insert node for head location.
    if(currentnode==&TList->head)
    {
        Linknode *last=getListElement(TList,getListlength(TList)-1);//current the last Node
        last->next=currentnode->next;
    }
    return 0;
}//insert node
Linknode* CircleList_Deletepos(CircleList *plist,int pos)
{
    TCircleList *TList=(TCircleList *)plist;
    if(!plist||pos<0||TList->size==0||pos>TList->size)
    {
            printf("delete error  \n");
           return NULL;
    }
    Linknode *currentnode=&TList->head;
    Linknode *ret=NULL;
    Linknode *last=NULL;
    for(int i=0;i<pos;i++)
    {
         currentnode=currentnode->next;
    }
    //If  delete head node .
    if(currentnode==&TList->head)
    {
        last=getListElement(TList,getListlength(TList)-1);
    }
    ret=currentnode->next;
    currentnode->next=ret->next;
    TList->size--;
    //iterator if ret?

    if(last!=NULL)
    {
        TList->head.next = ret->next;
        last->next=ret->next;
    }
    if(ret==TList->iterator)
    {
        TList->iterator=ret->next;
    }
    if(TList->size==0)
    {
        TList->head.next=NULL;
        TList->iterator=NULL;
    }
    return ret; //return delete  node address
}//delete pos Element
Linknode*  CircleList_Deletenode(CircleList *plist,Linknode *pnode)
{
          TCircleList *TList=(TCircleList *)plist;

          if(!plist||!pnode||TList->size==0)
          {
               printf("delete error  \n");
              return NULL;
          }
         Linknode *currentnode=&TList->head;
         Linknode *ret=NULL;
         int i;
         //1.found pnode index
        for( i=0;i<TList->size;i++)
        {
                if(currentnode->next==pnode)
                {
                    printf("delete the node Successful\n");
                    ret=currentnode->next;
                    break;
                }
                currentnode=currentnode->next;
        }

        //use  this index delete  ELement
        if(ret!=NULL)
        {
            CircleList_Deletepos(TList,i);
        }
        return ret;
}//delete  Element==Pnode

void CircleList_Destory(CircleList *plist)
{
        if(plist)
        {
            free(plist);
        }

}//free memory

//-----------------------------------------------------------------------------about iterator (you biao) API()

Linknode *CircleList_reset_iterator(CircleList *plist)
{
       TCircleList *TList=(TCircleList *)plist;
       if(TList->size==0||!TList)
       {
           printf("reset this iterator error\n");
           return NULL;
       }
       TList->iterator=TList->head.next;
       Linknode *ret=TList->iterator;
       return ret;
}


Linknode *CircleList_movedown_iterator(CircleList *plist)
{
    TCircleList *TList=(TCircleList *)plist;
    if(TList->size==0||!TList)
    {
        printf("movedown this iterator error\n");
        return NULL;
    }
     Linknode *ret=NULL;
    if(TList->iterator!=NULL)
    {
        ret=TList->iterator;
        TList->iterator=ret->next;
    }
    return ret;
}

Linknode *CircleList_CurrentElement_iterator(CircleList *plist)
{
    TCircleList *TList=(TCircleList *)plist;
    if(TList->size==0||!TList||TList->iterator==NULL)
    {
        printf("Current  this iterator error\n");
        return NULL;
    }
    return TList->iterator;
}
