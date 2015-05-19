#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string convertIntToString(int num) {
	string str = "";
	bool isPos = true;
	if(num < 0 )
		isPos = false;
	int remainder;
	while(num != 0) {
		remainder = num%10;
		char ch = remainder+48;
		str.insert(0,1,ch);
		num = num/10;
	}
	if(!isPos)
		str.insert(0,1,'-');
	return str;
}
int convertStringToInt(string str) {
	if(str.empty()) {
		throw -1;
	}
	int convertInt = 0;
	int length = str.length();
	char firstChar = str.at(0);
	bool ignoreFirstChar = true;
	bool isPositive = true;
	if(firstChar == '-') {
		isPositive = false;
	} else if(firstChar == '+') {
		
	} else if(firstChar >=48 && firstChar <=57){
		ignoreFirstChar = false;
	} else {
		throw -1;
	}
	int startLimit = 0;
	if(ignoreFirstChar == true) {
		startLimit = 1;
	}
	char charItr;
	for(int i = startLimit;i<length;i++) {
		charItr = str.at(i);
		if(charItr >=48 && charItr <=57) {
			convertInt = convertInt*10 + (charItr - 48);
		} else {
			throw -1;
		}
	}
	return isPositive ? convertInt : -convertInt;
}


/*
int main() {
	int i;
	cin>>i;
	string str = convertIntToString(i);
	cout<<"String is "<<str<<endl;;
	return 0;
}*/

