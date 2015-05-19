#include "Node.h"
#include "BST.h"

//Following lines say that these functions are implemented 
//in some other file.
extern int isEqualNode(Node* n1, Node* n2);
extern int isEqualBST (BST T1, BST T2);
extern int isEquivBST (BST T1, BST T2);

int populateTree(BST &T, char *filename) {
	
	// Given a BST and a filename, reads the lines in the file
	// and populates a BST. Returns the number of nodes successfully added
	// to BST.
	ifstream fin;
	fin.open(filename);
	int id, priority, duration;
	fin >> id >> priority >> duration;
	int count = 0;
	while (!fin.eof()) {
		Node* node = new Node(id, priority, duration);
		if (T.insert(node))  {
			count++;
		}
		fin >> id >> priority >> duration;
	}
	fin.close();
	return count;
}
int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Invalid number of arguments.\nUsage: " << argv[0] << " <filename1> <filename2>\n";
		return 1;
   	}
    	BST T1, T2; 

	populateTree(T1, argv[1]);

	populateTree(T2, argv[2]);
 	std::cout <<"Printing tree T1 \n";
	T1.printTree();
 	std::cout <<"Printing tree T2 \n";
	T2.printTree();
	
	isEqualBST(T1, T2);
	isEquivBST(T1, T2);
	

}

