#include<iostream>
#include<windows.h>
#include<vector>
#include<iomanip>
#include<fstream>
#include<string>
#include "SqList.h"

#define bookData "bookData.txt"
#define borrowerandreturnData "borrowerandreturnData.txt"
using namespace std;
extern void SplitString(const string& s, vector<string>& v, const string& c);//分割字符串，并存入向量中
extern void print_borrowAndReturn_menu();//打印借还管理菜单
void borrowerAdmin();//借书
void returnAdmin(); //还书
void borrowAndReturnShow();//显示
extern SqList GetallData();//获取数据

vector<string> GetborrowData() //判断文件是否缺失
{
	vector<string> brrowvec;//向量
	string temp;
	ifstream infile;//输入文件流
	infile.open(borrowerandreturnData);

	if (infile.eof())//到达文件底部
	{
		infile.close();
		return brrowvec;
	}

	while (getline(infile, temp))
	{
		vector<string> data;
		SplitString(temp, data, ",");
		if (data.size() == 4)
		{
			brrowvec.push_back(data[0]);
			brrowvec.push_back(data[1]);
			brrowvec.push_back(data[2]);
			brrowvec.push_back(data[3]);
		}
		else if (data.size() > 0 && data.size()< 4)
		{
			cout << "借阅信息存在缺失，请检查借阅信息存储文本文件！" << endl;
			return brrowvec;
		}

	}
	infile.close();

	return brrowvec;

}

SqList Ballbook;
void borrowAndReturnAdmin_process()//借还管理流程
{
	
	if (Ballbook.length == 0)
	{
		Ballbook = GetallData();//?
	}

	char n;
	cin >> n;
	system("cls");
	switch (n)
	{
	case '1':
		borrowerAdmin();//借书手续
		break;
	case '2':
		returnAdmin();//还书手续
		break;
	case '3':
		borrowAndReturnShow();//显示
		break;
	case 'q':
		return;
	default:cout << "提示：无效的输入！\n请输入相应的序号并按回车，输入q返回" << endl;
	}
	print_borrowAndReturn_menu();//借还菜单
	borrowAndReturnAdmin_process();//借还流程
}


void borrowerAdmin()//借书手续
{
	string userNo,borrowerTime,returnTime="NULL";//借阅书证号 ,借书时间，还书时间
	int bookNo_in;
	if (Ballbook.length == 0)
	{
		cout << "目前图书数量为： 0" << endl;
	}
	else
	{
		cout << "目前图书数量为： " << Ballbook.length << endl;
		cout << setw(20) << "图书编号" << setw(20) << "图书名称" << setw(10) << "图书作者" << setw(20)
			<< "图书当前库存" << setw(10) << "图书库存总量" << endl;
		for (int i = 0; i < Ballbook.length; i++)
		{
			cout << setw(20) << Ballbook.elem[i].BookNo << setw(20) << Ballbook.elem[i].BookName 
				<< setw(10) << Ballbook.elem[i].BookAuthor << setw(20) << Ballbook.elem[i].ExistNumber
				<< setw(10) << Ballbook.elem[i].AllNumber << endl;//书号，书名，作者，现存量，库存量
		}
	}

	cout<<"您正在办理借阅手续，最长借书时间1个月"<<endl; 
	cout<<"请输入借阅的书证号：";
	cin>>userNo;
	cout<<"请输入图书编号：";
	cin>> bookNo_in;

	if (bookNo_in<0 || bookNo_in>Ballbook.length - 1)
	{
		cout << "输入的图书编号错误！" << endl;
		cout << "已返回！" << endl;
		return;
	}
	if (Ballbook.elem[bookNo_in].ExistNumber == 0)
	{
		cout << "该书现已全部借出！" << endl;
		cout << "已返回！" << endl;
		return;
	}

	//获取时间 
	SYSTEMTIME m_time; //获取系统当前时间
	GetLocalTime(&m_time);
	char szDateTime[100] = {0};//借书时间
	char reDateTime[100] = { 0 };//还书时间
	sprintf_s(szDateTime, "%02d-%02d-%02d %02d:%02d:%02d", m_time.wYear, m_time.wMonth,m_time.wDay, m_time.wHour,
		m_time.wMinute, m_time.wSecond);//拼接字符串
	//默认最长借书时间1月
	if (m_time.wMonth == 12)//12月借书，次年一月份还书
	{
		sprintf_s(reDateTime, "%02d-%02d-%02d %02d:%02d:%02d", m_time.wYear+1, m_time.wMonth-11, m_time.wDay,
			m_time.wHour, m_time.wMinute, m_time.wSecond);
	}
	else //其余情况，月份加一
	{
		sprintf_s(reDateTime, "%02d-%02d-%02d %02d:%02d:%02d", m_time.wYear, m_time.wMonth+1, m_time.wDay,
			m_time.wHour, m_time.wMinute, m_time.wSecond);
	}

	string brtime(szDateTime);
	string retime(reDateTime);
	borrowerTime= brtime;
	returnTime = retime;

	//更新book数据 
	Ballbook.elem[bookNo_in].ExistNumber -= 1;
	//更新致图书信息文本
	fstream fout(bookData, ios::out | ios::trunc);
	for (int j = 0; j < Ballbook.length; j++)
	{
		string data = to_string(Ballbook.elem[j].BookNo) + "," + Ballbook.elem[j].BookName + "," 
			+ Ballbook.elem[j].BookAuthor + "," + to_string(Ballbook.elem[j].ExistNumber) + "," + to_string(Ballbook.elem[j].AllNumber);
		fout << data << endl;
	}
	fout.close();
	

	//更新至借书还书文本中
	fstream brrowfile;
	brrowfile.open(borrowerandreturnData, ios::app | ios::out);
	string data = userNo + "," + to_string(bookNo_in) + "," + borrowerTime + "," + returnTime ;
	brrowfile << data << endl;
	brrowfile.close();

	cout<<"借书人："<<userNo<<"借阅成功！ "<<"借阅图书编号："<< bookNo_in <<endl;
    cout << "目前图书数量为： " << Ballbook.length << endl;
	cout << setw(20) << "图书编号" << setw(20) << "图书名称" << setw(10) << "图书作者" << setw(20)
		<< "图书当前库存" << setw(10) << "图书库存总量" << endl;
	for (int i = 0; i < Ballbook.length; i++)
	{
		cout << setw(20) << Ballbook.elem[i].BookNo << setw(20) << Ballbook.elem[i].BookName
			<< setw(10) << Ballbook.elem[i].BookAuthor << setw(20) << Ballbook.elem[i].ExistNumber
			<< setw(10) << Ballbook.elem[i].AllNumber << endl;//书号，书名，作者，现存量，库存量
	}

}


