#ifndef CIRCLELIST_H
#define CIRCLELIST_H
#include<stdlib.h>
#include<stdio.h>
//pragma once
typedef void CircleList;  //i don't want to you know(PY:bu xiang rang ren zhidao typename)

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
CircleList* CircleList_Create();//intil  List
int CircleList_insert(CircleList *plist,Linknode *pnode,int pos);//insert node
Linknode*  CircleList_Deletepos(CircleList *plist,int pos);//delete pos Element
Linknode*  CircleList_Deletenode(CircleList *plist,Linknode *pnode);//delete  Element==Pnode
const int getListlength(CircleList *plist);//current this list Element number
Linknode *getListElement(CircleList *plist,int pos);//current pos location Element .
void CircleList_Destory(CircleList *plist);//free memory
//-----------------------------------------------------------------------------about iterator (you biao) API()

//revert iterator for head.next   and  return this iterator-> (address).
Linknode *CircleList_reset_iterator(CircleList *plist);

//iterator  move down and return this iterator
Linknode *CircleList_movedown_iterator(CircleList *plist);

//Current this iterator->(address)
Linknode *CircleList_CurrentElement_iterator(CircleList *plist);

#endif // CIRCLELIST_H
