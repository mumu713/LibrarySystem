#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;
#define bookData "bookData.txt"
#define MAXSIZE 100 //最大长度

class Bookcls {
public:
	unsigned int BookNo;
	string BookName;
	string BookAuthor;
	unsigned int ExistNumber;
	unsigned int AllNumber;

};

typedef struct
{
	Bookcls * elem;  //指向线性表的基地址
	int length;      //线性表当前长度
}SqList;


int InitList_Sq(SqList &L);     //初始化顺序表L，参数用引用
int InitList_Sq(SqList *L);     //初始化顺序表L，参数用指针
void DestroyList(SqList &L);    //销毁线性表L
void ClearList(SqList &L);      //清空线性表L
int GetLength(SqList L);        //判断线性表L的长度
int IsEmpty(SqList L);          //判断线性表L是否为空
int GetElem(SqList L, int i, Bookcls &e);      //获取线性表L中的某个数据元素的内容
int ListInsert_Sq(SqList &L, int i, Bookcls e);//在线性表L中第i个元素之前插入数据元素e
int ListDelete_Sq(SqList &L, int i);           //将线性表 L 中第 i 个元素删除
int Check(SqList L, Bookcls &e); //判断是否重复
void AddText(Bookcls book);      //添加到本地文件夹