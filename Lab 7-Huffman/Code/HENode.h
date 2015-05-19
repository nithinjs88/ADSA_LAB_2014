#include<bits/stdc++.h>
using namespace std;
class HENode {

public:
	HENode();
	char get_character();
	void set_character(char ch);
	int get_frequency();
	void set_frequency(int freq);
	string get_code();
	void set_code(string code);
	
	void set_left(HENode *left_node);
	HENode* get_left();
	void set_right(HENode *right_node);
	HENode* get_right();
	void set_parent(HENode *parent_node);
	HENode* get_parent();
	
	int compare_to(HENode *compare);
	//void swap_values(HENode* ptr);
	string get_string();
	
	//for sorting
	//void sort(vector<HENode*> &nodes);
	//bool operator<(HENode node2) const ;
	//static bool is_greater_than(HENode *node1,HENode *node2);
	
	void init_from_string(string line);
private:
	
	char character;
	int frequency;
	string code;
	HENode* left;
   	HENode* right;
  	HENode* parent;

};
	
	
	
	
	
