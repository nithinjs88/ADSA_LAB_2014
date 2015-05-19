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
	
	//debug img variables
	void debug_image(string file_name);
	
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
	
	//debug img variables
	//string in graphviz for entire tree for debugging
	string get_debug_graph_string();
	//string in graphviz for single node for debugging
	static string get_debug_graph_string(TreeNode* node,map<TreeNode*,string> &node_names);
	//node name in graphviz
	static string get_debug_node_name(TreeNode* node);
	//node string in graphviz
	static string get_debug_node_string(TreeNode* node);
	//add node vertex in graph and map
	static string add_node_graph_map(TreeNode* node,map<TreeNode*,string> &node_names);
	
};
