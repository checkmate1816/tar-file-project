#include"function.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<windows.h>
#include "finalpath.h"
#include <QDebug>
using namespace std;
Node* newNode(int j, char n)
{
	Node *temp = new Node();
	temp->num = j;
	temp->a = n;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
Node * build(vector<pair<char, int>> temp)//´´½¨¹þ·òÂüÊ÷
{
	int i;
	Node *maxNode = newNode(temp[0].second, temp[0].first);
	for (i = 1; i < temp.size(); i++)
	{
		Node *temp1 = newNode(temp[i].second, temp[i].first);
		int max = temp1->num + maxNode->num;
		Node *tempnode = newNode(max, '\0');
		tempnode->left = maxNode;
		tempnode->right = temp1;
		maxNode = tempnode;
	}
	return maxNode;
}
bool cmp(pair<char, int> a, pair<char, int> b)
{
	return a.second < b.second;
}
bool huffmancode(Node *tree, map<char, string> &code, bool judge, string &hcode)
{
	if (tree == NULL)
		return false;
	if (judge == true)
		hcode = hcode + "1";
	else
		hcode = hcode + "0";
	bool right = huffmancode(tree->right, code, true, hcode);
	bool left = huffmancode(tree->left, code, false, hcode);
	if (right == false && left == false)
		code.insert(make_pair(tree->a, hcode));
	hcode.pop_back();
	return true;
}
void encode(Node *tree, map<char, string> &code)
{
	if (tree == NULL)
		return;
	string hcode = "";
	huffmancode(tree->right, code, true, hcode);
	huffmancode(tree->left, code, false, hcode);
}




