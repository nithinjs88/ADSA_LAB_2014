#include "MinHeap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

string heapSort(MinHeap minHeap){
	ostringstream oss("");
	HeapNode*ptr = minHeap.extractMin();
	while(ptr !=NULL) {
		oss<<ptr->getJobId();
		oss<<" ";
		oss<<ptr->getPriority();
		oss<<" ";
		oss<<ptr->getDuration();
		oss<<" ";	
		oss<<endl;
		ptr = minHeap.extractMin();
	}
	cout<<"heap sort over"<<endl;
	cout <<oss.str()<<endl;
	return oss.str();	
}

int main(int argc,char*argv[]) {
	if(argc !=3) {
		cout<<"Error Incorrect Syntax"<<endl;
	} else {
		string inputFile = argv[1];
		string outputFile = argv[2];
		MinHeap minHeap;
		ifstream in;
		int noOfArgs = 0,jobId,priority,duration;	
		string fileLine;
		in.open(inputFile.c_str());
		in >> noOfArgs;
		//dout<<" total args is "<<noOfArgs<<endl;
	//while (!in.eof()) {
		for(int i=0;i<noOfArgs;i++) {
			in >>jobId>>priority>>duration;
			//cout<<" arg "<<jobId<<" "<<priority<<" "<<duration<<endl;
			//cout<<"insertingggggggg......"<<endl;
			//dout<<" i is "<<
			HeapNode *heapNode = new  HeapNode(jobId,priority,duration);
			minHeap.insertHeapNode(heapNode);
			//dout<<" heap is ==="<<endl;
			//preorder();
			//dout<<" heap print over"<<endl;
		}
	//}
	cout<<"Insert over"<<endl;
	minHeap.debug_image("debug_after_insert");
	ofstream myfile;
	myfile.open (outputFile.c_str());
 	
  	
	if(!in.eof()) {
		char ch;
		in>>ch;
		if(ch == 'P'){	
		string str = minHeap.preorderString();
		cout<<"preorderString is "<<	str<<endl;
		myfile << str<<"\n";
		}
	}
	string hs = heapSort(minHeap);
	myfile << hs;
	myfile.close();
	in.close();
	//dout<<"At last"<<endl;
	//preorder();
	}
}


