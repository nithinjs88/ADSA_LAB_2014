# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o BinaryTree.o functions.o
	$(CXX) $(CXXFLAGS) -o main main.o BinaryTree.o functions.o

# The main.o target can be written more simply

functions.o: functions.cpp BinaryTree.cpp
	$(CXX) $(CXXFLAGS) -c functions.cpp

main.o: main.cpp BinaryTree.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp


BinaryTree.o: BinaryTree.cpp
	$(CXX) $(CXXFLAGS) -c BinaryTree.cpp
	

tar:
	tar -czvf sources.tar.gz main.cpp functions.cpp BinaryTree.cpp makefile input.txt
