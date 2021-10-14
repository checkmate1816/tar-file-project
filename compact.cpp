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
	cout << "输入文件路径" << endl;
	cin >> path;
	LPCSTR filepath = path.c_str();
	DWORD FileAttr = GetFileAttributes(filepath);//判断是否是文件或者目录
	if (FileAttr == INVALID_FILE_ATTRIBUTES)
	{
		cout << "目录无效" << endl;
		exit(0);
	}
	if (FileAttr == FILE_ATTRIBUTE_DIRECTORY)//path为目录的情况
	{
		tardir(path);
	}
	else//path为文件的情况
	{
		tarfile(path);
	}
	return 0;

}