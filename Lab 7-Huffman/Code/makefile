HuffCode:main.o HENode.o HENode.o
	g++ -g -o HuffCode main.o HENode.o Huffman.o
HENode.o:HENode.h
	g++ -g -c -o HENode.o HENode.cpp
Huffman.o:Huffman.h HENode.o
	g++ -g -c -o Huffman.o Huffman.cpp
main.o:Huffman.o HENode.o
	g++ -g -c -o main.o main.cpp
objects:main.o HENode.o HENode.o
clean:
	\rm *.o HuffCode
target:
	tar -zcvf CS14M033.tar.gz main.cpp TreeNode.cpp TreeNode.h Tree.cpp Tree.h makefile
