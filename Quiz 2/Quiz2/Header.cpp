
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "string.h"
using namespace std;

/* Class definition needed from Problem 1 */


class Vote {
public:
      Vote();
      Vote(string str) {
		name = str;
      }

      int isEqual(Vote* V) {
		if (NULL == V) {
			cout << "comparing to a NULL object\n Exiting \n";
			exit(1);
		
		}
		if ( 0 == name.compare(V->name)) {
			return 1;
		} else 
			return 0;
      }

      void print() {
		cout<<"Vote = " << name <<"\n";
      }
private:
	string name;
};


/* Class definition needed from Problem 2 */

class Matrix {
private :
    int entries[100][100];
    int n; // number of rows
    int m; // number of columns
public :
    Matrix();
    Matrix(char *filename){
        n = m = 0;
        ifstream fin;
        fin.open(filename);
        fin >> n >> m;
        cout << n << m;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                fin >> entries[i][j];
            }
        }
        fin.close();
    }
    int get(int i, int j){
        if((i >= n)||(j>=m)||(i<0)||(j<0))
            cout << "Error in matrix entry request";
        return entries[i][j];
    }
    int getNumRows(){ return n;}
    int getNumColumns(){ return m;}
    void print(){
        cout << endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cout <<  entries[i][j] << " ";
            }
            cout << endl;
        }
	cout <<endl;
    }
};


