#include<bits/stdc++.h>
#include "Tree.h"
using namespace std;
#define LESSER -1
#define EQUAL 0
#define GREATER 1
#define DEBUG 0
#define dout if(DEBUG) cout
#define debug if(DEBUG)
Tree::Tree() {
		root=NULL;
}

Tree::~Tree() {
	
}
/*
void Tree::inorderTraversal(TreeNode* rootNode){
	if(rootNode !=NULL) {
		inorderTraversal(rootNode->getLeft());
		rootNode->printNode();
		inorderTraversal(rootNode->getRight());
	}
}

void Tree::inorderTraversal(){
	inorderTraversal(root);
}
*/
void Tree::printTree(TreeNode* rootNode){
	if(rootNode !=NULL) {
		rootNode->printNode();
		printTree(rootNode->getLeft());
		printTree(rootNode->getRight());
	}
}

void Tree::printTree(){
	printTree(root);
}

void Tree::insert(TreeNode* newNode){
	if(root ==NULL)
		root = newNode;
	else
		insert(newNode,root);
}

TreeNode* Tree::insert(TreeNode* newNode,TreeNode* rootNode){
	if(rootNode == NULL)
		return NULL;
		
	//dout<<"new node "<<newNode->getJobId()<<" cur root "<<rootNode->getJobId()<<endl;
	int compareTo = newNode->compareTo(rootNode);
	//dout<<"newNode compareTo curroot "<<compareTo<<endl;
	TreeNode* child = NULL;
	if(compareTo == LESSER) {
		child = insert(newNode,rootNode->getLeft());
		if(child == NULL) {
			rootNode->pointToLeft(newNode);
			newNode->pointToParent(rootNode);
		}
	} else if(compareTo == GREATER){
		child = insert(newNode,rootNode->getRight());
		if(child == NULL) {
			rootNode->pointToRight(newNode);
			newNode->pointToParent(rootNode);
		}
	} else if(compareTo == EQUAL){
		ostringstream oss("");
		oss<<"Duplicate jobId "<<newNode->getJobId()<<". Insert unsuccessful.";
		//cout<<"Duplicate jobId "<<newNode->getJobId()<<". Insert unsuccessful."<<endl;
		error(oss.str());
	}
	/*
	if(child == NULL) {
		newNode->pointToParent(rootNode);
	}
	*/
	return rootNode;
}
void Tree::remove(int id) {
	TreeNode* delNode = search(id);
	if(delNode == NULL) {
		ostringstream oss("");
		oss<<"JobId "<<id<<" not found. Remove unsuccessful.";
		//cout<<"Duplicate jobId "<<newNode->getJobId()<<". Insert unsuccessful."<<endl;
		error(oss.str());
	} else {
		remove(delNode);
	}
}
TreeNode* Tree::remove(TreeNode* delNode) {
	//TreeNode* delNode = search(id);
	if(delNode ==NULL) {
		return NULL;
	} else {
		dout<<"del node ";
		debug delNode->printNode();
		bool isRootDel = delNode == root;
		int childType = getChildType(delNode->getParent(),delNode);
		dout<<"child type "<<childType<<endl;
		if(delNode->getLeft() ==NULL && delNode->getRight() ==NULL) {
			dout<<"both null"<<endl;
			if(isRootDel) {
				root = NULL;
			} else {
				dout<<"del node parent ";
				debug delNode->getParent()->printNode();
				if(childType == LEFT_CHILD) {
					dout<<"set left child of del parent null"<<endl;
					delNode->getParent()->pointToLeft(NULL);
				} else if(childType == RIGHT_CHILD){
					dout<<"set right child of del parent null"<<endl;
					delNode->getParent()->pointToRight(NULL);
				}
			}
		} else if(delNode->getLeft() ==NULL) {
			
			//right not null
			dout<<"right not null"<<endl;
			if(isRootDel) {
				root = root->getRight();
				//root -> pointToParent(NULL); 
				//return;
			} else {
				if(childType == LEFT_CHILD) {
					delNode->getParent()->pointToLeft(delNode->getRight());
				} else if(childType == RIGHT_CHILD){
					delNode->getParent()->pointToRight(delNode->getRight());
				}
				delNode->getRight()->pointToParent(delNode->getParent());
			}
			
		} else if(delNode->getRight() ==NULL) {
			//left not null
			dout<<"left not null"<<endl;
			if(isRootDel) {
				root = root->getLeft();
				root -> pointToParent(NULL); 
			} else {
				if(childType == LEFT_CHILD) {
					delNode->getParent()->pointToLeft(delNode->getLeft());
				} else if(childType == RIGHT_CHILD){
					delNode->getParent()->pointToRight(delNode->getLeft());
				}
				delNode->getLeft()->pointToParent(delNode->getParent());
			}
		} else {
			dout<<"both not null"<<endl;
			TreeNode* successor = getSuccessor(delNode);
			dout<<"successor ";
			debug successor->printNode();
			delNode->swapValues(successor);
			dout<<"swapped del node ";
			debug delNode->printNode();
			dout<<"swapped successor node ";
			debug successor->printNode();
			int succReln = getChildType(successor->getParent(),successor);
			if(succReln == LEFT_CHILD) {
				successor->getParent()->pointToLeft(successor->getRight());
			} else {
				successor->getParent()->pointToRight(successor->getRight());
			}
			if(successor->getRight() != NULL) {
				successor->getRight()->pointToParent(successor->getParent());
			}
			delNode = successor;
			//return remove(successor);
		}
		delNode->pointToParent(NULL);
		return delNode;
	}
}
TreeNode* Tree::search(int jobId) {
	TreeNode* dummyNode =new TreeNode(jobId,0,0);
	return search(root,dummyNode);
}

TreeNode* Tree::search(TreeNode* rootNode,TreeNode* dummyNode) {
	if(rootNode == NULL) {
		return NULL;
	} else {
		int compareTo = dummyNode->compareTo(rootNode);
		switch(compareTo) {
			case LESSER:
				return search(rootNode->getLeft(),dummyNode);
			case GREATER:
				return search(rootNode->getRight(),dummyNode);
			case EQUAL:
				return rootNode;
			default:
				return NULL;
		}
		/*
		if(compareTo == LESSER) {
			return search(rootNode->getLeft(),dummyNode);
		} else if(compareTo == GREATER){
			return search(rootNode->getRight(),dummyNode);
		} else if(compareTo == EQUAL){
			return rootNode;
		}
		*/
	}
}

void Tree::error(string msg) {
	cout<<"ERROR "<<msg<<endl;
}

int Tree:: getChildType(TreeNode* parentNode,TreeNode* childNode) {
	if(parentNode!= NULL && childNode!=NULL) {
		if(parentNode->getLeft() == childNode) {
			return LEFT_CHILD;
		} else if(parentNode->getRight() == childNode) {
			return RIGHT_CHILD;
		}
	}
	return NOT_CHILD;
}

TreeNode* Tree::getSuccessor(TreeNode* node) {
	node = node->getRight();
	while(node !=NULL && node->getLeft()!=NULL) {
		node = node->getLeft();
	}
	return node;
}
