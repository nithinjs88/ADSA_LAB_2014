#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//#include "common_functions.cpp"
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

	HeapNode(int jobId,int priority,int duration) {
		this->jobId = jobId;
		this->priority = priority;
		this->duration = duration;
		this->left = NULL;
		this->right= NULL;
	}
	
	int getJobId() {
		return jobId;
	}
	int getPriority() {
		return priority;
	}
	int getDuration() {
		return duration;
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
	
	bool isLessThan(HeapNode *compare) {
		int compPrior = compare->getPriority();
		int compId = compare->getJobId();
		if(priority < compPrior) {
			return true;	
		} else if(priority == compPrior) {
			return jobId < compare->getJobId();
		} else {
			return false;
		}
	}

	void swapValues(HeapNode* ptr) {
		int tempJobId = this-> jobId;
		this->jobId = ptr->jobId;
		ptr->jobId = tempJobId;

		int tempPriority = this-> priority;
		this->priority = ptr->priority;
		ptr->priority = tempPriority;

		int tempDuration = this-> duration;
		this->duration = ptr->duration;
		ptr->duration = tempDuration;
	}
	
private:
	
	int jobId;
	int priority;
	int duration;	
	HeapNode *left;
    	HeapNode *right;
    	HeapNode *parent;
};

class MinHeap {
	
public:
	MinHeap() {
		root=NULL;
		tail=NULL;
		size=0;	
	}
	void insertHeapNode(HeapNode* ptr);
	void read(string inputFile,string outputFile);
	string convertIntToString(int num);
	string getBinary(int num);
	int convertStringToInt(string str);
	HeapNode* extractMin();
	string heapSort();

private:
	HeapNode* root;
	HeapNode* tail;
	HeapNode* getNewEleParent();
	void minHeapify(HeapNode* ptr);
	int size;
	void decreasekey(HeapNode *ptr);
	void preorder();
	void preorder(HeapNode *ptr);
	string preorderString();
	string preorderString(HeapNode *ptr);

	
};

void MinHeap::minHeapify(HeapNode* ptr){
	if(ptr != NULL) {
		HeapNode* leftNode = ptr->getLeft();
		HeapNode* rightNode = ptr->getRight();
		if(leftNode !=NULL && rightNode!=NULL) {
			if(leftNode->isLessThan(ptr) && leftNode->isLessThan(rightNode))	{
				leftNode->swapValues(ptr);
			} else if(rightNode->isLessThan(ptr) && rightNode->isLessThan(leftNode))	{
				rightNode->swapValues(ptr);
			} else {
				//no change
			}
		} else if(leftNode !=NULL) {
			if(leftNode->isLessThan(ptr)){
				leftNode->swapValues(ptr);			
			}		
		}
		
	}
}
HeapNode* MinHeap:: getNewEleParent() {
	if(tail != NULL) {
		HeapNode* ptr = root;
		//int num = getBinary(size);
		string str = getBinary(size);
		//dout<<" size is "<<size<<" bin is "<<str<<endl;		
		if(str.size() > 1) {
			for(int i=1;i<str.size()-1;i++) {
				char ch = str.at(i);
				if(ch == 48) {
					ptr = ptr->getLeft();
				} else if(ch == 49){
					ptr = ptr->getRight();
				}
				//dout<<" In getNewEleParent "<<size<<" ptr is "<<ptr->getJobId()<<endl;
				fflush(stdout);
			}
			return ptr;
		} else {
			return root;
		}
	}
}

void MinHeap::decreasekey(HeapNode *ptr) {
	HeapNode *parent = ptr->getParent();
	dout<<" In decreasekey of ptr "<<ptr->getJobId()<<endl;
	dout<<" parent for dec key is "<<parent->getJobId()<<endl;
	while(parent!=NULL && ptr->isLessThan(parent)) {
		dout<<" parent is "<<parent->getJobId()<<" ptr is "<<ptr->getJobId()<<endl;
		parent->swapValues(ptr);
		dout<<" After swapping parent is "<<parent->getJobId()<<" ptr is "<<ptr->getJobId()<<endl;
		ptr = parent;
		parent = parent->getParent();		
	}
}
void MinHeap::insertHeapNode(HeapNode* ptr){
	if(root == NULL) {
		root = tail = ptr;
		size++;
	} else {
		size++;
		dout<<"size is "<<size<<endl;
		HeapNode* parent = getNewEleParent();
		dout<<" parent is "<<parent->getJobId()<<endl;
		if(size %2 == 1) {
			dout<<"point to right"<<endl;
			parent->pointToRight(ptr);
		} else {
			dout<<"point to left"<<endl;
			parent->pointToLeft(ptr);
		}
		ptr->pointToParent(parent);
		decreasekey(ptr);
		tail = ptr;
	}
}

void MinHeap::preorder() {
	dout<<" preorder start "<<endl;
	preorder(this->root);
	dout<<" preorder end "<<endl;
}

void MinHeap::preorder(HeapNode *ptr) {
	//string str="";	
	if(ptr != NULL) {
		cout<<ptr->getJobId()<<" "<<ptr->getPriority()<<" "<<ptr->getDuration();
		cout<<endl;
		preorder(ptr->getLeft());
		preorder(ptr->getRight());
		/*
		str.append(convertIntToString(ptr->getJobId()));
		str.append(" ");
		str.append(convertIntToString(ptr->getPriority()));
		str.append(" ");
		str.append(convertIntToString(ptr->getDuration()));
		str.append("\n");

		str.append(preorder(ptr->getLeft()));
		str.append(preorder(ptr->getRight()));
		*/
	}	
	//return str;
	
}

