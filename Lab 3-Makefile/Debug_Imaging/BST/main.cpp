#include<bits/stdc++.h>
#include "Tree.h"
using namespace std;
#define DEBUG 1
#define dout if(DEBUG) cout
#define debug if(DEBUG)

void error(string msg) {
	cout<<"ERROR: "<<msg<<endl;
}
void readInput(Tree* bst,string inputFile) {
	ifstream in;
	in.open(inputFile.c_str());
	string inputLine;
	int jobId,priority,duration;
	while (getline(in, inputLine)) {
		istringstream iss;
		iss.str(inputLine);
		if(inputLine.length()>0) {
			iss >> jobId>>priority>>duration;
			TreeNode *node = new TreeNode(jobId,priority,duration);
			//dout<<"To insert node with jobId "<< jobId<<endl;
			bst->insert(node);
		} 
		
	}
	dout<<"Inorder "<<endl;
	//debug bst->inorderTraversal();
	dout<<"Insert Over"<<endl;
	in.close();
}

void readTestCases(Tree* bst,string testFile) {
	//debug bst->inorderTraversal();
	//dout<<"Test case start"<<endl;
	ifstream in;
	in.open(testFile.c_str());
	string inputLine;
	int jobId,priority,duration;
	while (getline(in, inputLine)) {
		istringstream iss;
		iss.str(inputLine);
		char ch;
		if(inputLine.length()>0) {
			iss>>ch;
			dout<<inputLine<<endl;
			if(ch == 'I') {
				int jobId,priority,duration;
				iss >> jobId>>priority>>duration;
				TreeNode *node = new TreeNode(jobId,priority,duration);
				dout<<"To insert node with jobId "<< node->getJobId()<<endl;
				bst->insert(node);
			} else if(ch =='S') {
				int searchId;
				iss >> jobId;
				TreeNode *searchNode = bst->search(jobId);
				if(searchNode == NULL) {
					ostringstream oss("");
					oss<<jobId<<" "<<"jobId not found.";
					error(oss.str());
				} else {
					cout<<searchNode->getDuration()<<" "<<searchNode->getPriority()<<endl;
				}
			} else if(ch =='R') {
				int searchId;
				iss >> searchId;
				bst->remove(searchId);
			} else if(ch =='P') {
				bst->printTree();
				debug bst->debug_image("debug_bst");
			}
		} 
		
	}
	//dout<<"Inorder "<<endl;
	//debug bst->inorderTraversal();
	//dout<<"Insert Over"<<endl;
	in.close();
}


int main(int argc,char *argv[]) {
		if(argc != 3) {
			error("Invalid no of arguments");
			return -1;
		}
		Tree* bst = new Tree();;
		readInput(bst,argv[1]);
		readTestCases(bst,argv[2]);
}
