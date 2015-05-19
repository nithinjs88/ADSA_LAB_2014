#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "common_functions.cpp"
using namespace std;
#define DEBUG 1
#define dout	if (DEBUG) cout
#define dout15	if (DEBUG && newKey==15) cout
#define ifdebug if (DEBUG)
#define GET_MAX "getmax"
#define EXTRACT_MAX "extractmax"
#define INCREASE_KEY "increasekey"
#define INSERT "insert"

class HeapNode {

public:

	HeapNode(int id, string &name) {
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
	void pointToLeft(HeapNode *leftnode) {
		this->left = leftnode;
	}
	HeapNode *getLeft() {
		return left;
	}
	void pointToRight(HeapNode *rightnode) {
		this->right = rightnode;
	}
	HeapNode *getRight() {
		return right;
	}
	
	void pointToParent(HeapNode *parentnode) {
		this->parent = parentnode;
	}
	HeapNode *getParent() {
		return parent;
	}
	
private:
	string name;
	int id;
	HeapNode *left;
    HeapNode *right;
    HeapNode *parent;
};

class MaxHeap {
	
public:
	void insertHeapNode(HeapNode* ptr);

private:
	HeapNode* root = NULL;
	HeapNode* tail = NULL;
	HeapNode* getNewEleParent();
	void maxHeapify(HeapNode* ptr);
	int size = 0;
};

void maxHeapify(HeapNode* ptr){
	if(ptr != null) {
		int eleAtIdx = ptr->getId();
		if(ptr->getLeft() && ptr->getRight()) {
			int leftEle = ptr->getLeft()->getId();
			int rightEle = ptr->getRight()->getId();
			if(leftEle >eleAtIdx && leftEle>=rightEle) {
				
			} else if(rightEle >eleAtIdx && rightEle>=leftEle) {
				
			}
		}
	int leftIdx = getLeftChildIdx(index);
	int rightIdx = getRightChildIdx(index);
	if(isValidIdx(leftIdx)) {
		if(isValidIdx(rightIdx)) {
			int maxIdx = index;
			if(heapPtr[leftIdx] > eleAtIdx) {
				maxIdx = leftIdx;
			}
			if(heapPtr[rightIdx] > heapPtr[maxIdx]) {
				maxIdx = rightIdx;
			}
			if(maxIdx != index) {
				swap(maxIdx,index);
				heapify(maxIdx);
			}
		} else {
			if(heapPtr[leftIdx] > eleAtIdx) {
				swap(index,leftIdx);
			}
		}
	}
	}
}
HeapNode* MaxHeap:: getNewEleParent() {
	if(tail != null) {
		HeapNode* ptr = root;
		int num = getBinary(size);
		string str = convertIntToString(num);
		if(str.size() > 1) {
			for(int i=1;i<str.size()-1;i++) {
				char ch = str.at(i);
				if(ch == 48) {
					ptr = ptr->left;
				} else if(ch == 49){
					ptr = ptr->right;
				}
				return ptr;
			}
		} else {
			return root;
		}
	}
}
void MaxHeap::insertHeapNode(HeapNode* ptr){
	if(root == NULL) {
		root = tail = ptr;
	} else {
		HeapNode* parent = getNewEleParent();
		if(size %2 == 0) {
			parent.setRight(ptr);
		} else {
			parent.setLeft(ptr);
		}
		ptr.setParent(parent);
	}
	size++;
	
}

}

int main(int argc,char*argv[]) {
	
	
}
