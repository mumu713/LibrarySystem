#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <map>
#include "SqList.h"
#define bookData "bookData.txt"


using namespace std;

void bookAdd();			//图书增加 
void bookModify();		//图书采编入库
void bookFind();		//图书查询 
void bookDel();			//图书删除 

extern void print_bookAdmin_menu();//打印图书管理菜单 

void SplitString(const string& s, vector<string>& v, const string& c);//字符串分割


//定义全局的线性表
static SqList allbook;

//判断图书信息是否缺失，获取数据
SqList GetallData()
{
	SqList allbook;
	InitList_Sq(&allbook);//初始化线性表

	string temp;
	ifstream infile;
	infile.open(bookData);
	
	if (infile.eof())//到达文件底部
	{
		infile.close();
		return allbook;
	}

	int i = 0;
	while (getline(infile, temp))
	{
		vector<string> data;
		SplitString(temp, data, ",");
		if (data.size() == 5)
		{
			allbook.elem[i].BookNo = stoi(data[0]);
			allbook.elem[i].BookName = data[1];
			allbook.elem[i].BookAuthor = data[2];
			allbook.elem[i].ExistNumber = stoi(data[3]);
			allbook.elem[i].AllNumber = stoi(data[4]);
			i++;
			allbook.length++;
		}
		else if(data.size() > 0 && data.size()< 5)
		{
			cout << "存在书籍缺少信息，请检查书籍信息存储文本文件！" << endl;
			return allbook;
		}

	}
	infile.close();

	return allbook;

}

//分割字符串 并存入向量中
void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)//存在
    {
        v.push_back(s.substr(pos1, pos2-pos1));
         
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())//末尾
        v.push_back(s.substr(pos1));
}



void bookAdmin_process()//图书信息管理流程
{
	if (allbook.length == 0)
	{
		allbook = GetallData();
	}

	char n;
	cin >> n;
	system("cls");
	switch (n)
	{
	case '1':
		bookAdd();
		break;
	case '2':
		bookModify();
		break;
	case '3':
		bookFind();
		break;
	case '4':
		bookDel();
		break;
	case 'q':
		return;
	default:cout << "提示：无效的输入！\n请输入相应的序号并按回车，输入q返回" << endl;
	}
	print_bookAdmin_menu();
	bookAdmin_process();
}


//录入
void bookAdd()
{


	Bookcls BookInput;
	//图书名称、作者、库存量
	string bookName,bookAuthor;
	int AllNumber;

	if (allbook.length == 0)
	{
		cout << "目前图书数量为： 0" << endl;
	}
	else {
		cout << "目前图书数量为： " << allbook.length << endl;
		cout << setw(20) << "图书编号" << setw(20) << "图书名称" << setw(10) << "图书作者" << setw(30) << "图书当前库存" << setw(30) << "图书库存总量" << endl;
		for (int i = 0; i < allbook.length; i++)
		{
					cout << setw(20) << allbook.elem[i].BookNo << setw(20) << allbook.elem[i].BookName << setw(10) << allbook.elem[i].BookAuthor << setw(30) << allbook.elem[i].ExistNumber << setw(30) << allbook.elem[i].AllNumber << endl;
		}
	}
	cout<<"请输入图书名称：";
	cin>>bookName;
	cout<<"请输入作者：";
	cin>>bookAuthor;
	cout << "请输入库存(数字)：";
	cin >> AllNumber;

	if (allbook.length == 0)
	{
		BookInput.BookNo = allbook.length;
	}
	else
	{
		BookInput.BookNo = allbook.elem[allbook.length - 1].BookNo + 1;
	}
	BookInput.AllNumber = AllNumber;
	BookInput.BookAuthor = bookAuthor;
	BookInput.BookName = bookName;
	BookInput.ExistNumber = BookInput.AllNumber;

	if (Check(allbook, BookInput) == 0)//
	{
		allbook.elem[allbook.length] = BookInput;
		allbook.length++;
		cout << "新增数据成功" << endl;

		//更新到本地文件夹
		AddText(BookInput);
		return;
	}
	else if (Check(allbook, BookInput) == -1)//
	{
		cout << "输入为空！" << endl;
		return;
	}
	else if (Check(allbook, BookInput) == -2)//
	{
		cout << "录入图书书名与作者与库存重复，录入失败！若为增加库存请在采编入库中添加" << endl;
		return;
	}

}

