# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o Header.o  functions.o
	$(CXX) $(CXXFLAGS) -o main main.o Header.o  functions.o

# The main.o target can be written more simply

functions.o: functions.cpp Header.o
	$(CXX) $(CXXFLAGS) -c functions.cpp

main.o: main.cpp Header.o
	$(CXX) $(CXXFLAGS) -c main.cpp


Vote.o: Header.cpp
	$(CXX) $(CXXFLAGS) -c Header.cpp
	

tar:
	tar -czvf Quiz2.tar.gz main.cpp functions.cpp Header.cpp  makefile VotesFile1 VotesFile2 MatrixFile1 MatrixFile2
