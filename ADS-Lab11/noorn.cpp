#include <iostream>
#include <stdlib.h>
#include <string.h>

#define notDEBUG        //make it just DEBUG to use the sample example given in our test question.

using namespace std;


struct avlNode
{
    int val;
    struct avlNode* leftNode;
    struct avlNode* rightNode;
}*current;

class avlTree 
{
public:
    int height(avlNode*);
    int heightDiff(avlNode*);
    avlNode* rightLeftRotation(avlNode*);
    avlNode* rightRightRotation(avlNode*);
    avlNode* leftLeftRotation(avlNode*);
    avlNode* leftRightRotation(avlNode*);
    avlNode* balance(avlNode*);
    avlNode* insert(avlNode*, int);
    void inorderWalk(avlNode*);
    avlTree() 
    {
       current = NULL;
    }
};


int main(void)
{
	int arraySize = 6 ;
#ifdef DEBUG
	int A[] = { 4,2,3,6,5,1 }; //sample, not to be included.
#else 
	int A[] = { 3,5,6,4,1,2 }; //actual example to be included
#endif
    avlTree avl;
    cout << "Input Array A=[";
    for (int i = 0; i < arraySize; i++)
    {
        if (i != 0)
        {
            cout << ' ';
        }
        cout << A[i];
        if (i != arraySize - 1)
        {
            cout << ',';
        }
        else
        {
            cout << ']' << endl;
        }
    }


    for (int i = 0; i < arraySize; i++)
    {
        current = avl.insert(current, A[i]);
        avl.inorderWalk(current);
        cout << endl;
    }
}














int avlTree::height(avlNode* t) {
    int h = 0;
    if (t != NULL) {
        int l_height = height(t->leftNode);
        int r_height = height(t->rightNode);
        int max_height = l_height;
        if (r_height > l_height)
        {
            max_height = r_height;
        }
        h = max_height + 1;
    }
    return h;
}

int avlTree::heightDiff(avlNode* t) {
    int l_height = height(t->leftNode);
    int r_height = height(t->rightNode);
    int diff = l_height - r_height;
    return diff;
}
avlNode* avlTree::rightLeftRotation(avlNode* parent)
{
    avlNode* temp;
    temp = parent->rightNode;
    parent->rightNode = leftLeftRotation(temp);
    return rightRightRotation(parent);
}
avlNode* avlTree::rightRightRotation(avlNode* parent) 
{
    avlNode* temp;
    temp = parent->rightNode;
    parent->rightNode = temp->leftNode;
    temp->leftNode = parent;
    return temp;
}

avlNode* avlTree::leftLeftRotation(avlNode* parent)
{
    avlNode* temp;
    temp = parent->leftNode;
    parent->leftNode = temp->rightNode;
    temp->rightNode = parent;
    return temp;
}
avlNode* avlTree::leftRightRotation(avlNode* parent) 
{
    avlNode* temp;
    temp = parent->leftNode;
    parent->leftNode = rightRightRotation(temp);
    return leftLeftRotation(parent);
}
avlNode* avlTree::balance(avlNode* node)
{
    int balStat = heightDiff(node);
    if (balStat > 1) {
        if (heightDiff(node->leftNode) <= 0)
            node = leftRightRotation(node);
        else
            node = leftLeftRotation(node);
    }
    else if (balStat < -1) {
        if (heightDiff(node->rightNode) <= 0)
            node = rightRightRotation(node);
        else
            node = rightLeftRotation(node);
    }
    return node;
}

avlNode* avlTree::insert(avlNode* treeNode, int val) {
    if (treeNode == NULL) 
    {
        treeNode = new avlNode;
        treeNode->val = val;
        treeNode->leftNode = NULL;
        treeNode->rightNode = NULL;
        return treeNode;
    }
    else if (val < treeNode->val) 
    {
        treeNode->leftNode = insert(treeNode->leftNode, val);
        treeNode = balance(treeNode);
    }
    else if (val >= treeNode->val) 
    {
        treeNode->rightNode = insert(treeNode->rightNode, val);
        treeNode = balance(treeNode);
    } return treeNode;
}

void avlTree::inorderWalk(avlNode* node) 
{
    if (node == NULL)
        return;
    inorderWalk(node->leftNode);
    cout << node->val << " ";
    inorderWalk(node->rightNode);
}