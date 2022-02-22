#include<iostream>
#include<windows.h>
#include<stdlib.h>
using namespace std;


extern void print_main_menu();	   //打印主菜单 
extern void print_bookAdmin_menu();//打印图书管理菜单 
extern void bookAdmin_process();   //图书管理流程 
extern void print_borrowAndReturn_menu(); //打印借还管理菜单
extern void borrowAndReturnAdmin_process();//借还管理流程 


void mainProcess()
{	//程序流程控制 
	//打印菜单 
	print_main_menu(); //主页面
	char n;
	cin>>n;
	Sleep(500);
	system("cls");
	switch(n)
	{
		case '1':
			print_bookAdmin_menu();//打印图书管理菜单
			bookAdmin_process();//图书管理流程
			break;
		case '2':
			print_borrowAndReturn_menu();//打印借还管理菜单
			borrowAndReturnAdmin_process();//借还管理流程
			break;
		case 'q':
			return;
		default:cout<<"提示：无效的输入！\n请输入相应的序号并按回车，输入q退出程序"<<endl;
	}
	mainProcess();	
} 
int main(int argc, char** argv) 
{
	mainProcess();
	return 0;
}

