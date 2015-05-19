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
	
	cout<<"is 10 anc 23 "<<isAncestor(tree,10,23)<<endl;
	cout<<"is 10 anc 40 "<<isAncestor(tree,10,40)<<endl;
	cout<<"is 40 anc 10 "<<isAncestor(tree,40,10)<<endl;
	cout<<"is 2 anc 47 "<<isAncestor(tree,2,47)<<endl;
	cout<<"is 1 anc 160 "<<isAncestor(tree,1,160)<<endl;
	cout<<"is 160 anc 1 "<<isAncestor(tree,160,1)<<endl;
	cout<<"is 160 anc 95 "<<isAncestor(tree,160,95)<<endl;
	cout<<"is 5 anc 11 "<<isAncestor(tree,5,11)<<endl;
	cout<<"is 11 anc 5 "<<isAncestor(tree,11,5)<<endl;

	cout << "LCA of 1 and 160 is " << LCA(tree,1,160) << endl;
	cout << "LCA of 160 and 1 is " << LCA(tree,160,1) << endl;
	cout << "LCA of 160 and 95 is " << LCA(tree,160,95) << endl;
	cout << "LCA of 95 and 160 is " << LCA(tree,95,160) << endl;
	cout << "LCA of 2 and 2 is " << LCA(tree,2,2) << endl;
	cout << "LCA of 5 and 11 is " << LCA(tree,5,11) << endl;
	cout << "LCA of 11 and 5 is " << LCA(tree,11,5) << endl;
	cout << "LCA of 160 and 3 is " << LCA(tree,160,3) << endl;
	cout << "LCA of 10 and 11 is " << LCA(tree,10,11) << endl;

	cout << "Size of tree = " << subTreeSize(tree,1) << endl;
	cout << "Size of subtree at 160 = " << subTreeSize(tree,160) << endl;
	cout << "Size of subtree at 95 = " << subTreeSize(tree,95) << endl;
	cout << "Size of subtree at 5 = " << subTreeSize(tree,5) << endl;
	cout << "Size of subtree at 2 = " << subTreeSize(tree,2) << endl;

	cout << "Balance = " << isBalanced(tree, 1) << endl;
	cout << "Balance at 160 = " << isBalanced(tree, 160) << endl;
	cout << "Balance at 80 = " << isBalanced(tree, 80) << endl;
	cout << "Balance at 40 = " << isBalanced(tree, 40) << endl;
	cout << "Balance at 5 = " << isBalanced(tree, 5) << endl;
	cout << "Balance at 2 = " << isBalanced(tree, 2) << endl;
	cout << "Balance at 3 = " << isBalanced(tree, 3) << endl;

	/*
	cout << "LCA of 2 and 6 is " << LCA(tree,2,6) << endl;
	cout << "LCA of 2 and 4 is " << LCA(tree,2,4) << endl;
	cout << "LCA of 2 and 2 is " << LCA(tree,2,2) << endl;
	cout << "LCA of 7 and 4 is " << LCA(tree,7,4) << endl;
	
	cout << "Balance = " << isBalanced(tree, 1) << endl;
	cout << "Balance at 8= " << isBalanced(tree, 8) << endl;
	cout << "Balance at 4 = " << isBalanced(tree, 4) << endl;
	cout << "Balance at 3 = " << isBalanced(tree, 3) << endl;
	cout << "Balance at 2 = " << isBalanced(tree, 2) << endl;
	
	cout << "Size of tree = " << subTreeSize(tree,1) << endl;
	cout << "Size of subtree at 2 = " << subTreeSize(tree,2) << endl;
	cout << "Size of subtree at 3 = " << subTreeSize(tree,3) << endl;
	cout << "Size of subtree at 8 = " << subTreeSize(tree,8) << endl;
	*/
	cout <<"Diameter of tree =" << diameter(tree) <<endl;
	return 0;
}
