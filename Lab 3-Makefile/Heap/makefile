heapsort:main.o HeapNode.o MinHeap.o
	g++ -g -o heapsort main.o HeapNode.o MinHeap.o
objects:main.o HeapNode.o MinHeap.o
main.o:HeapNode.o MinHeap.o
	g++ -g -c -o main.o main.cpp
HeapNode.o:HeapNode.h
	g++ -g -c -o HeapNode.o HeapNode.cpp
MinHeap.o:HeapNode.o HeapNode.h
	g++ -g -c -o MinHeap.o MinHeap.cpp
clean:
	rm *.o heapsort
target:
	tar -zcvf CS14M033.tar.gz main.cpp MinHeap.cpp MinHeap.h HeapNode.cpp HeapNode.h makefile

