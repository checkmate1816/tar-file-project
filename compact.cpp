#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include "function.h"
using namespace std;



int main()
{
	string path = "";
	cout << "�����ļ�·��" << endl;
	cin >> path;
	LPCSTR filepath = path.c_str();
	DWORD FileAttr = GetFileAttributes(filepath);//�ж��Ƿ����ļ�����Ŀ¼
	if (FileAttr == INVALID_FILE_ATTRIBUTES)
	{
		cout << "Ŀ¼��Ч" << endl;
		exit(0);
	}
	if (FileAttr == FILE_ATTRIBUTE_DIRECTORY)//pathΪĿ¼�����
	{
		tardir(path);
	}
	else//pathΪ�ļ������
	{
		tarfile(path);
	}
	return 0;

}