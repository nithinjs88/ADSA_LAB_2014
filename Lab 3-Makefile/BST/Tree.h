#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "TreeNode.h"
#define LEFT_CHILD 0
#define RIGHT_CHILD 1
#define NOT_CHILD -1

using namespace std;
class Tree {

public:
	Tree();
	~Tree();
	//void inorderTraversal();
	void printTree();
	void insert(TreeNode*);
	void remove(int);
	TreeNode* search(int);
	
	
private:

	TreeNode* root;
	//void inorderTraversal(TreeNode* rootNode);
	void printTree(TreeNode* rootNode);
	TreeNode* insert(TreeNode* newNode,TreeNode* rootNode);
	TreeNode* search(TreeNode* rootNode,TreeNode* dummyNode);
	TreeNode* getSuccessor(TreeNode* node);
	TreeNode* remove(TreeNode* delNode);
	static void error(string msg);
	static int getChildType(TreeNode* parentNode,TreeNode* childNode);
	
};
