#include<bits/stdc++.h>
#include "Tree.h"
using namespace std;
#define LESSER -1
#define EQUAL 0
#define GREATER 1
#define DEBUG 1
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

/*
 * debug imaging starts
 */
void Tree:: debug_image(string file_name) {
	string img_file = file_name + ".png";
	string dot_file = file_name + ".dot";
	ofstream op_stream;
	op_stream.open (dot_file.c_str());
	op_stream<<get_debug_graph_string();
	op_stream.close();
	
	ostringstream oss;
	oss<<"dot -Tpng "<<dot_file<<" -o "<<img_file;
	int status = system(oss.str().c_str());
}

string Tree::get_debug_graph_string(){
	ostringstream oss("");
	oss<<("digraph G { ");
	oss<<endl;
	//oss<<"\t"<<"size =\"6,6\";"<<endl;
	oss<<"\t"<<"edge[arrowhead=normal,arrowtail=none]"<<endl<<endl;
	
	queue<TreeNode*> bfs_queue;
	if(root != NULL)
		bfs_queue.push(root);
	TreeNode* ptr;
	map<TreeNode*,string> node_names;
	while (!bfs_queue.empty()) {
		ptr = bfs_queue.front();
		//dout<<"front ele is "<<ptr->get_node_string()<<endl;
		oss<<get_debug_graph_string(ptr,node_names);
		bfs_queue.pop();
		if(ptr->getLeft() != NULL) {
			bfs_queue.push(ptr->getLeft());
			//dout<<"enqueing "<<ptr->getLeft()->get_node_string()<<endl;
		}
		if(ptr->getRight() != NULL) {
			bfs_queue.push(ptr->getRight());
			//dout<<"enqueing "<<ptr->getRight()->get_node_string()<<endl;
		}
	}
	oss<<"}"<<endl;
	return oss.str();
}

string Tree::get_debug_graph_string(TreeNode* node,map<TreeNode*,string> &node_names) {
	if(node == NULL)
		return "";
	ostringstream oss("");
	string node_name = "";
	//dout<<"node name is "<<node_name<<endl;
	node_name = node_names[node];
	//dout<<"node name is "<<node_name<<endl;
	if(node_name.empty()) {
		
		string add_node = add_node_graph_map(node,node_names);
		//dout<<"add_node_graph_map for cur node "<<add_node<<endl;
		oss<<"\t"<<add_node;
		//reinitialize node_name
		node_name = node_names[node];
		//dout<<"node name after rein is "<<node_name<<endl;
	}
	
	//draw black edge for parent
	TreeNode* parent = node->getParent();
	if(parent !=NULL) {
		//dout<<"parent not NULL"<<endl;
		string parent_name = node_names[parent];
		//dout<<"parent name is "<<parent_name<<endl;
		if(parent_name.empty()) {
			string add_parent = add_node_graph_map(parent,node_names);
			//dout<<"add_node_graph_map for cur node "<<add_parent<<endl;
			oss<<"\t"<<add_parent;
			//reinitialize parent_name
			parent_name = node_names[parent];
			//dout<<"parent name after rein is "<<node_name<<endl;
		}
		oss<<"\t"<<"edge [color=black];"<<endl;
		oss<<"\t"<<node_name<<" -> "<<parent_name<<endl;
		
	} else {
		//dout<<"parent NULL for "<<node_name<<endl;
	}
	
	//draw blue edge for left child
	TreeNode* left_child = node->getLeft();
	if(left_child !=NULL) {
		string left_child_name = node_names[left_child];
		if(left_child_name.empty()) {
			string add_left = add_node_graph_map(left_child,node_names);
			oss<<"\t"<<add_left;
			//reinitialize node_name
			left_child_name = node_names[left_child];
		}
		oss<<"\t"<<"edge [color=blue];"<<endl;
		oss<<"\t"<<node_name<<" -> "<<left_child_name<<endl;
		
	}
	
	//draw red edge for right child
	TreeNode* right_child = node->getRight();
	if(right_child !=NULL) {
		string right_child_name = node_names[right_child];
		if(right_child_name.empty()) {
			string add_right = add_node_graph_map(right_child,node_names);
			oss<<"\t"<<add_right;
			//reinitialize node_name
			right_child_name = node_names[right_child];
		}
		oss<<"\t"<<"edge [color=red];"<<endl;
		oss<<"\t"<<node_name<<" -> "<<right_child_name<<endl;
		
	}
	oss<<endl;
	return oss.str();
}

string Tree:: add_node_graph_map(TreeNode* node,map<TreeNode*,string> &node_names) {
	string node_name = "";
	node_name = node_names[node];
	//dout<<"node name in add_node_graph_map is "<<node_name<<endl;
	if(node_name.empty()) {
		node_name = get_debug_node_name(node);
		//dout<<"node name in add_node_graph_map after fn call is "<<node_name<<endl;
		//add into the map
		node_names[node] = node_name;
		//add into the graph
		//dout<<"b4 call to get_debug_node_string"<<endl;
		string node_graph_str = get_debug_node_string(node);
		//dout<<"after call to get_debug_node_string"<<endl;
		//dout<<"size of node_graph_str "<<node_graph_str.size();
		//dout<<"node_graph_str in add_node_graph_map after fn call is "<<node_graph_str<<endl;	
		return node_graph_str;
	}
	return "";
}
string Tree:: get_debug_node_name(TreeNode* node){
	if(node == NULL)
		return "";
	ostringstream node_name_oss("");
	node_name_oss << "node" << node->getJobId();
	//dout<<"debug_node_name is "<<node_name_oss.str()<<endl;
	return node_name_oss.str();
}

string Tree:: get_debug_node_string(TreeNode* node){
	if(node == NULL)
		return "";
	ostringstream oss("");
	oss<<get_debug_node_name(node);
	oss<<" [shape=circle,label=\""<<node->getJobId();
	oss<<"\"];";
	oss<<endl;
	//dout<<"debug_node_string is "<<oss.str()<<endl;
	return oss.str();
}

/*
 * debug imaging ends
 */
