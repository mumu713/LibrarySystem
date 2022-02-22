#include<iostream>
using namespace std;
void print_main_menu()//主菜单
{
	cout<<"=====图书管理系统====="<<endl; 
	cout<<"1、图书信息管理"<<endl;
	cout<<"2、图书借还管理"<<endl;
	cout<<"提示：请输入相应的序号并按回车，输入q返回"<<endl;
}
void print_bookAdmin_menu()//图书管理菜单
{
	cout<<"1、图书录入"<<endl;
	cout<<"2、图书采编入库"<<endl;
	cout<<"3、图书查询"<<endl; 
	cout<<"4、图书删除"<<endl;
	cout<<"提示：请输入相应的序号并按回车，输入q返回"<<endl;
}
void print_borrowAndReturn_menu()//借书菜单
{
	cout<<"1、办理借书手续"<<endl;
	cout<<"2、办理还书手续"<<endl;
	cout<<"3、显示借书信息"<<endl; 
	cout<<"提示：请输入相应的序号并按回车，输入q返回"<<endl;
} 