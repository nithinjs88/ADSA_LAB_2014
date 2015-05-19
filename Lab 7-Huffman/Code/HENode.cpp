#include "HENode.h"
#include<bits/stdc++.h>
using namespace std;
#define LESSER -1
#define EQUAL 0
#define GREATER 1
#define OFFSET 20

	HENode::HENode() {
		this->frequency = 0;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
	}
	
	char HENode:: get_character() {
		return character;
	}

	void HENode::set_character(char ch) {
		this->character = ch;
	}

	int HENode:: get_frequency() {
		return frequency;
	}

	void HENode::set_frequency(int freq) {
		this->frequency = freq;
	}
	
	string HENode::get_code() {
		return code;
	}
	
	void HENode::set_code(string code) {
		this->code = code;
	}
	
	void HENode::set_left(HENode *leftnode) {
		this->left = leftnode;
	}
	
	HENode* HENode:: get_left() {
		return left;
	}
	
	void HENode::set_right(HENode *rightnode) {
		this->right = rightnode;
	}
	
	HENode* HENode:: get_right() {
		return right;
	}
	
	void HENode::set_parent(HENode *parent) {
		this->parent = parent;
	}
	
	HENode* HENode:: get_parent() {
		return parent;
	}
	
	int HENode::compare_to(HENode *compare) {
		int comp_freq = compare->frequency;
		//int compId = compare->getJobId();
		if(frequency < comp_freq) {
			return LESSER;	
		} else if(frequency == comp_freq) {
			return EQUAL;
		} else {
			return GREATER;
		}
	}
	
	/*
	bool HENode::is_greater_than(HENode *node1,HENode *node2) {
		return node1->compare_to(node2) == GREATER;
	}
	*/
	/*
	void HENode::swapValues(HENode* ptr) {
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
	*/
	
	void HENode::init_from_string(string line) {
		string char_str;
		istringstream iss;
		iss>>char_str;
		if(char_str == "space") {
			character = ' ';
		} else if(char_str == "\\n") {
			character = '\n';
		} else if(char_str == "\\t") {
			character = '\t';
		} else if(char_str == "\\r") {
			character = '\r';
		} else {
			character = char_str.at(0);
		}
		iss>>frequency>>code;
	}
	
	string HENode::get_string() {
		//cout<<"ch:"character<<" freq:"<<frequency<<" code:"<<code<<endl;
		ostringstream oss;
		string str_ch;
		switch(character) {
			case '\n':
				str_ch = "\\n";
				break;
			case '\t':
				str_ch = "\\t";
				break;
			case '\r':
				str_ch = "\\r";
				break;
			case ' ':
				str_ch = "space";
				break;
			default:
				str_ch = character;
		}
		//dont change the below lines
		str_ch.append(OFFSET - str_ch.length(),' ');
		oss<<str_ch;
				
		ostringstream freq_stream;
		freq_stream <<frequency;
		string freq_str;
		freq_str.append(freq_stream.str());
		freq_str.append(OFFSET - freq_stream.str().length(),' ');
		
		str_ch.append(OFFSET - str_ch.length(),' ');
		oss<<freq_str<<"\t"<<code<<endl;
		return oss.str();
	}
	
	/*
	void HENode::sort(vector<HENode*> &nodes) {
		std::sort (nodes.begin(), nodes.end());
	}
	
	
	bool HENode::operator<(HENode node2) const {
		bool flag = (frequency > node2.frequency);
		return flag;	
       return weight > other.weight;
    }
    */

