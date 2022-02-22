#include "SqList.h"


//初始化线性表
//参数用引用
int InitList_Sq(SqList &L) //构造一个空的顺序表L
{
	L.elem = new Bookcls[MAXSIZE]; //为顺序表分配空间
	if (!L.elem)
	{
		exit(OVERFLOW); //存储分配失败
	}
	L.length = 0;
	return 0;
}


//初始化线性表
//参数用指针
int InitList_Sq(SqList *L) //构造一个空的顺序表L
{
	L->elem = new Bookcls[MAXSIZE]; //为顺序表分配空间
	if (!L->elem)
	{
		exit(OVERFLOW); //存储空间分配失败
	}
	L->length = 0;
	return 0;
}


//销毁线性表L
void DestroyList(SqList &L)
{
	if (L.elem)
	{
		delete[] L.elem; //释放存储空间
	}
}

//清空线性表L
void ClearList(SqList &L)
{
	L.length = 0; //将线性表的长度置为 0
}


//判断线性表L的长度
int GetLength(SqList L)
{
	return (L.length);
}


//判断线性表L是否为空
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


//判断是否重复
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


//添加到本地文件夹
void AddText(Bookcls book)
{
	fstream file1;
	file1.open(bookData, ios::app | ios::out);
	string data = to_string(book.BookNo) + "," + book.BookName + "," + book.BookAuthor + "," + to_string(book.ExistNumber) + "," + to_string(book.AllNumber);
	file1 << data << endl;
	file1.close();
}



//取值（根据位置 i 获取相应位置数据元素的内容）
//获取线性表L中的某个数据元素的内容
int GetElem(SqList L, int i, Bookcls &e)
{
	if (i < 1 || i > L.length)
	{
		return -1;
	}
	//判断 i 值是否合理，若不合理，返回-1
	e = L.elem[i - 1]; //第 i-1 存储着第 i 个数据
	return 0;
}



//在线性表L中第i个元素之前插入数据元素e
int ListInsert_Sq(SqList &L, int i, Bookcls e)
{
	int j;
	if (i<1 || i > L.length + 1)
	{
		return -1; // i 值不合法
	}
	if (L.length == MAXSIZE)
	{
		return -1; //当前存储空间已满。
	}
	for (j = L.length - 1; j >= i - 1; j--)
	{
		L.elem[j + 1] = L.elem[j]; //插入位置及之后的元素后移
		L.elem[i - 1] = e; //将新元素 e 放入第 i 个位置
		++L.length; //表长增1
		return 0;
	}
}


//将线性表 L 中第 i 个元素删除
int ListDelete_Sq(SqList &L, int i)
{
	if ((i<1) || (i > L.length))
	{
		return -1;  // i 值不合法
	}
	for (int j = i+1; j <= L.length - 1; j++)
	{
		L.elem[j].BookNo -= 1;
		L.elem[j - 1] = L.elem[j]; //被删除元素之后的元素前移
	}
	--L.length; //表长减 1
	return 0;
}