#include "HeapNode.h"
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
		
};
