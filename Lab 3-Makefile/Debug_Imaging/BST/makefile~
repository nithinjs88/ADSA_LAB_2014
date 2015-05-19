BST:main.o TreeNode.o Tree.o
	g++ -g -o binTree main.o TreeNode.o Tree.o
TreeNode.o:TreeNode.h
	g++ -g -c -o TreeNode.o TreeNode.cpp
Tree.o:TreeNode.o
	g++ -g -c -o Tree.o Tree.cpp
main.o:Tree.o TreeNode.o
	g++ -g -c -o main.o main.cpp
objects:main.o TreeNode.o Tree.o
clean:
	\rm *.o binTree
target:
	tar -zcvf CS14M033.tar.gz main.cpp TreeNode.cpp TreeNode.h Tree.cpp Tree.h makefile
