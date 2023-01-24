#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MAXSIZE 100

#define UPPERBOUNDRY 9999999

class bstnode
{
private:

protected:

public:
	int value;
//	node* root;
	bstnode* left;
	bstnode* right;
	bstnode* parent;

	bstnode()
	{
//		this->value = NULL;
		//value = NULL;
		//left = NULL;		//=nullptr;
		//right = NULL;		//=nullptr;
		//parent = NULL;		//=nullptr;
	}
	~bstnode() {}
};


void postorderWalk(bstnode* root)
{
	if (root == NULL)
	{
		return;
	}
	postorderWalk(root->left);
	postorderWalk(root->right);
	cout << root->value << ',';
};


void successorOf(bstnode* root,int givenElement, int foundElement=UPPERBOUNDRY)
{
	if (root == NULL)
	{
		return;
	}
	postorderWalk(root->left);
	postorderWalk(root->right);
	if (root->value > givenElement)
	{
		if (root->value < foundElement)
		{
			if (foundElement != UPPERBOUNDRY)
				cout << "The succesor of " << givenElement << "is: " << foundElement << '.'<<endl;
			else
				cout << "The succesor of " << givenElement << "is: " << givenElement << "itself." << endl;
		}
	}
};


bstnode* insert(bstnode* node, int value, int ithInsert)
{
	//Handing actual entry process

	if (node==NULL&& ithInsert==0)
	{
		node = new bstnode;
		node->value = value;
		node->left = NULL;		//=nullptr;
		node->right = NULL;		//=nullptr;
		node->parent = NULL;		//=nullptr;
		//postorderWalk(node);
	}
	else if (node == NULL)
	{
		node = new bstnode;
		node->value = value;
		node->left = NULL;		//=nullptr;
		node->right = NULL;		//=nullptr;
	}
	//if (node->parent == NULL && isnullnode->value)
	//{
	//	//Note that left, right, and parent are set as NULL in default constructor already.
	//	node->value = value;
	//}
	//else if (node->value == NULL)
	//{
	//	node = new bstnode;					//Note that left, right, and parent are set as NULL in default constructor already.
	//}


	//handling recursion part
	else if (node->value > value)	//left branch
	{
		node->left = insert(node->left, value,ithInsert);
		node->left->parent = node;
	}
	else if (value > node->value)		//right branch
	{
		node->right = insert(node->right, value,ithInsert);
		node->right->parent = node;
	}
	return node;
}


int main(void)
{

	//inputting data:
	int givenElement =5;
	int A[] = { 4,1,2,7,3,6,5,-1};		//-1 symbolizes end of array
														//int A[MAXSIZE]; int givenElement = -2;		//for finding k-th largest element
														//for (int i = 0; i < MAXSIZE; i++)
														//{
														//	A[i] = -2;			//for detecting when the real input (+ive ints) ends  //=-1
														//}

	//calling functions
//	bstnode* root = new bstnode;
	bstnode* root = NULL;
	bstnode* lastInserted = NULL;
	for (int i = 0; i < MAXSIZE && A[i] != -1 ; i++)
	{
		if (i == 0)
		{
			root = insert(root, A[i], i);
			lastInserted = root;
		}
		else
		{
			lastInserted = insert(lastInserted, A[i], i);
			lastInserted = root;
		}
		postorderWalk(root);
		cout << endl;
	}
	successorOf(root, givenElement);
	//return
	return EXIT_SUCCESS;
}