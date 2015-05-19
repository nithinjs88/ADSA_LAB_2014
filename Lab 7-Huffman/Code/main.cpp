#include<bits/stdc++.h>
#include "Huffman.h"
using namespace std;
#define DEBUG 1
#define dout if(DEBUG) cout
#define debug if(DEBUG)
#define ENCODE_MODE 0
#define DECODE_MODE 1

void error(string msg) {
	cout<<"ERROR: "<<msg<<endl;
}

int main(int argc,char *argv[]) {
		if(argc == 1) {
			error("Invalid no of arguments");
			return -1;
		}
		string input_file="",map_file="",output_file="",code_file="";
		int mode = ENCODE_MODE;
		for(int i=0;i<argc;i++) {
			string arg = argv[i];
			//dout<<argv[i]<<endl;
			if("-c" == arg) {
				input_file.append(argv[i+1]);
				//cout<<"input_file"<<input_file<<endl;
			} else if("-m" == arg) {
				map_file.append(argv[i+1]);
				//cout<<"test_file"<<test_file<<endl;
			} else if("-o" == arg) {
				output_file.append(argv[i+1]);
				//cout<<"test_file"<<test_file<<endl;
			} else if("-d" == arg) {
				code_file.append(argv[i+1]);
				int mode = DECODE_MODE;
				//cout<<"test_file"<<test_file<<endl;
			} else {
				//dout<<"not eq"<<endl;
			}
		}
		dout<<input_file<<endl;
		dout<<map_file<<endl;
		dout<<output_file<<endl;
		dout<<code_file<<endl;
		
		Huffman* huffman = new Huffman();
		huffman->set_input_file(input_file);
		huffman->set_map_file(map_file);
		huffman->set_output_file(output_file);
		huffman->set_code_file(code_file);
		huffman->set_mode(mode);
		
		
		huffman->execute();
		return 0;
				
}
