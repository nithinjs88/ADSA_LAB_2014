#ifndef _BST_H
#define _BST_H

class BST {
public:
	BST();
  	int insert(Node* newnode);
	Node* search(int id);
	Node* getRoot();
	void printTree();
	void RecPOPrint(Node* currRoot);  // Recursive routine that prints tree in preorder format.
	void POPrint();  		  // Nonrecursive routine that prints tree in preorder format.
private:
	Node* ROOT;
	int add(Node* currRoot, Node* newnode);
	Node* find(Node* currRoot, int id);
	
};


#endif
