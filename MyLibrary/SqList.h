#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;
#define bookData "bookData.txt"
#define MAXSIZE 100 //��󳤶�

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
	Bookcls * elem;  //ָ�����Ա�Ļ���ַ
	int length;      //���Ա�ǰ����
}SqList;


int InitList_Sq(SqList &L);     //��ʼ��˳���L������������
int InitList_Sq(SqList *L);     //��ʼ��˳���L��������ָ��
void DestroyList(SqList &L);    //�������Ա�L
void ClearList(SqList &L);      //������Ա�L
int GetLength(SqList L);        //�ж����Ա�L�ĳ���
int IsEmpty(SqList L);          //�ж����Ա�L�Ƿ�Ϊ��
int GetElem(SqList L, int i, Bookcls &e);      //��ȡ���Ա�L�е�ĳ������Ԫ�ص�����
int ListInsert_Sq(SqList &L, int i, Bookcls e);//�����Ա�L�е�i��Ԫ��֮ǰ��������Ԫ��e
int ListDelete_Sq(SqList &L, int i);           //�����Ա� L �е� i ��Ԫ��ɾ��
int Check(SqList L, Bookcls &e); //�ж��Ƿ��ظ�
void AddText(Bookcls book);      //��ӵ������ļ���