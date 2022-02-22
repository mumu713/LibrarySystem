#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <map>
#include "SqList.h"
#define bookData "bookData.txt"


using namespace std;

void bookAdd();			//ͼ������ 
void bookModify();		//ͼ��ɱ����
void bookFind();		//ͼ���ѯ 
void bookDel();			//ͼ��ɾ�� 

extern void print_bookAdmin_menu();//��ӡͼ�����˵� 

void SplitString(const string& s, vector<string>& v, const string& c);//�ַ����ָ�


//����ȫ�ֵ����Ա�
static SqList allbook;

//�ж�ͼ����Ϣ�Ƿ�ȱʧ����ȡ����
SqList GetallData()
{
	SqList allbook;
	InitList_Sq(&allbook);//��ʼ�����Ա�

	string temp;
	ifstream infile;
	infile.open(bookData);
	
	if (infile.eof())//�����ļ��ײ�
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
			cout << "�����鼮ȱ����Ϣ�������鼮��Ϣ�洢�ı��ļ���" << endl;
			return allbook;
		}

	}
	infile.close();

	return allbook;

}

//�ָ��ַ��� ������������
void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)//����
    {
        v.push_back(s.substr(pos1, pos2-pos1));
         
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())//ĩβ
        v.push_back(s.substr(pos1));
}



void bookAdmin_process()//ͼ����Ϣ��������
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
	default:cout << "��ʾ����Ч�����룡\n��������Ӧ����Ų����س�������q����" << endl;
	}
	print_bookAdmin_menu();
	bookAdmin_process();
}


//¼��
void bookAdd()
{


	Bookcls BookInput;
	//ͼ�����ơ����ߡ������
	string bookName,bookAuthor;
	int AllNumber;

	if (allbook.length == 0)
	{
		cout << "Ŀǰͼ������Ϊ�� 0" << endl;
	}
	else {
		cout << "Ŀǰͼ������Ϊ�� " << allbook.length << endl;
		cout << setw(20) << "ͼ����" << setw(20) << "ͼ������" << setw(10) << "ͼ������" << setw(30) << "ͼ�鵱ǰ���" << setw(30) << "ͼ��������" << endl;
		for (int i = 0; i < allbook.length; i++)
		{
					cout << setw(20) << allbook.elem[i].BookNo << setw(20) << allbook.elem[i].BookName << setw(10) << allbook.elem[i].BookAuthor << setw(30) << allbook.elem[i].ExistNumber << setw(30) << allbook.elem[i].AllNumber << endl;
		}
	}
	cout<<"������ͼ�����ƣ�";
	cin>>bookName;
	cout<<"���������ߣ�";
	cin>>bookAuthor;
	cout << "��������(����)��";
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
		cout << "�������ݳɹ�" << endl;

		//���µ������ļ���
		AddText(BookInput);
		return;
	}
	else if (Check(allbook, BookInput) == -1)//
	{
		cout << "����Ϊ�գ�" << endl;
		return;
	}
	else if (Check(allbook, BookInput) == -2)//
	{
		cout << "¼��ͼ�����������������ظ���¼��ʧ�ܣ���Ϊ���ӿ�����ڲɱ���������" << endl;
		return;
	}

}

