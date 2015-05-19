#include<bits/stdc++.h>
#include "MinHeap.h"
//#include "HeapNode.h"
//#include "common_functions.cpp"

using namespace std;
#define DEBUG 1
#define dout	if (DEBUG) cout
#define dout15	if (DEBUG && newKey==15) cout
#define ifdebug if (DEBUG)

MinHeap::MinHeap() {
		root=NULL;
		tail=NULL;
		size=0;
}

MinHeap::~MinHeap() {
	
}


void MinHeap::minHeapify(HeapNode* ptr){
	if(ptr != NULL) {
		HeapNode* leftNode = ptr->getLeft();
		HeapNode* rightNode = ptr->getRight();
		if(leftNode !=NULL && rightNode!=NULL) {
			if(leftNode->isLessThan(ptr) && leftNode->isLessThan(rightNode))	{
				leftNode->swapValues(ptr);
				minHeapify(leftNode);
			} else if(rightNode->isLessThan(ptr) && rightNode->isLessThan(leftNode))	{
				rightNode->swapValues(ptr);
				minHeapify(rightNode);
			} else {
				//no change
			}
		} else if(leftNode !=NULL) {
			if(leftNode->isLessThan(ptr)){
				leftNode->swapValues(ptr);
				minHeapify(leftNode);	
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
	}	
	//return str;
	
}

string MinHeap::preorderString() {
	//dout<<" preorder start "<<endl;
	return preorderString(this->root);
	//dout<<" preorder end "<<endl;
}

string MinHeap::preorderString(HeapNode *ptr) {
	ostringstream oss("");
	if(ptr != NULL) {
		oss<<ptr->getJobId();
		oss<<" ";
		oss<<ptr->getPriority();
		oss<<" ";
		oss<<ptr->getDuration();
		oss<<" ";
		oss<<endl;	
		oss<<preorderString(ptr->getLeft());
		oss<<preorderString(ptr->getRight());
	}
	return oss.str();
/*
	string str="";	
	if(ptr != NULL) {
			
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
*/
	
}
/*
string MinHeap::heapSort(){
	string str="";	
	while(true) {
		HeapNode*min = extractMin();
		if(min == NULL)
			break;		
		str.append(convertIntToString(min->getJobId()));
		str.append(" ");
		str.append(convertIntToString(min->getPriority()));
		str.append(" ");
		str.append(convertIntToString(min->getDuration()));
		str.append("\n");
	}
	return str;	
}
*/



HeapNode* MinHeap:: extractMin(){
	if(size == 0) {
		return NULL;
	}
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
/*
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
*/
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

/*
 * debug imaging starts
 */
void MinHeap:: debug_image(string file_name) {
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

string MinHeap::get_debug_graph_string(){
	ostringstream oss("");
	oss<<("digraph G { ");
	oss<<endl;
	//oss<<"\t"<<"size =\"6,6\";"<<endl;
	oss<<"\t"<<"edge[arrowhead=normal,arrowtail=none]"<<endl<<endl;
	
	queue<HeapNode*> bfs_queue;
	if(root != NULL)
		bfs_queue.push(root);
	HeapNode* ptr;
	map<HeapNode*,string> node_names;
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

string MinHeap::get_debug_graph_string(HeapNode* node,map<HeapNode*,string> &node_names) {
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
	HeapNode* parent = node->getParent();
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
	HeapNode* left_child = node->getLeft();
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
	HeapNode* right_child = node->getRight();
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

string MinHeap:: add_node_graph_map(HeapNode* node,map<HeapNode*,string> &node_names) {
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
string MinHeap:: get_debug_node_name(HeapNode* node){
	if(node == NULL)
		return "";
	ostringstream node_name_oss("");
	node_name_oss << "node" << node->getJobId();
	//dout<<"debug_node_name is "<<node_name_oss.str()<<endl;
	return node_name_oss.str();
}

string MinHeap:: get_debug_node_string(HeapNode* node){
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



