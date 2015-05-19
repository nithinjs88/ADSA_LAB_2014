#include "HeapNode.h"
#include<bits/stdc++.h>
#include <iostream>
using namespace std;
class MinHeap {
	
public:
	MinHeap();
	~MinHeap();
	void insertHeapNode(HeapNode* ptr);
	//void read(string inputFile,string outputFile);
	void preorder();
	string preorderString();
	HeapNode* extractMin();
	//string heapSort();
	
	//debug img variables
	void debug_image(string file_name);
	

private:
	HeapNode* root;
	HeapNode* tail;
	int size;	
	string convertIntToString(int num);
	HeapNode* getNewEleParent();
	void minHeapify(HeapNode* ptr);
	void decreasekey(HeapNode *ptr);
	void preorder(HeapNode *ptr);
	string preorderString(HeapNode *ptr);
	string getBinary(int num);
	int convertStringToInt(string str);
	
	//debug img variables
	//string in graphviz for entire tree for debugging
	string get_debug_graph_string();
	//string in graphviz for single node for debugging
	static string get_debug_graph_string(HeapNode* node,map<HeapNode*,string> &node_names);
	//node name in graphviz
	static string get_debug_node_name(HeapNode* node);
	//node string in graphviz
	static string get_debug_node_string(HeapNode* node);
	//add node vertex in graph and map
	static string add_node_graph_map(HeapNode* node,map<HeapNode*,string> &node_names);
		
};
