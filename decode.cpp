#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<map>
#include"decodehead.h"
#include <QDebug>
using namespace std;


void untar(string path)
{
	FILE *fp;
	fp = fopen(path.c_str(), "r");//fpΪ����ѹ�ļ�
	fseek(fp, 0L, SEEK_END);
	int totalsize = ftell(fp);//��¼�ļ����ֽ���
	rewind(fp);
	map<string, char> huffman;//������
	if (fp == NULL)
	{
		qDebug() << "error";
		exit(0);
	}
	header filehead = { '\0',{'\0'},{'\0'},{'\0'} };
	string temp = "";
	char head[512] = { '\0' };//�洢���������ļ�����
	int i = 0;//������
	long position = ftell(fp);
	while (feof(fp) == 0)
	{
		fread(&filehead, sizeof(header), 1, fp);//ÿ�ζ�512���ֽ�
		position = ftell(fp);
		if (filehead.type == '0')//��ǰͷ��Ϊ�ļ���
		{
			temp = "md ";
			temp = temp + filehead.source;
			system(temp.c_str());
			temp = "";
		}
		else//��ǰͷ��Ϊ�ļ�
		{
			FILE *final;//���ɵĴ洢�ļ�
			final = fopen(filehead.source, "a+");
			strcpy(head, filehead.content);//����������
			i = 0;
			char tempchar = '\0';
			while (i < 512)//����������Ϊӳ���ֵ�ӳ����ϵ
			{
				if (head[i] == '\0')
					break;
				else if (isalpha(head[i]) != 0)
				{
					tempchar = head[i];
					i++;
					while (isdigit(head[i]) != 0)
					{
						temp = temp + head[i];
						i++;
					}
					huffman.insert(make_pair(temp, tempchar));
					temp.clear();
				}
			}
			Node *huffmantree = new Node();
			buildtree(huffmantree, huffman);//������������
			i = 0;
			char body[512] = { '\0' };
			int num;
			num = atoi(filehead.size);//�洢���������ַ�����
			if (num <= 512)//��������������һ��512����
			{
				fread(body, sizeof(char), num, fp);//���ļ���������������
				position = ftell(fp);
				char *tranverse = body;
				while (*tranverse != '\0')
				{
					tranverse = retrive(huffmantree, final, tranverse);
				}//�����������ļ�д���洢�ļ���
				fseek(fp, 512 - num, SEEK_CUR);//����ʣ����0
				position = ftell(fp);
				fseek(fp, 512, SEEK_CUR);//�����ļ���β��512��0
				position = ftell(fp);
				fclose(final);
				if (ftell(fp)==totalsize)
					break;
			}
			else//���������ֳ���1��512�ֽڵĿ�
			{
				while (num > 512)
				{
					fread(body, sizeof(char), 512, fp);//���ļ���������������
					char *tranverse = body;
					while (*tranverse != '\0')
					{
						tranverse = retrive(huffmantree, final, tranverse);
					}//�����������ļ�д���洢�ļ���
					num -= 512;
				}
				fread(body, sizeof(char), num, fp);//���ļ�����ʣ���Ĺ���������
				char *tranverse = body;
				while (*tranverse != '\0')
				{
					tranverse = retrive(huffmantree, final, tranverse);
				}//��С�ڵ���512�ֽڵĲ��ֽ���д���洢�ļ���
				fseek(fp, 512 - num, SEEK_CUR);//����ʣ����0
				fseek(fp, 512, SEEK_CUR);//�����ļ���β��512��0
				fclose(final);
				if (ftell(fp) == totalsize)
					break;
			}
		}
	}
	fclose(fp);
}
