#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "common_functions.cpp"
using namespace std;
#define DEBUG 0
#define dout	if (DEBUG) cout
#define ifdebug if (DEBUG)
class TreeNode {
  public:
	TreeNode(int id, string &name) {
		this->id = id;
		this->name = name;
		this->left = NULL;
		this->right= NULL;
	}
	std::string getName() {
		return name;
	}
	int getID() {
		return id;
	}
	bool isNameEqual(string &secondname) {
		return name == secondname;
	}
	bool isIDEqual(int  secondid) {
		return id == secondid;
	}
	void pointToLeft(TreeNode *leftnode) {
		this->left = leftnode;
	}
	TreeNode *getLeft() {
		return left;
	}
	void pointToRight(TreeNode *rightnode) {
		this->right = rightnode;
	}
	TreeNode *getRight() {
		return right;
	}
        
private:
	string name;
	int id;
	class TreeNode *left;
    class TreeNode *right;


};

class Tree {

public:
	Tree(){
		root = NULL;
	}
	void readFiles(string inputFile,string testFile);
	void addAdvisee(int parentId,int adviseeId,string name);
	void listAllAdvisee(int id);
	static void error(string msg);
	void inorderTraversal();
private:	
	class TreeNode* root;
	class TreeNode* search(int adviseeid,class TreeNode* rootNode);
	class TreeNode* search(int adviseeid);
	void inorderTraversal(class TreeNode* rootNode);
	void printChildren(TreeNode* rootNode);
};

void Tree::inorderTraversal(class TreeNode* rootNode){
	if(rootNode !=NULL) {
		inorderTraversal(rootNode->getLeft());
		cout<<rootNode->getID()<< " ";
		inorderTraversal(rootNode->getRight());
	}
}

void Tree::inorderTraversal(){
	inorderTraversal(root);
	cout<<endl;
}	

void Tree::addAdvisee(int parentId,int adviseeId, string name){
	TreeNode* newNode = new TreeNode(adviseeId,name);	
	bool insert = false;	
	if(parentId == 0) {
		//check root exists
		if(root == NULL) {
			root = newNode;
			insert = true;				
		} else {
			error("the root already exists");		
		}
	} else {
		TreeNode *parent = search(parentId);
		if(parent == NULL) {
			error("parentId doesnt exist");		
		} else {
			if(parent->getLeft() == NULL) {
				parent->pointToLeft(newNode);
				insert = true;
			} else if(parent->getRight() == NULL) {
				parent->pointToRight(newNode);
				insert = true;			
			}		
		}
	}
	if(!insert)
		delete(newNode);
}

class TreeNode* Tree::search(int adviseeid) {
	return search(adviseeid,root);
}

class TreeNode* Tree::search(int adviseeid,class TreeNode* rootNode) {
	if(rootNode !=NULL) {
		if(rootNode->getID() == adviseeid) {
			return rootNode;
		} else {
			class TreeNode* node = search(adviseeid,rootNode->getLeft());
			if(node == NULL)
				return 	search(adviseeid,rootNode->getRight());
			else 
				return node;	
		}
	}
	return NULL;
}
void Tree::listAllAdvisee(int parentId){
	TreeNode *parentNode = search(parentId);
	if(parentNode == NULL) {
		string str = "No user with id ";
		str.append(convertIntToString(parentId));
		error(str);
	} else {
		TreeNode *leftNode = parentNode->getLeft();
		TreeNode *rightNode = parentNode->getRight();
		if(leftNode == NULL && rightNode ==NULL){
			string str = "No advisees for id ";
			str.append(convertIntToString(parentId));
			error(str);
		}
		printChildren(leftNode);
		printChildren(rightNode);
	}
}

void Tree::printChildren(TreeNode* rootNode){
	if(rootNode != NULL) {
		cout<<"ID "<<rootNode->getID()<<" Name "<<rootNode->getName();
		cout<<endl;
		printChildren(rootNode->getLeft());
		printChildren(rootNode->getRight());
	}
}

void Tree::readFiles(string inputFile,string testFile){
	ifstream in;
	string name;
	int pid,uid;

	in.open(inputFile.c_str());	// doesn't work with strings.
	in >> pid>> uid >> name;
	while (!in.eof()) {
		dout << "PID "<<pid << " UID " << uid<<" name "<<name << endl;
		addAdvisee(pid,uid, name);
		in >> pid>> uid >> name;
	}
	in.close();
	dout<<"The tree formed is "<<endl;
	ifdebug inorderTraversal();
	cout<<endl;
	
	string fileLine;
	//in.open(testFile.c_str());
	in.open(testFile.c_str());
	
	while (getline(in, fileLine)) {
		dout<<"Length is "<<fileLine.length()<<endl;
		cout <<"===="<< fileLine << endl;
		fflush(stdout);
		istringstream iss;
		iss.str(fileLine);
		string args[5];
		int noOfArgs = 0;
		//dout <<"Line :";
		for(int i=0;i<5 && (iss >> args[i]);i++) {
			noOfArgs++;
			//dout<<"arg "<<i<<" "<< args[i]<<" ";
		}
		dout<<"No of args is "<<noOfArgs<<endl;
		dout<<endl;
		if(args[0] == "List") {
			int intArg2;
			bool isValidListArg = true;
			try {
				if(noOfArgs != 2) {
					isValidListArg = false;
				} else {
				 	intArg2 = convertStringToInt(args[1]);
					cout<<"Listing all advisees of "<<intArg2;
					cout<<endl;
					listAllAdvisee(intArg2);
				}
			} catch(int e) {
				isValidListArg = false;
			}
			if(!isValidListArg)
				error("Invalid format of List statement");
			cout<<endl;
		} else if(args[0] == "Add") {
			bool isValidAddArg = true; 
			int intArg2,intArg3;
			try {
				if(noOfArgs != 4) {
					isValidAddArg = false;
				} else {
					intArg2 = convertStringToInt(args[1]);
					intArg3 = convertStringToInt(args[2]);
					cout<<"Adding "<< intArg2 << " "<< intArg3 << " "<< args[3];
					cout<<endl;
					addAdvisee(intArg3,intArg2,args[3]);
				}
				//in >> arg2 >> arg3 >> arg4;
				
			} catch(int e) {
				isValidAddArg = false;
				//error("Invalid format of Add statement");
			}
			if(!isValidAddArg)
				error("Invalid format of Add statement");
			cout<<endl;
		} else {
			error("Invalid argument in "+testFile);
			cout<<endl;		
		}
	}
	ifdebug inorderTraversal();
}

void Tree::error(string msg) {
	std::cout << "ERROR: " << msg << std::endl;
}

int main(int argc, char *argv[]) {
	dout<<"The no of args is "<<argc;
	dout<<endl;
	for(int i=0;i<argc;i++) {
		dout<<"Argument "<<(i+1)<<" is "<<argv[i];
		dout<<endl;
	}
	if (argc != 3) {
		cout << "Invalid number of arguments.\nUsage: " << argv[0] << "<inputfile> <testfile>\n";
		return 1;
	}
	Tree bTree;
	bTree.readFiles(argv[1],argv[2]);
	return 0;
}
