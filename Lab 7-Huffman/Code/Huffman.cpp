#include<bits/stdc++.h>
//#include <HENode.h>
#include "Huffman.h"
#define ENCODE_MODE 0
#define DECODE_MODE 1
#define LESSER -1
#define EQUAL 0
#define GREATER 1
#define OFFSET 20

using namespace std;

	Huffman::Huffman() {
	}
	
	void Huffman::set_input_file(string input_file) {
		this->input_file = input_file;
	}
	
	void Huffman::set_map_file(string map_file) {
		this->map_file = map_file;
	}
	
	void Huffman::set_output_file(string output_file) {
		this->output_file = output_file;
	}
	
	void Huffman::set_code_file(string code_file) {
		this->code_file = code_file;
	}
	
	void Huffman::set_mode(int mode) {
		this->mode = mode;
	}
	
	
	void Huffman::execute() {
		switch(mode) {
			case ENCODE_MODE:
				encode();
				break;
			case DECODE_MODE:
				decode();
				break;
		}
	}
	
	void Huffman::encode() {
		read_input_text_file();
		sort();
		write_map_file();
	}
	
	void Huffman::sort() {
		for(int i = 0;i< nodes.size() -1;i++) {
			for(int j = i+1;j< nodes.size() ;j++) {
				HENode* node1 = nodes[i];
				HENode* node2 = nodes[j];
				int compare = node1->compare_to(node2);
				if(compare == LESSER) {
					nodes[i] = node2;
					nodes[j] = node1;
				}
			}
		}
	}
	
	void Huffman::write_map_file() {
		ofstream myfile;
		myfile.open (map_file.c_str());
		
		string header_line;
		header_line.append(3*OFFSET,'-');
		header_line.append(1,'\n');
		
		string title_line;
		title_line.append("character");
		title_line.append(OFFSET - title_line.length(),' ');
		title_line.append("frequency");
		title_line.append(2*OFFSET - title_line.length(),' ');
		title_line.append("code");
		myfile<<header_line<<title_line<<endl<<header_line;
		
		for(int i=0;i<nodes.size();i++) {
			myfile<<nodes.at(i)->get_string();
		}
		myfile.close();
	}
	
	void Huffman::read_input_text_file() {
		ifstream in;
		in.open(input_file.c_str());
		char ch;
		HENode* he_node;
		while(!in.eof()) {
			char ch = in.get();
			if(ch == 0 || ch== -1)
				continue;
			he_node = char_node_map[ch];
			if(he_node == NULL) {
				he_node = new HENode();
				he_node->set_character(ch);
				he_node->set_frequency(1);
				nodes.push_back(he_node);
				char_node_map[ch]=he_node;
			} else {
				he_node->set_frequency(he_node->get_frequency() + 1);
			}
		}
		in.close();
	}
	
	void Huffman::decode() {
	}
	
	/*
	bool Huffman::is_greater_than(HENode *node1,HENode *node2) {
		return node1->compare_to(node2) == GREATER;
	}
	
	void Huffman::sort_nodes() {
		std::sort (nodes.begin(), nodes.end(), is_greater_than);
	}
	*/
	
	
	