//�ɱ����
void bookModify(){

	if (allbook.length == 0)
	{
		cout << "Ŀǰͼ������Ϊ�� 0" << endl;
	}
	else {
		cout << "Ŀǰͼ������Ϊ�� " << allbook.length << endl;
		cout << setw(20) << "ͼ����" << setw(20) << "ͼ������" << setw(10) << "ͼ������" << setw(30) << "ͼ�鵱ǰ���" << setw(30) << "ͼ��������" << endl;
		for (int i = 0; i < allbook.length; i++)
		{
			cout << setw(20) << allbook.elem[i].BookNo << setw(20) << allbook.elem[i].BookName << setw(10) << allbook.elem[i].BookAuthor << setw(30) << allbook.elem[i].ExistNumber << setw(30) << allbook.elem[i].AllNumber << endl;
		}
	}

	int bookNo_in,number;
	cout<<"������ͼ����:"; 
	cin>> bookNo_in;
	if (bookNo_in<0 || bookNo_in>allbook.length - 1)
	{
		cout << "�����ͼ���Ŵ���" << endl;
		cout << "�ѷ��أ�" << endl;
		return;
	}

	cout << "���������������:";
	cin >> number;
	if(number < 0){
		cout << "����������������" << endl;
		cout << "�ѷ��أ�" << endl;
		return;
	}

	allbook.elem[bookNo_in].AllNumber += number;
	allbook.elem[bookNo_in].ExistNumber += number;

	cout << "�޸ĺ���ϢΪ��" << endl;
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
//��ѯ
void bookFind()
{

	vector<string> booknamevec;
	if (allbook.length == 0)
	{
		cout << "Ŀǰͼ������Ϊ�� 0 ,�޷���ѯ" << endl;
	}
	else {
		for (int i = 0; i < allbook.length; i++)
		{
			booknamevec.push_back(allbook.elem[i].BookName);
			booknamevec.push_back(to_string(allbook.elem[i].BookNo));
		}
	}

	cout<<"������ͼ���Ż�ͼ�����ƽ��в�ѯ��"; 
	string findStr;
	cin>>findStr;


	bool findFlag=true;

	for (int i = 0; i < booknamevec.size(); i++) 
	{
		if (booknamevec[i].find(findStr) != string::npos )
		{
			if ((i+1) % 2 == 0)
			{
				cout << "ͼ���ţ�" << allbook.elem[stoi(booknamevec[i])].BookNo << endl;
				cout << "ͼ�����ƣ�" << allbook.elem[stoi(booknamevec[i])].BookName << endl;
				cout << "ͼ�����ߣ�" << allbook.elem[stoi(booknamevec[i])].BookAuthor << endl;
				cout << "ͼ�鵱ǰ��棺" << allbook.elem[stoi(booknamevec[i])].ExistNumber << endl;
				cout << "���ڿ��������" << allbook.elem[stoi(booknamevec[i])].AllNumber << endl;
				cout << "---------------------------------------" << endl;
			}
			else
			{
				cout << "ͼ���ţ�" << allbook.elem[stoi(booknamevec[i + 1])].BookNo << endl;
				cout << "ͼ�����ƣ�" << allbook.elem[stoi(booknamevec[i + 1])].BookName << endl;
				cout << "ͼ�����ߣ�" << allbook.elem[stoi(booknamevec[i + 1])].BookAuthor << endl;
				cout << "ͼ�鵱ǰ��棺" << allbook.elem[stoi(booknamevec[i + 1])].ExistNumber << endl;
				cout << "���ڿ��������" << allbook.elem[stoi(booknamevec[i + 1])].AllNumber << endl;
				cout << "---------------------------------------" << endl;
			}
			findFlag = false;
		}

	}
    if(findFlag){
    	cout<<"��Ǹ��û���ҵ����ͼ����Ϣ��"<<endl;
	}
} 
//ɾ��
void bookDel()
{

	if (allbook.length == 0)
	{
		cout << "Ŀǰͼ������Ϊ�� 0" << endl;
	}
	else {
		cout << "Ŀǰͼ������Ϊ�� " << allbook.length << endl;
		cout << setw(20) << "ͼ����" << setw(20) << "ͼ������" << setw(10) << "ͼ������" << setw(30) << "ͼ�鵱ǰ���" << setw(30) << "ͼ��������" << endl;
		for (int i = 0; i < allbook.length; i++)
		{
			cout << setw(20) << allbook.elem[i].BookNo << setw(20) << allbook.elem[i].BookName << setw(10) << allbook.elem[i].BookAuthor << setw(30) << allbook.elem[i].ExistNumber << setw(30) << allbook.elem[i].AllNumber << endl;
		}
	}

	int bookNo_in;
	cout << "������ͼ����:";
	cin >> bookNo_in;

	if (bookNo_in<0 || bookNo_in>allbook.length - 1)
	{
		cout << "�����ͼ���Ŵ���" << endl;
		cout << "�ѷ��أ�" << endl;
		return;
	}

	cout << "��ȷ��ɾ��ͼ����Ϣ��" << endl;
	cout << setw(20) << allbook.elem[bookNo_in].BookNo << setw(20) << allbook.elem[bookNo_in].BookName << setw(10) << allbook.elem[bookNo_in].BookAuthor << setw(30) << allbook.elem[bookNo_in].ExistNumber << setw(30) << allbook.elem[bookNo_in].AllNumber << endl;
	
	
	string flg;

	cout << "ȷ��ɾ�������룺Y " << endl;
	cin >> flg;

	if (flg == "Y" || flg == "y")
	{
		ListDelete_Sq(allbook, bookNo_in);

		//���µ��ı�
		fstream fout(bookData, ios::out | ios::trunc);
		for (int j = 0; j < allbook.length; j++)
		{
			string data = to_string(allbook.elem[j].BookNo) + "," + allbook.elem[j].BookName + "," + allbook.elem[j].BookAuthor + "," + to_string(allbook.elem[j].ExistNumber) + "," + to_string(allbook.elem[j].AllNumber);
			fout << data << endl;
		}
		fout.close();

		cout<<"�ѳɹ�ɾ������ͼ��,������ͼ����Ϣ��"<<endl;

		if (allbook.length == 0)
		{
			cout << "Ŀǰͼ������Ϊ�� 0" << endl;
		}
		else {
			cout << "Ŀǰͼ������Ϊ�� " << allbook.length << endl;
			cout << setw(20) << "ͼ����" << setw(20) << "ͼ������" << setw(10) << "ͼ������" << setw(30) << "ͼ�鵱ǰ���" << setw(30) << "ͼ��������" << endl;
			for (int i = 0; i < allbook.length; i++)
			{
				cout << setw(20) << allbook.elem[i].BookNo << setw(20) << allbook.elem[i].BookName << setw(10) << allbook.elem[i].BookAuthor << setw(30) << allbook.elem[i].ExistNumber << setw(30) << allbook.elem[i].AllNumber << endl;
			}
		}
	}
	else {
		cout << "ȷ�ϴ���ɾ��ʧ�ܣ�" << endl;
		cout << "�ѷ��أ�" << endl;
		return;
	}

	
} 
