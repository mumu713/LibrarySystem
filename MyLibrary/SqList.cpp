#include "SqList.h"


//��ʼ�����Ա�
//����������
int InitList_Sq(SqList &L) //����һ���յ�˳���L
{
	L.elem = new Bookcls[MAXSIZE]; //Ϊ˳������ռ�
	if (!L.elem)
	{
		exit(OVERFLOW); //�洢����ʧ��
	}
	L.length = 0;
	return 0;
}


//��ʼ�����Ա�
//������ָ��
int InitList_Sq(SqList *L) //����һ���յ�˳���L
{
	L->elem = new Bookcls[MAXSIZE]; //Ϊ˳������ռ�
	if (!L->elem)
	{
		exit(OVERFLOW); //�洢�ռ����ʧ��
	}
	L->length = 0;
	return 0;
}


//�������Ա�L
void DestroyList(SqList &L)
{
	if (L.elem)
	{
		delete[] L.elem; //�ͷŴ洢�ռ�
	}
}

//������Ա�L
void ClearList(SqList &L)
{
	L.length = 0; //�����Ա�ĳ�����Ϊ 0
}


//�ж����Ա�L�ĳ���
int GetLength(SqList L)
{
	return (L.length);
}


//�ж����Ա�L�Ƿ�Ϊ��
int IsEmpty(SqList L)
{
	if (L.length == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


//�ж��Ƿ��ظ�
int Check(SqList L, Bookcls &e)
{
	for (int i = 0; i < L.length; i++)
	{
		if ( e.BookName == ""  &&  e.BookAuthor == "")
		{
			return -1;
		}
		else if (L.elem[i].BookName == e.BookName  &&  L.elem[i].BookAuthor == e.BookAuthor) {
			return -2;
		}
	}
	return 0;
}


//��ӵ������ļ���
void AddText(Bookcls book)
{
	fstream file1;
	file1.open(bookData, ios::app | ios::out);
	string data = to_string(book.BookNo) + "," + book.BookName + "," + book.BookAuthor + "," + to_string(book.ExistNumber) + "," + to_string(book.AllNumber);
	file1 << data << endl;
	file1.close();
}



//ȡֵ������λ�� i ��ȡ��Ӧλ������Ԫ�ص����ݣ�
//��ȡ���Ա�L�е�ĳ������Ԫ�ص�����
int GetElem(SqList L, int i, Bookcls &e)
{
	if (i < 1 || i > L.length)
	{
		return -1;
	}
	//�ж� i ֵ�Ƿ����������������-1
	e = L.elem[i - 1]; //�� i-1 �洢�ŵ� i ������
	return 0;
}



//�����Ա�L�е�i��Ԫ��֮ǰ��������Ԫ��e
int ListInsert_Sq(SqList &L, int i, Bookcls e)
{
	int j;
	if (i<1 || i > L.length + 1)
	{
		return -1; // i ֵ���Ϸ�
	}
	if (L.length == MAXSIZE)
	{
		return -1; //��ǰ�洢�ռ�������
	}
	for (j = L.length - 1; j >= i - 1; j--)
	{
		L.elem[j + 1] = L.elem[j]; //����λ�ü�֮���Ԫ�غ���
		L.elem[i - 1] = e; //����Ԫ�� e ����� i ��λ��
		++L.length; //����1
		return 0;
	}
}


//�����Ա� L �е� i ��Ԫ��ɾ��
int ListDelete_Sq(SqList &L, int i)
{
	if ((i<1) || (i > L.length))
	{
		return -1;  // i ֵ���Ϸ�
	}
	for (int j = i+1; j <= L.length - 1; j++)
	{
		L.elem[j].BookNo -= 1;
		L.elem[j - 1] = L.elem[j]; //��ɾ��Ԫ��֮���Ԫ��ǰ��
	}
	--L.length; //���� 1
	return 0;
}