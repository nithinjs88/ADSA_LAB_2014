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

class MaxHeap {
		
	private:
	int *heapPtr;
	int size;
	int maxCapacity;
	void heapify(int index);
	void buildHeap();
	static int getParentIdx(int idx);
	static int getLeftChildIdx(int idx);
	static int getRightChildIdx(int idx);
	bool isValidIdx(int idx);
	void swap(int idx1,int idx2);
	int getMax();
	int extractMax();
	void increaseKey(int index,int newKey);
	void insert(int ele);
	static void error(string msg);
	
	public:
	void read(string inputFile,string testFile);
	void print();
};

int MaxHeap::getMax() {
	if(size == 0)
		throw "heap is empty";
	return heapPtr[0];
}

int MaxHeap::extractMax() {
	if(size == 0)
		throw "heap is empty";
	 int ele = heapPtr[0];
	 swap(0,size-1);
	 size--;
	 heapify(0);
	 return ele;
}
int MaxHeap::getParentIdx(int idx) {
	return ((idx + 1)/2)-1;
}

int MaxHeap::getLeftChildIdx(int idx) {
	return (idx*2)+1;
}

int MaxHeap::getRightChildIdx(int idx) {
	return ((idx + 1)*2);
}

void MaxHeap::buildHeap() {
	int startIdx = ((size + 1)/2)-1;
	for(int i=startIdx;i>=0;i--) {
		heapify(i);
	}
}

bool MaxHeap::isValidIdx(int idx) {
		return idx <=(size-1);
}

void MaxHeap::swap(int idx1,int idx2) {
	int temp = heapPtr[idx1];
	heapPtr[idx1] = heapPtr[idx2];
	heapPtr[idx2] = temp;
}
void MaxHeap::heapify(int index){
	int eleAtIdx = heapPtr[index];
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
				heapify(leftIdx);
			}
		}
	}
}

void MaxHeap::increaseKey(int idx,int newKey) {
	int oldKey = heapPtr[idx];
	if(newKey <= oldKey) {
		throw "Cannot increase key";
	} else {
		int parentIdx = getParentIdx(idx);
		int parentKey = heapPtr[parentIdx];
		heapPtr[idx] = newKey;
		int keyItr = newKey;
		while(parentIdx>=0 && parentKey < keyItr ) {
			dout15<<"start: parKey "<<parentKey<< " parIdx"<<parentIdx<<" curKey "<<keyItr<<" curIdx "<<idx<<endl;
			swap(parentIdx,idx);
			idx = parentIdx;
			parentIdx = getParentIdx(parentIdx);
			keyItr = heapPtr[idx];
			parentKey = heapPtr[parentIdx];
			dout15<<"end: parKey "<<parentKey<< " parIdx"<<parentIdx<<" curKey "<<keyItr<<" curIdx "<<idx<<endl;
		}
	}	
}

void MaxHeap::insert(int ele) {
	
	if(size >= maxCapacity) {
		maxCapacity = 2*maxCapacity;
		int newArray[maxCapacity];
		for(int i=0;i<size;i++) {
			newArray[i] = heapPtr[i];
		}
		delete(heapPtr);
		heapPtr = newArray;
		dout<<"heap resized "<<" size "<<size<<" maxCap "<<maxCapacity;
	}
	int minEle = 1<<( sizeof(int)*8 - 1);
	dout<<minEle<<endl;
	heapPtr[size] = minEle;
	size = size + 1;
	dout<<"size "<<size<<" cap "<<maxCapacity<<endl;
	increaseKey(size-1,ele);
}

void MaxHeap::read(string inputFile,string testFile) {
	ifstream in;
	string fileLine;
	in.open(inputFile.c_str());
	vector<int> elements;
	int elementItr;
	while (getline(in, fileLine)) {
		istringstream iss;
		iss.str(fileLine);
		dout<<fileLine<<endl;
		while(iss >> elementItr) {
			elements.push_back(elementItr);
		}
	}
	in.close();
	int size = elements.size();
	dout<<"No of elements is"<<size;
	dout<<endl;
	int maxCapacity = size + 10;
	int array[maxCapacity];
	for(int i=0;i<size;i++) {
		array[i] = elements.at(i);
	}
	heapPtr = array;
	this->size = size;
	this->maxCapacity=maxCapacity;
	buildHeap();
	ifdebug print();
	
	vector<string> strings;
	string stringItr;
	in.open(testFile.c_str());
	while (getline(in, fileLine)) {
		istringstream iss;
		iss.str(fileLine);
		dout<<fileLine<<endl;
		strings.clear();
		while(iss >> stringItr) {
			strings.push_back(stringItr);
		}
		int stringSize = strings.size();
		if(stringSize > 0) {
			string command = strings.at(0);
			bool isError = false;
			string errorMsg = "";
			if(command == GET_MAX) {
				if(stringSize == 1) {
					int max = getMax();
					cout<<"Max element is "<<max<<endl;
				} else {
					isError = true;
					errorMsg.append("Invalid form of ");
					errorMsg.append(GET_MAX);
				}
			} else if(command == EXTRACT_MAX) {
				if(stringSize == 1) {
					int max = extractMax();
					cout<<"Extracted Max element is "<<max<<endl;
				} else {
					isError = true;
					errorMsg.append("Invalid form of ");
					errorMsg.append(EXTRACT_MAX);
				}
			} else if(command == INCREASE_KEY) {
				if(stringSize == 3) {
					try {
						increaseKey(convertStringToInt(strings.at(1)),convertStringToInt(strings.at(2)));
					} catch (int e) {
						isError = true;
						errorMsg.append("Invalid format of ");
						errorMsg.append(INCREASE_KEY);
					}
				} else {
					isError = true;
					errorMsg.append("Invalid form of ");
					errorMsg.append(INCREASE_KEY);
				}
			} else if(command == INSERT) {
				if(stringSize == 2) {
					try {
						insert(convertStringToInt(strings.at(1)));
					} catch (int e) {
						isError = true;
						errorMsg.append("Invalid format of ");
						errorMsg.append(INSERT);
					}
				} else {
					isError = true;
					errorMsg.append("Invalid form of ");
					errorMsg.append(INCREASE_KEY);
				}
			} else {
				isError = true;
				errorMsg = "Invalid command";
				
			}
			dout<<"Heap is ";
			ifdebug print();
			if(isError) {
				error(errorMsg);
			}
		}
	}
	in.close();
}

void MaxHeap::print() {
	for(int i=0;i<size;i++) {
		cout<<(*(heapPtr+i))<<" ";
	}
	cout<<endl;
}
void MaxHeap::error(string message) {
	cout<<"ERROR: "<<message<<endl;
}

int main(int argc,char*argv[]) {
	if(argc != 3) {
		cout<<"Invalid arguments: Correct syntax <input_file> <test_file>";
		return -1;
	}
	MaxHeap maxHeap;
	maxHeap.read(argv[1],argv[2]);
	return 0;
}