string MinHeap::preorderString() {
	//dout<<" preorder start "<<endl;
	return preorderString(this->root);
	//dout<<" preorder end "<<endl;
}

string MinHeap::preorderString(HeapNode *ptr) {
	string str="";	
	if(ptr != NULL) {
	//	cout<<ptr->getJobId()<<" "<<ptr->getPriority()<<" "<<ptr->getDuration();
	//	cout<<endl;
	//	preorder(ptr->getLeft());
	//	preorder(ptr->getRight());
		
		str.append(convertIntToString(ptr->getJobId()));
		str.append(" ");
		str.append(convertIntToString(ptr->getPriority()));
		str.append(" ");
		str.append(convertIntToString(ptr->getDuration()));
		str.append("\n");

		str.append(preorderString(ptr->getLeft()));
		str.append(preorderString(ptr->getRight()));
		
	}	
	return str;
	
}

string MinHeap::heapSort(){
	string str="";	
	while(size !=0) {
		HeapNode*min = extractMin();
		str.append(convertIntToString(min->getJobId()));
		str.append(" ");
		str.append(convertIntToString(min->getPriority()));
		str.append(" ");
		str.append(convertIntToString(min->getDuration()));
		str.append("\n");
	}
	return str;	
}




HeapNode* MinHeap:: extractMin(){
	root->swapValues(tail);
	size--;
	HeapNode* min = tail;
	HeapNode* parent = tail->getParent();
	if(parent != NULL) {
		if(size %2 == 0) {
			tail->getParent()->pointToRight(NULL);	
		} else {
			tail->getParent()->pointToLeft(NULL);
		}
	}
	string str = getBinary(size);
		HeapNode* ptr = root;
		//dout<<" size is "<<size<<" bin is "<<str<<endl;		
		if(str.size() > 1) {
			for(int i=1;i<str.size();i++) {
				char ch = str.at(i);
				if(ch == 48) {
					ptr = ptr->getLeft();
				} else if(ch == 49){
					ptr = ptr->getRight();
				}
				//dout<<" In getNewEleParent "<<size<<" ptr is "<<ptr->getJobId()<<endl;
				fflush(stdout);
			}
			tail= ptr;
		} else {
			tail= root;
		}
	minHeapify(root);
	return min;
}
void MinHeap::read(string inputFile,string outputFile) {
	ifstream in;
	int noOfArgs = 0,jobId,priority,duration;	
	string fileLine;
	in.open(inputFile.c_str());
	in >> noOfArgs;
	dout<<" total args is "<<noOfArgs<<endl;
	//while (!in.eof()) {
		for(int i=0;i<noOfArgs;i++) {
			in >>jobId>>priority>>duration;
			cout<<" arg "<<jobId<<" "<<priority<<" "<<duration<<endl;
			cout<<"insertingggggggg......"<<endl;
			//dout<<" i is "<<
			HeapNode *heapNode = new  HeapNode(jobId,priority,duration);
			insertHeapNode(heapNode);
			dout<<" heap is ==="<<endl;
			//preorder();
			dout<<" heap print over"<<endl;
		}
	//}
	ofstream myfile;
	myfile.open (outputFile.c_str());
 	
  	
	if(!in.eof()) {
		char ch;
		in>>ch;
		if(ch == 'P'){	
		string str = preorderString();
		dout<<"preorderString is "<<	str<<endl;
		myfile << str<<"\n";
		}
	}
	string hs = heapSort();
	myfile << hs;
	myfile.close();
	in.close();
	dout<<"At last"<<endl;
	//preorder();
	
}

string MinHeap::convertIntToString(int num) {
	string str = "";
	bool isPos = true;
	if(num < 0 )
		isPos = false;
	int remainder;
	while(num != 0) {
		remainder = num%10;
		char ch = remainder+48;
		str.insert(0,1,ch);
		num = num/10;
	}
	if(!isPos)
		str.insert(0,1,'-');
	return str;
}

string MinHeap:: getBinary(int num) {
	string binary = "";
	int rem = 0;
	char ch;
	while(num>0) {
		rem = num %2;
		ch = 48+rem;
		binary.insert(0,1,ch);
		num = num /2; 
	}
	return binary;
}
int MinHeap:: convertStringToInt(string str) {
	if(str.empty()) {
		throw -1;
	}
	int convertInt = 0;
	int length = str.length();
	char firstChar = str.at(0);
	bool ignoreFirstChar = true;
	bool isPositive = true;
	if(firstChar == '-') {
		isPositive = false;
	} else if(firstChar == '+') {
		
	} else if(firstChar >=48 && firstChar <=57){
		ignoreFirstChar = false;
	} else {
		throw -1;
	}
	int startLimit = 0;
	if(ignoreFirstChar == true) {
		startLimit = 1;
	}
	char charItr;
	for(int i = startLimit;i<length;i++) {
		charItr = str.at(i);
		if(charItr >=48 && charItr <=57) {
			convertInt = convertInt*10 + (charItr - 48);
		} else {
			throw -1;
		}
	}
	return isPositive ? convertInt : -convertInt;
}

int main(int argc,char*argv[]) {
	MinHeap minHeap;
	minHeap.read(argv[1],argv[2]);
	
}
