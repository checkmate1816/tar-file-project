#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<map>
using namespace std;
struct Node
{
	char alpha = '\0';
	string code = "";
	Node * left = NULL;
	Node *right = NULL;
};
struct header
{
	char type;//1为文件，0为目录
	char size[10];
	char source[100];
	char content[401];

};
Node * construct(Node *tree, map<string, char>store, bool judge, string level, int max);
void buildtree(Node *tree, map<string, char>store);
char * retrive(Node *tree, FILE *file, char *body);
void untar(string path);
