#include<iostream>
#include<windows.h>
#include<stdlib.h>
using namespace std;


extern void print_main_menu();	   //��ӡ���˵� 
extern void print_bookAdmin_menu();//��ӡͼ�����˵� 
extern void bookAdmin_process();   //ͼ��������� 
extern void print_borrowAndReturn_menu(); //��ӡ�軹����˵�
extern void borrowAndReturnAdmin_process();//�軹�������� 


void mainProcess()
{	//�������̿��� 
	//��ӡ�˵� 
	print_main_menu(); //��ҳ��
	char n;
	cin>>n;
	Sleep(500);
	system("cls");
	switch(n)
	{
		case '1':
			print_bookAdmin_menu();//��ӡͼ�����˵�
			bookAdmin_process();//ͼ���������
			break;
		case '2':
			print_borrowAndReturn_menu();//��ӡ�軹����˵�
			borrowAndReturnAdmin_process();//�軹��������
			break;
		case 'q':
			return;
		default:cout<<"��ʾ����Ч�����룡\n��������Ӧ����Ų����س�������q�˳�����"<<endl;
	}
	mainProcess();	
} 
int main(int argc, char** argv) 
{
	mainProcess();
	return 0;
}

