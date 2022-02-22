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
extern void SplitString(const string& s, vector<string>& v, const string& c);//�ָ��ַ�����������������
extern void print_borrowAndReturn_menu();//��ӡ�軹����˵�
void borrowerAdmin();//����
void returnAdmin(); //����
void borrowAndReturnShow();//��ʾ
extern SqList GetallData();//��ȡ����

vector<string> GetborrowData() //�ж��ļ��Ƿ�ȱʧ
{
	vector<string> brrowvec;//����
	string temp;
	ifstream infile;//�����ļ���
	infile.open(borrowerandreturnData);

	if (infile.eof())//�����ļ��ײ�
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
			cout << "������Ϣ����ȱʧ�����������Ϣ�洢�ı��ļ���" << endl;
			return brrowvec;
		}

	}
	infile.close();

	return brrowvec;

}

SqList Ballbook;
void borrowAndReturnAdmin_process()//�軹��������
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
		borrowerAdmin();//��������
		break;
	case '2':
		returnAdmin();//��������
		break;
	case '3':
		borrowAndReturnShow();//��ʾ
		break;
	case 'q':
		return;
	default:cout << "��ʾ����Ч�����룡\n��������Ӧ����Ų����س�������q����" << endl;
	}
	print_borrowAndReturn_menu();//�軹�˵�
	borrowAndReturnAdmin_process();//�軹����
}


void borrowerAdmin()//��������
{
	string userNo,borrowerTime,returnTime="NULL";//������֤�� ,����ʱ�䣬����ʱ��
	int bookNo_in;
	if (Ballbook.length == 0)
	{
		cout << "Ŀǰͼ������Ϊ�� 0" << endl;
	}
	else
	{
		cout << "Ŀǰͼ������Ϊ�� " << Ballbook.length << endl;
		cout << setw(20) << "ͼ����" << setw(20) << "ͼ������" << setw(10) << "ͼ������" << setw(20)
			<< "ͼ�鵱ǰ���" << setw(10) << "ͼ��������" << endl;
		for (int i = 0; i < Ballbook.length; i++)
		{
			cout << setw(20) << Ballbook.elem[i].BookNo << setw(20) << Ballbook.elem[i].BookName 
				<< setw(10) << Ballbook.elem[i].BookAuthor << setw(20) << Ballbook.elem[i].ExistNumber
				<< setw(10) << Ballbook.elem[i].AllNumber << endl;//��ţ����������ߣ��ִ����������
		}
	}

	cout<<"�����ڰ�����������������ʱ��1����"<<endl; 
	cout<<"��������ĵ���֤�ţ�";
	cin>>userNo;
	cout<<"������ͼ���ţ�";
	cin>> bookNo_in;

	if (bookNo_in<0 || bookNo_in>Ballbook.length - 1)
	{
		cout << "�����ͼ���Ŵ���" << endl;
		cout << "�ѷ��أ�" << endl;
		return;
	}
	if (Ballbook.elem[bookNo_in].ExistNumber == 0)
	{
		cout << "��������ȫ�������" << endl;
		cout << "�ѷ��أ�" << endl;
		return;
	}

	//��ȡʱ�� 
	SYSTEMTIME m_time; //��ȡϵͳ��ǰʱ��
	GetLocalTime(&m_time);
	char szDateTime[100] = {0};//����ʱ��
	char reDateTime[100] = { 0 };//����ʱ��
	sprintf_s(szDateTime, "%02d-%02d-%02d %02d:%02d:%02d", m_time.wYear, m_time.wMonth,m_time.wDay, m_time.wHour,
		m_time.wMinute, m_time.wSecond);//ƴ���ַ���
	//Ĭ�������ʱ��1��
	if (m_time.wMonth == 12)//12�½��飬����һ�·ݻ���
	{
		sprintf_s(reDateTime, "%02d-%02d-%02d %02d:%02d:%02d", m_time.wYear+1, m_time.wMonth-11, m_time.wDay,
			m_time.wHour, m_time.wMinute, m_time.wSecond);
	}
	else //����������·ݼ�һ
	{
		sprintf_s(reDateTime, "%02d-%02d-%02d %02d:%02d:%02d", m_time.wYear, m_time.wMonth+1, m_time.wDay,
			m_time.wHour, m_time.wMinute, m_time.wSecond);
	}

	string brtime(szDateTime);
	string retime(reDateTime);
	borrowerTime= brtime;
	returnTime = retime;

	//����book���� 
	Ballbook.elem[bookNo_in].ExistNumber -= 1;
	//������ͼ����Ϣ�ı�
	fstream fout(bookData, ios::out | ios::trunc);
	for (int j = 0; j < Ballbook.length; j++)
	{
		string data = to_string(Ballbook.elem[j].BookNo) + "," + Ballbook.elem[j].BookName + "," 
			+ Ballbook.elem[j].BookAuthor + "," + to_string(Ballbook.elem[j].ExistNumber) + "," + to_string(Ballbook.elem[j].AllNumber);
		fout << data << endl;
	}
	fout.close();
	

	//���������黹���ı���
	fstream brrowfile;
	brrowfile.open(borrowerandreturnData, ios::app | ios::out);
	string data = userNo + "," + to_string(bookNo_in) + "," + borrowerTime + "," + returnTime ;
	brrowfile << data << endl;
	brrowfile.close();

	cout<<"�����ˣ�"<<userNo<<"���ĳɹ��� "<<"����ͼ���ţ�"<< bookNo_in <<endl;
    cout << "Ŀǰͼ������Ϊ�� " << Ballbook.length << endl;
	cout << setw(20) << "ͼ����" << setw(20) << "ͼ������" << setw(10) << "ͼ������" << setw(20)
		<< "ͼ�鵱ǰ���" << setw(10) << "ͼ��������" << endl;
	for (int i = 0; i < Ballbook.length; i++)
	{
		cout << setw(20) << Ballbook.elem[i].BookNo << setw(20) << Ballbook.elem[i].BookName
			<< setw(10) << Ballbook.elem[i].BookAuthor << setw(20) << Ballbook.elem[i].ExistNumber
			<< setw(10) << Ballbook.elem[i].AllNumber << endl;//��ţ����������ߣ��ִ����������
	}

}