//采编入库
void bookModify(){

	if (allbook.length == 0)
	{
		cout << "目前图书数量为： 0" << endl;
	}
	else {
		cout << "目前图书数量为： " << allbook.length << endl;
		cout << setw(20) << "图书编号" << setw(20) << "图书名称" << setw(10) << "图书作者" << setw(30) << "图书当前库存" << setw(30) << "图书库存总量" << endl;
		for (int i = 0; i < allbook.length; i++)
		{
			cout << setw(20) << allbook.elem[i].BookNo << setw(20) << allbook.elem[i].BookName << setw(10) << allbook.elem[i].BookAuthor << setw(30) << allbook.elem[i].ExistNumber << setw(30) << allbook.elem[i].AllNumber << endl;
		}
	}

	int bookNo_in,number;
	cout<<"请输入图书编号:"; 
	cin>> bookNo_in;
	if (bookNo_in<0 || bookNo_in>allbook.length - 1)
	{
		cout << "输入的图书编号错误！" << endl;
		cout << "已返回！" << endl;
		return;
	}

	cout << "请输入新入库数量:";
	cin >> number;
	if(number < 0){
		cout << "输入的入库数量错误！" << endl;
		cout << "已返回！" << endl;
		return;
	}

	allbook.elem[bookNo_in].AllNumber += number;
	allbook.elem[bookNo_in].ExistNumber += number;

	cout << "修改后信息为：" << endl;
	cout << setw(20) << allbook.elem[bookNo_in].BookNo << setw(20) << allbook.elem[bookNo_in].BookName << setw(10) << allbook.elem[bookNo_in].BookAuthor << setw(30) << allbook.elem[bookNo_in].ExistNumber << setw(30) << allbook.elem[bookNo_in].AllNumber << endl;

	fstream fout(bookData, ios::out | ios::trunc);
	for (int j = 0; j < allbook.length; j++)
	{
		string data = to_string(allbook.elem[j].BookNo) + "," + allbook.elem[j].BookName + ","
			+ allbook.elem[j].BookAuthor + "," + to_string(allbook.elem[j].ExistNumber) + "," +
			to_string(allbook.elem[j].AllNumber);
		fout << data << endl;
	}
	fout.close();
	return;
}
//查询
void bookFind()
{

	vector<string> booknamevec;
	if (allbook.length == 0)
	{
		cout << "目前图书数量为： 0 ,无法查询" << endl;
	}
	else {
		for (int i = 0; i < allbook.length; i++)
		{
			booknamevec.push_back(allbook.elem[i].BookName);
			booknamevec.push_back(to_string(allbook.elem[i].BookNo));
		}
	}

	cout<<"请输入图书编号或图书名称进行查询："; 
	string findStr;
	cin>>findStr;


	bool findFlag=true;

	for (int i = 0; i < booknamevec.size(); i++) 
	{
		if (booknamevec[i].find(findStr) != string::npos )
		{
			if ((i+1) % 2 == 0)
			{
				cout << "图书编号：" << allbook.elem[stoi(booknamevec[i])].BookNo << endl;
				cout << "图书名称：" << allbook.elem[stoi(booknamevec[i])].BookName << endl;
				cout << "图书作者：" << allbook.elem[stoi(booknamevec[i])].BookAuthor << endl;
				cout << "图书当前库存：" << allbook.elem[stoi(booknamevec[i])].ExistNumber << endl;
				cout << "存在库存总量：" << allbook.elem[stoi(booknamevec[i])].AllNumber << endl;
				cout << "---------------------------------------" << endl;
			}
			else
			{
				cout << "图书编号：" << allbook.elem[stoi(booknamevec[i + 1])].BookNo << endl;
				cout << "图书名称：" << allbook.elem[stoi(booknamevec[i + 1])].BookName << endl;
				cout << "图书作者：" << allbook.elem[stoi(booknamevec[i + 1])].BookAuthor << endl;
				cout << "图书当前库存：" << allbook.elem[stoi(booknamevec[i + 1])].ExistNumber << endl;
				cout << "存在库存总量：" << allbook.elem[stoi(booknamevec[i + 1])].AllNumber << endl;
				cout << "---------------------------------------" << endl;
			}
			findFlag = false;
		}

	}
    if(findFlag){
    	cout<<"抱歉，没有找到相关图书信息！"<<endl;
	}
} 
//删除
void bookDel()
{

	if (allbook.length == 0)
	{
		cout << "目前图书数量为： 0" << endl;
	}
	else {
		cout << "目前图书数量为： " << allbook.length << endl;
		cout << setw(20) << "图书编号" << setw(20) << "图书名称" << setw(10) << "图书作者" << setw(30) << "图书当前库存" << setw(30) << "图书库存总量" << endl;
		for (int i = 0; i < allbook.length; i++)
		{
			cout << setw(20) << allbook.elem[i].BookNo << setw(20) << allbook.elem[i].BookName << setw(10) << allbook.elem[i].BookAuthor << setw(30) << allbook.elem[i].ExistNumber << setw(30) << allbook.elem[i].AllNumber << endl;
		}
	}

	int bookNo_in;
	cout << "请输入图书编号:";
	cin >> bookNo_in;

	if (bookNo_in<0 || bookNo_in>allbook.length - 1)
	{
		cout << "输入的图书编号错误！" << endl;
		cout << "已返回！" << endl;
		return;
	}

	cout << "请确认删除图书信息：" << endl;
	cout << setw(20) << allbook.elem[bookNo_in].BookNo << setw(20) << allbook.elem[bookNo_in].BookName << setw(10) << allbook.elem[bookNo_in].BookAuthor << setw(30) << allbook.elem[bookNo_in].ExistNumber << setw(30) << allbook.elem[bookNo_in].AllNumber << endl;
	
	
	string flg;

	cout << "确认删除请输入：Y " << endl;
	cin >> flg;

	if (flg == "Y" || flg == "y")
	{
		ListDelete_Sq(allbook, bookNo_in);

		//更新到文本
		fstream fout(bookData, ios::out | ios::trunc);
		for (int j = 0; j < allbook.length; j++)
		{
			string data = to_string(allbook.elem[j].BookNo) + "," + allbook.elem[j].BookName + "," + allbook.elem[j].BookAuthor + "," + to_string(allbook.elem[j].ExistNumber) + "," + to_string(allbook.elem[j].AllNumber);
			fout << data << endl;
		}
		fout.close();

		cout<<"已成功删除以上图书,并更新图书信息！"<<endl;

		if (allbook.length == 0)
		{
			cout << "目前图书数量为： 0" << endl;
		}
		else {
			cout << "目前图书数量为： " << allbook.length << endl;
			cout << setw(20) << "图书编号" << setw(20) << "图书名称" << setw(10) << "图书作者" << setw(30) << "图书当前库存" << setw(30) << "图书库存总量" << endl;
			for (int i = 0; i < allbook.length; i++)
			{
				cout << setw(20) << allbook.elem[i].BookNo << setw(20) << allbook.elem[i].BookName << setw(10) << allbook.elem[i].BookAuthor << setw(30) << allbook.elem[i].ExistNumber << setw(30) << allbook.elem[i].AllNumber << endl;
			}
		}
	}
	else {
		cout << "确认错误，删除失败！" << endl;
		cout << "已返回！" << endl;
		return;
	}

	
} 
