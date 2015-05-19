#include "Header.cpp"

//Following lines say that these functions are implemented 
//in some other file.

extern int findLeader(Vote* Varray[],int n);
extern int findMaxSubmatrixSum(Matrix matrix);
int populateVotesArray(Vote* VArray[], char *filename) {
	
	// Given a BST and a filename, reads the lines in the file
	// and populates a BST. Returns the number of nodes successfully added
	// to BST.
	ifstream fin;
	fin.open(filename);
	string name;
	fin >> name;
	int count = 0;
	while (!fin.eof()) {
		Vote* vote = new Vote(name);
		VArray[count] = vote;
		count++;
		fin >> name;
	}
	fin.close();
	return count;
}
int main(int argc, char *argv[]) {
	

	if (argc < 2) {
		cout<< "Invalid number of arguments.\n Usage: \n "<< argv[0] << " -p1 n <filename>\n OR \n " << argv[0] <<" -p2 <filename>\n ";
	}

	else if (strcmp(argv[1], "-p1") == 0) {
		// Code for reading input for Problem 1.
		if (argc != 4) {
			cout << "Invalid number of arguments.\nUsage: " << argv[0]  << " -p1 n <filename>\n";
			return -1;
   		}
		int n = atoi(argv[2]);
		Vote* allVotes[n];
		populateVotesArray(allVotes, argv[3]);

		//Helper loop for printing votes read from file.
		for (int i=0; i<n; i++){
			allVotes[i]->print();
		}
		// Call to findLeader.
		int leaderIndex = findLeader(allVotes,n);


		if (leaderIndex >= 0 && leaderIndex < n) {
			allVotes[leaderIndex]->print();
		} else if (leaderIndex == -1) {
			cout <<"No leader.\n";
		} else if (leaderIndex == -2) {
			cout <<"findLeader not implemented\n";
		}
		return 0;
	}
	else if (strcmp(argv[1], "-p2") == 0 ) {
		// Code for reading input for Problem 2.
		if(argc != 3) {
			cout << "Invalid number of arguments.\nUsage: " << argv[0]  << " -p2  <filename>\n";
			return -1;
    		}
    		Matrix mat(argv[2]);

		//Helper function for printing matrix read from file.
    		mat.print();

		// Call to findMaxSubmatrixSum.
    		int total = findMaxSubmatrixSum(mat);
    		cout << endl << "Total = " << total << endl;
		return 0;

	} else {
		cout <<"Usage:  \n "<< argv[0] << " -p1 n <filename>\n OR \n " << argv[0] <<" -p2 <filename>\n ";
	}
	

}