//还书手续
void returnAdmin()
{

	if (Ballbook.length == 0)
	{
		cout << "目前图书数量为： 0" << endl;
	}
	else {
		cout << "目前图书数量为： " << Ballbook.length << endl;
		cout << setw(20) << "图书编号" << setw(20) << "图书名称" << setw(10) << "图书作者" << setw(30) << "图书当前库存"
			<< setw(30) << "图书库存总量" << endl;
		for (int i = 0; i < Ballbook.length; i++)
		{
			cout << setw(20) << Ballbook.elem[i].BookNo << setw(20) << Ballbook.elem[i].BookName 
				<< setw(10) << Ballbook.elem[i].BookAuthor << setw(30) << Ballbook.elem[i].ExistNumber 
				<< setw(30) << Ballbook.elem[i].AllNumber << endl;
		}
	}
	vector<string> borrowData;
	borrowData = GetborrowData();
	if (borrowData.size() == 0)
	{
		cout << "当前无借阅信息！" << endl;
		cout << "已返回！" << endl;
		return;
	}
	else
	{
		cout << "目前借阅信息：" << endl;
		for (int i = 0; i < borrowData.size(); i = i + 4)
		{
			cout << setw(10) << "书证号" << setw(15) << "图书编号" << setw(30) << "借书时间" << setw(30) << "规定还书时间" << endl;
			cout << setw(10) << borrowData[i] << setw(15) << borrowData[i + 1] << setw(30) << borrowData[i + 2] 
				<< setw(30) << borrowData[i + 3] << endl;
		}
	}

	string userNo,returnTime;
	int bookNo_in;
	cout<<"您正在办理还书手续"<<endl; 
	cout << "请输入借阅的书证号：";
	cin >> userNo;
	cout << "请输入图书编号：";
	cin >> bookNo_in;

	//判断输入的借书信息是否存在
	int f = 0;
	for (int i = 0; i < borrowData.size(); i=i+4)
	{
		if (borrowData[i] == userNo && borrowData[i + 1] == to_string(bookNo_in))
		{
			borrowData.erase(borrowData.begin() + i, borrowData.begin() + i + 4);/////////?
			f = 1;
		}
	}
	//若不存在
	if (f == 0)
	{
		cout << "找不到借阅信息，请输入正确信息！ " << endl;
		cout << "已返回！" << endl;
		return;
	}
	//若存在
	else
	{
		//更新至借书还书文本
		fstream fout(borrowerandreturnData, ios::out | ios::trunc);
		for (int j = 0; j < borrowData.size(); j=j+4)
		{
			string data = borrowData[j] + "," + borrowData[j+1] + "," + borrowData[j+2] + "," + borrowData[j+3] ;
			fout << data << endl;
		}
		fout.close();

		//更新book数据
		Ballbook.elem[bookNo_in].ExistNumber += 1;
		//更新至图书信息文本
		fstream bookfout(bookData, ios::out | ios::trunc);
		for (int j = 0; j < Ballbook.length; j++)
		{
			string data = to_string(Ballbook.elem[j].BookNo) + "," + Ballbook.elem[j].BookName + "," + 
				Ballbook.elem[j].BookAuthor + "," + to_string(Ballbook.elem[j].ExistNumber) + "," + 
				to_string(Ballbook.elem[j].AllNumber);
			bookfout << data << endl;
		}
		bookfout.close();


		cout << "办理还书手续成功，已清除借阅信息！ " << endl;
		cout << "已返回！" << endl;
		return;
	}

}
//显示借还信息
void borrowAndReturnShow()
{

	vector<string> borrowData;
	borrowData = GetborrowData();

	if (borrowData.size() == 0)
	{
		cout << "当前无借阅信息！" << endl;
		cout << "已返回！" << endl;
		return;
	}
	else
	{
		for (int i = 0; i < borrowData.size(); i=i+4)
		{
			cout << setw(10) << "书证号" << setw(15) << "图书编号" << setw(30) << "借书时间" << setw(30) << "规定还书时间" << endl;
			cout << setw(10) << borrowData[i] << setw(15) << borrowData[i+1] << setw(30) << borrowData[i+2] << setw(30) << borrowData[i+3] << endl;
		}
	}

} 

