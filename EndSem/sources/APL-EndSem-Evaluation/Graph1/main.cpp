#include "BinaryTree.cpp"
		
extern bool isAncestor(BinaryTree tree, int anc, int desc);

extern int LCA(BinaryTree tree, int n1, int n2);

extern int subTreeSize(BinaryTree tree, int node);

extern bool isBalanced(BinaryTree tree, int node);

extern int diameter(BinaryTree tree);
	
int main(int argc, char** argv) {
	
	BinaryTree tree;
	
	 if (argc != 3) {
                std::cout << "Invalid number of arguments.\nUsage: " << argv[0] << " <inputFile> <outFile>\n";
                return 1;
        }

	tree.readFile(argv[1]);
	tree.DFS();
	tree.gvout(argv[2]);	
//	tree.printPre();
//	tree.printPost();
	

//	cout << "Pre" << endl;
	if (tree.isPre())
		cout << "PreOrder correct ----------------####### + 1.5 Marks" << endl;
	else
		cout << "PreOrder incorrect ----------------####### + 0 Marks" << endl;

//	cout << "Post" << endl;
	if (tree.isPost())
		cout << "PostOrder correct ----------------####### + 1.5 Marks" << endl;
	else
		cout << "PostOrder incorrect ----------------####### + 0 Marks" << endl;
	
	int u = 0;
	if (tree.getHeight(1) == 7)
		u++;
	
	if (tree.getHeight(64) == 1)
		u++;
	cout << "Height Values ----------------####### +" << u << " Marks"<< endl;
//	cout << "isAncestor" << endl;
	cout << "************************************************************************" << endl;
/*
	cout << isAncestor(tree, 2, 256) << endl;
	cout << isAncestor(tree, 3, 256) << endl;

	
	cout << LCA(tree, 10, 256) << endl;
	cout << LCA(tree, 65, 256) << endl;	
	cout << LCA(tree, 3, 1024) << endl;
	
	cout << isBalanced(tree, 1) << endl;	
	cout << isBalanced(tree, 512) << endl;
	
	cout << subTreeSize(tree, 1) << endl;
	cout << subTreeSize(tree, 3) << endl;

*/
//	cout <<"Diameter of tree =" << diameter(tree) <<endl;

	bool h;
	cin >> h;
	if (isAncestor(tree, 2, 45) == h)
		cout << "isAncestor Case 1 correct ----------------####### + 0.25 Marks" << endl;
	else
		cout << "isAncestor Case 1 incorrect ----------------####### + 0 Marks" << endl;
	cin >> h;
	if (isAncestor(tree, 3, 45) == h)
		cout << "isAncestor Case 2 correct ----------------####### + 0.25 Marks" << endl;
	else
		cout << "isAncestor Case 2 incorrect ----------------####### + 0 Marks" << endl;
	cout << "CHECK MANUALLY, if both cases correct and isAncestor is a O(1) algo then award additional half mark"	<< endl;	
	
	cout << "************************************************************************" << endl;


	int h1;
	cin >> h1;
	if (LCA(tree, 62, 64) == h1)
		cout << "LCA Case 1 correct ----------------####### + 1 Marks" << endl;
	else
		cout << "LCA Case 1 incorrect ----------------####### + 0 Marks" << endl;
	
	cin >> h1;
	if (LCA(tree, 22, 47) == h1)
		cout << "LCA Case 2 correct ----------------####### + 1 Marks" << endl;
	else
		cout << "LCA Case 2 incorrect ----------------####### + 0 Marks" << endl;
	
	cin >> h1;
	if (LCA(tree, 5, 41) == h1)
		cout << "LCA Case 3 correct ----------------####### + 1 Marks" << endl;
	else
		cout << "LCA Case 3 incorrect ----------------####### + 0 Marks" << endl;
	
	
	cout << "************************************************************************" << endl;

	cin >> h;
	if (isBalanced(tree, 1) == h)
		cout << "isBalanced Case 1 correct ----------------####### + 0.5 Marks" << endl;
	else
		cout << "isBalanced Case 1 incorrect ----------------####### + 0 Marks" << endl;
	
	cin >> h;
	if (isBalanced(tree, 20) == h)
		cout << "isBalanced Case 2 correct ----------------####### + 0.5 Marks" << endl;
	else
		cout << "isBalanced Case 2 incorrect ----------------####### + 0 Marks" << endl;

	
	cout << "************************************************************************" << endl;

	cin >> h1;
	if (subTreeSize(tree, 1) == h1)
		cout << "subTreeSize Case 1 correct ----------------####### + 0.25 Marks" << endl;
	else
		cout << "subTreeSize Case 1 incorrect ----------------####### + 0 Marks" << subTreeSize(tree, 1) << endl;
	

	cin >> h1;
	if (subTreeSize(tree, 2) == h1)
		cout << "subTreeSize Case 2 correct ----------------####### + 0.25 Marks" << endl;
	else
		cout << "subTreeSize Case 2 incorrect ----------------####### + 0 Marks" << subTreeSize(tree, 2) << endl;
	
	cout << "CHECK MANUALLY, if both cases correct and subTreeSize is a O(1) algo then award additional one and a half mark"	<< endl;	

	
	cout << "************************************************************************" << endl;

	cin >> h1;

	if (diameter(tree) == h1)
		cout << "Diameter correct ----------------####### + 1 Marks" << endl;
	else
		cout << "Diameter incorrect ----------------####### + 0 Marks" << endl;
	cout << "CHECK MANUALLY, if diameter is right then verify if its a O(n) algo and award two additional marks"	<< endl;		
//	cout <<"Diameter of tree =" << diameter(tree) <<endl;
	
	cout << "************************************************************************" << endl;	
	return 0;
}