//��������
void returnAdmin()
{

	if (Ballbook.length == 0)
	{
		cout << "Ŀǰͼ������Ϊ�� 0" << endl;
	}
	else {
		cout << "Ŀǰͼ������Ϊ�� " << Ballbook.length << endl;
		cout << setw(20) << "ͼ����" << setw(20) << "ͼ������" << setw(10) << "ͼ������" << setw(30) << "ͼ�鵱ǰ���"
			<< setw(30) << "ͼ��������" << endl;
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
		cout << "��ǰ�޽�����Ϣ��" << endl;
		cout << "�ѷ��أ�" << endl;
		return;
	}
	else
	{
		cout << "Ŀǰ������Ϣ��" << endl;
		for (int i = 0; i < borrowData.size(); i = i + 4)
		{
			cout << setw(10) << "��֤��" << setw(15) << "ͼ����" << setw(30) << "����ʱ��" << setw(30) << "�涨����ʱ��" << endl;
			cout << setw(10) << borrowData[i] << setw(15) << borrowData[i + 1] << setw(30) << borrowData[i + 2] 
				<< setw(30) << borrowData[i + 3] << endl;
		}
	}

	string userNo,returnTime;
	int bookNo_in;
	cout<<"�����ڰ���������"<<endl; 
	cout << "��������ĵ���֤�ţ�";
	cin >> userNo;
	cout << "������ͼ���ţ�";
	cin >> bookNo_in;

	//�ж�����Ľ�����Ϣ�Ƿ����
	int f = 0;
	for (int i = 0; i < borrowData.size(); i=i+4)
	{
		if (borrowData[i] == userNo && borrowData[i + 1] == to_string(bookNo_in))
		{
			borrowData.erase(borrowData.begin() + i, borrowData.begin() + i + 4);/////////?
			f = 1;
		}
	}
	//��������
	if (f == 0)
	{
		cout << "�Ҳ���������Ϣ����������ȷ��Ϣ�� " << endl;
		cout << "�ѷ��أ�" << endl;
		return;
	}
	//������
	else
	{
		//���������黹���ı�
		fstream fout(borrowerandreturnData, ios::out | ios::trunc);
		for (int j = 0; j < borrowData.size(); j=j+4)
		{
			string data = borrowData[j] + "," + borrowData[j+1] + "," + borrowData[j+2] + "," + borrowData[j+3] ;
			fout << data << endl;
		}
		fout.close();

		//����book����
		Ballbook.elem[bookNo_in].ExistNumber += 1;
		//������ͼ����Ϣ�ı�
		fstream bookfout(bookData, ios::out | ios::trunc);
		for (int j = 0; j < Ballbook.length; j++)
		{
			string data = to_string(Ballbook.elem[j].BookNo) + "," + Ballbook.elem[j].BookName + "," + 
				Ballbook.elem[j].BookAuthor + "," + to_string(Ballbook.elem[j].ExistNumber) + "," + 
				to_string(Ballbook.elem[j].AllNumber);
			bookfout << data << endl;
		}
		bookfout.close();


		cout << "�����������ɹ��������������Ϣ�� " << endl;
		cout << "�ѷ��أ�" << endl;
		return;
	}

}
//��ʾ�軹��Ϣ
void borrowAndReturnShow()
{

	vector<string> borrowData;
	borrowData = GetborrowData();

	if (borrowData.size() == 0)
	{
		cout << "��ǰ�޽�����Ϣ��" << endl;
		cout << "�ѷ��أ�" << endl;
		return;
	}
	else
	{
		for (int i = 0; i < borrowData.size(); i=i+4)
		{
			cout << setw(10) << "��֤��" << setw(15) << "ͼ����" << setw(30) << "����ʱ��" << setw(30) << "�涨����ʱ��" << endl;
			cout << setw(10) << borrowData[i] << setw(15) << borrowData[i+1] << setw(30) << borrowData[i+2] << setw(30) << borrowData[i+3] << endl;
		}
	}

} 

