#include<bits/stdc++.h>
#include "HENode.h"
using namespace std;

class Huffman{
	
public:
	Huffman();
	void set_input_file(string input_file);
	void set_map_file(string map_file);
	void set_output_file(string output_file);
	void set_code_file(string code_file);
	void set_mode(int mode);
	void execute();
	
	
private:
	string input_file;
	string map_file;
	string output_file;
	string code_file;
	int mode;
	
	map<char,HENode*> char_node_map;
	map<string,HENode*> code_node_map;
	vector<HENode*> nodes;
	
	void encode();
	void decode();
	void read_input_text_file();
	void write_map_file();
	void sort();
	/*
	void sort_nodes();
	bool is_greater_than(HENode *node1,HENode *node2);
	*/
};
