#include<vector>
#include<map>
#include<Windows.h>
#include<time.h>
#include<string>
using namespace std;

class Node
{
public:
	int num = 0;
	char a = '\0';
	Node *left, *right;
};
class header
{
public:
	char type;//1为文件，0为目录
	char size[10];
	char source[100];
	char content[401];

};
class Record
{
public:
	char block[512];
};
Node * newNode(int j, char n);
Node *build(vector<pair<char, int>> temp);
bool cmp(pair<char, int> a, pair<char, int> b);
bool huffmancode(Node *tree, map<char, string> &code, bool judge, string &hcode);
void encode(Node *tree, map<char, string> &code);


//void pack(string path,vector<string> &store);
