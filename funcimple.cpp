#include"decodehead.h"
Node * construct(Node *tree, map<string, char>store, bool judge, string level, int max)
{
	if (level.size() > max)
		return NULL;
	if (judge == true)
	{
		level = level + '1';
		map<string, char>::iterator search;
		search = store.find(level);
		tree = new Node();
		tree->alpha = search->second;
		tree->code = search->first;
		return tree;
	}
	else
	{
		level = level + '0';
		if (level.size() == max)
		{
			map<string, char>::iterator search;
			search = store.find(level);
			tree = new Node();
			tree->alpha = search->second;
			tree->code = search->first;
			return tree;
		}
		else
		{
			tree = new Node();
			tree->left = construct(tree->left, store, false, level, max);
			tree->right = construct(tree->right, store, true, level, max);
			return tree;
		}
	}
}
void buildtree(Node *tree, map<string, char>store)
{
	int max = 0;
	for (auto a : store)
	{
		if (a.first.size() > max)
		{
			max = a.first.size();
		}
	}
	string lcode = "";
	tree->left = construct(tree->left, store, false, lcode, max);
	tree->right = construct(tree->right, store, true, lcode, max);
}
char * retrive(Node *tree, FILE *file, char *body)
{
	if (tree->left == NULL && tree->right == NULL)
	{
		fputs(&tree->alpha, file);
		return body;
	}
	if (*body == '0')
	{
		body++;
		body = retrive(tree->left, file, body);
		return body;
	}
	else
	{
		body = retrive(tree->right, file, body);
		body++;
		return body;
	}

}