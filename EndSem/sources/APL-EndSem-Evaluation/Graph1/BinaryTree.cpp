#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "string.h"
using namespace std;

const int MAX=1025; // ensure 2^k + 1 for some k



class BinaryTree {
private:	
	bool nodes[MAX];
	int pre[MAX];
	int post[MAX];
	int height[MAX];
	int numNodes;
//	vector<int> A(1025, 0);
//	vector<int> B(1025, 0);
	int A[MAX];
	int B[MAX];

	int visit_time; // Use this to compute pre-visit and post-visit numbers in your DFS.
	
	bool DFS_done; // initialized to false and set to true after first DFS, thus indicating that
					// pre, post and height arrays are populated.
	
	bool DFS_visit(int node);
	
public:
	BinaryTree(){
		for(int i=1;i<MAX;i++){
			nodes[i]=false;	
			pre[i]=-1;
			post[i]=-1;
			height[i]=-1;
		}
		this->DFS_done = false;
		
	}
	
	
	
	bool isNode(int node){
	/*
		The following function returns 1 if for a given index $i$ the
		node corresponding to that id is present in the binary tree. Else
		the function returns 0.
	*/
		return nodes[node];
	}
	
	
	/*
		The following four functions return proper values
		only after a proper execution of DFS in which these
		numbers are correctly computed and stored in the 
		appropriate private arrays. 
	*/
	int getPre(int node){
		return pre[node];
	}
	int getPost(int node){
		return post[node];
	}
	int getHeight(int node){
		return height[node];
	}
	bool isDfsDone(){
		return DFS_done;
	}
	
	
	bool readFile(char *filename){
	/* Following function reads the file containing the 
	   specification of the binary tree.
	   Recall that node ids start at 1 instead of 0.
	*/
		string token;
		int index=1;
		ifstream fin;
		numNodes=0;
		int tt;
		for(int i=0;i<MAX;i++){
			nodes[i]=false;	
			pre[i]=-1;
			post[i]=-1;
			height[i]=-1;
		}
		
		fin.open(filename);
		do {
			fin >> token;
			if(token.compare("1")==0){
				nodes[index++]=true;
				if(!nodes[(index-1)/2] && index >2){
					cout << "Error (no parent) in line " << index << endl;
					return false;
				}
				numNodes++;
			}
			else if(token.compare("0") == 0){
				nodes[index++]=false;
			}
			else if(token.compare("end")!=0){
				cout << "Error in line " << ++index << endl;
				fin.close();
				return false;
			}
		}while(token.compare("end") != 0);
		index  = 0;
		do {
			fin >> tt;
			A[index] = tt;
			index++;
		}while(tt != -100);
		index  = 0;
		do {
			fin >> tt;
			B[index] = tt;
			index++;
		}while(tt != -100);
//		cout << "Reading done" << endl;
//		int h;
//		cin >> h;	

		fin.close();
//		cout << "Reading done" << endl;
		return true;
	}
	
	bool gvout(char *filename){
		ofstream fout;
		fout.open(filename);
		fout << "digraph tree{" << endl; 
		
		
		/*
			The following for loop ensures that each node is printed with labels that 
			give information about its pre-visit, post-visit numbers and the height of the subtree
			provided that these numbers have been pre-computed in your DFS. Otherwise, these numbers 
			are initialized to -1 in the constructor and therefore will appear as zeros.	
		*/
		for(int i =1; i<(MAX-1)/2; i++){
			if(nodes[i]){
				fout << i << " [label=\"" << i << " (" << pre[i] << "," << post[i] << "," << height[i] << ")\"];"  << endl;
			}
		}
		for(int i=1;i<(MAX-1)/2;i++){
			if(nodes[i] && nodes[2*i]){
				fout << i << " -> " << 2*i << endl;
			}
			if(nodes[i] && nodes[2*i+1]){
				fout << i  << " -> " << 2*i+1 << endl;
			}
		}
		fout << "}";
		fout.close();
		return true;
	}
	
	bool DFS(){
		visit_time = 1;
		if(DFS_done){
			return true;
		}
		DFS_done= DFS_visit(1);
		return DFS_done;
		
	}
	bool isPre()
	{
		for (int i = 0 ; i < numNodes; i++)
		{
			if (A[i] != pre[i])
				return false;
		}
		return true;
	}	
	bool isPost()
	{
		for (int i = 0 ; i < numNodes; i++)
		{
			if (B[i] != post[i])
				return false;
		}
		return true;
	}
	void printPre()
	{
		for (int i = 0; i < numNodes; i++)
			cout << pre[i] << endl;
		cout << "-100" << endl;
	}
	void printPost()
	{
		for (int i = 0; i < numNodes; i++)
			cout << post[i] << endl;
		cout << "-100" << endl;
	}
};

