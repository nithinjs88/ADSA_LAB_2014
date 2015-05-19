#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
#define DEBUG 1
#define dout if(DEBUG) cout
#define debug if(DEBUG)
#define LESSER -2
#define EQUAL_LESSER -1
#define EQUAL 0
#define EQUAL_GREATER 1
#define GREATER 2
#define MAX 32766

class Point {

public:
	
	Point(int x,int y){
		this->x = x;
		this->y = y;
	}

	int get_x() {
		return x;
	}

	int get_y() {
		return y;
	}

	int compare(Point* point,bool sort_x) {
		if(sort_x) {
			return this->compare_x(point);
		} else {
			return this->compare_y(point);
		}
	}

	string get_string() {
		ostringstream oss;
		oss<<x<<" "<<y;
		return oss.str();
	}

	int manhattan(Point* point) {
		return (abs(x - point->get_x()) + abs(y - point->get_y()));
	}

private:
	int x,y;
	
	int compare_x(Point* point){
		int point_x = point->get_x();
		if(x < point_x) {
			return LESSER;
		}if(x == point_x) {
			int point_y = point->get_y();
			if(y < point_y) {
				return EQUAL_LESSER;
			} else if(y == point_y) {
				return EQUAL;
			} else {
				//y > point_y
				return EQUAL_GREATER;
			}
		} else {
			//x > point_x
			return GREATER;
		}
	}
	
	int compare_y(Point* point){
		int point_y = point->get_y();
		if(y < point_y) {
			return LESSER;
		}if(y == point_y) {
			int point_x = point->get_x();
			if(x < point_x) {
				return EQUAL_LESSER;
			} else if(x == point_x) {
				return EQUAL;
			} else {
				//x > point_x
				return EQUAL_GREATER;
			}
		} else {
			//y > point_y
			return GREATER;
		}
	}

	
};

class Info {

public:
	Info(Point *p1, Point *p2, int distance) {
		this->point1 = p1;
		this->point2 = p2;
		this->distance = distance;
	}
	Point* get_point1() {
		return point1;
	}
	Point* get_point2() {
		return point2;
	}
	void set_point1(Point* point1) {
		this->point1 = point1;
	}
	void set_point2(Point* point2) {
		this->point2 = point2;
	}
	int get_distance() {
		return distance;
	}
	void set_distance(int distance) {
		this->distance = distance;
	}
		
private:

	Point* point1;
	Point* point2;
	int distance;	
};

class ManhattanFinder {

public:

	ManhattanFinder(vector<Point*> input) {
		this->input = input;
	}
	
	Info* get_info() {
		return info;
	}
	
	void find() {
		sort_x();
		sort_y();
		
		ostringstream oss("");
		this->info = computeManhattan(0,sorted_x.size()-1, oss);
	
		ofstream fp;
		fp.open("comparisons.log");
		fp << oss.str();
		fp.close();

		cout <<info->get_distance()<<"\n";
		dout <<"Manhattan Distance="<<info->get_distance()<<"\n";
		dout <<"p1="<<info->get_point1()->get_string()<<"  p2="<<info->get_point2()->get_string()<<"\n";
	}
	
	Info* computeManhattan(int start,int end, ostringstream& oss) {
		int min = 9999;
		Point* p1, *p2;
		Info *ret;
		for(int i =0;i<sorted_x.size();i++) 
		{
			for(int j=0; j<sorted_x.size();j++)
			{
				if (i != j) {
					int temp = sorted_x.at(i)->manhattan(sorted_x.at(j));
					if (temp < min) {
						ret = new Info(sorted_x.at(i), sorted_x.at(j), temp);
						min = temp;
					}
				}
			}
		}
		//cout <<p1->getString()<<" "<<p2->getString()<<" dist="<<min;
		return ret;		
				
	}
	
	void sort_x() {
		for(int i=0;i<input.size();i++) {
			sorted_x.push_back(input.at(i));
		}
		mergesort(sorted_x,0,sorted_x.size() -1 ,true);
	}
	
	void sort_y() {
		for(int i=0;i<input.size();i++) {
			sorted_y.push_back(input.at(i));
		}
		mergesort(sorted_y,0,sorted_y.size() -1 ,false);
	}
	
	void mergesort(vector<Point*> &points,int start,int end,bool sort_x_flag) {
		int mid;
		if (start < end) {
			mid=(start+end)/2;
			mergesort(points,start,mid,sort_x_flag);
			mergesort(points,mid+1,end,sort_x_flag);
			merge(points,start,end,sort_x_flag);
		}
	}
	
	int binary_search(vector<Point*> points,Point *findPoint,
			int start,int end,bool sort_x_flag) {
		if(start < end) {
			int mid = (start + end)/2;
			if(mid < points.size()) {
				Point* midEle = points.at(mid);
				int compare = findPoint->compare(midEle,sort_x_flag);
				if(compare < EQUAL) {
					//findPoint < midEle
					return binary_search(points,findPoint,start,mid-1,sort_x_flag);
				} else if(compare == EQUAL) {
					return mid;
				} else {
					//findPoint > midEle
					return binary_search(points,findPoint,mid + 1,end,sort_x_flag);
				}
			} else {
				return -1;
			}
		}
	}
	
	void merge(vector<Point*> &points,int start,int end,bool sort_x_flag) {
		//idx - index,itr - iterator,ele - element
		int itrLeftIdx, itrRightIdx, itrSortedIdx, mid;
		Point *itrLeftEle,*itrRightEle;
		int noOfLeftEle,noOfRightEle;
		vector<Point*> left_sub_vector,right_sub_vector;
		
		mid = (start + end)/2;
		noOfLeftEle = mid - start + 1;
		noOfRightEle = end - mid;
		
		for(itrLeftIdx=0;itrLeftIdx < noOfLeftEle;itrLeftIdx++) {
			//copy to left_sub_vector
			left_sub_vector.push_back(points.at(start + itrLeftIdx));
		}
		
		for(itrRightIdx=0;itrRightIdx < noOfRightEle;itrRightIdx++) {
			//copy to right_sub_vector
			right_sub_vector.push_back(points.at(mid + 1 + itrRightIdx));
		}
		itrLeftIdx=0;
		itrRightIdx=0;
		int compare = EQUAL;
		for (itrSortedIdx = start;itrSortedIdx <= end ; itrSortedIdx++) {
			itrLeftEle =  left_sub_vector.at(itrLeftIdx);
			itrRightEle =  right_sub_vector.at(itrRightIdx);
			compare = itrLeftEle->compare(itrRightEle,sort_x_flag);
			if(compare < EQUAL) {
				//left < right
				points.at(itrSortedIdx) = itrLeftEle;
				itrLeftIdx++;
			} else if(compare == EQUAL) {
				//left = right
				points.at(itrSortedIdx) = itrLeftEle;
				itrLeftIdx++;
			} else {
				//left > right
				points.at(itrSortedIdx) = itrRightEle;
				itrRightIdx++;
			}
			if(itrLeftIdx >= left_sub_vector.size()) {
				//copy right_vector elements
				for(;itrRightIdx < right_sub_vector.size();itrRightIdx++) {
					itrSortedIdx++;
					points.at(itrSortedIdx) = right_sub_vector.at(itrRightIdx);;
				}
				break;
			}
			if(itrRightIdx >= right_sub_vector.size()) {
				//copy left_vector elements
				for(;itrLeftIdx < left_sub_vector.size();itrLeftIdx++) {
					itrSortedIdx++;
					points.at(itrSortedIdx) = left_sub_vector.at(itrLeftIdx);;
				}
				break;
			}
		}
    
	}
	
private:
	vector<Point*> input;
	vector<Point*> sorted_x;
	vector<Point*> sorted_y;
	Info* info;
};

void readInput(string input_file,vector<Point*> &points);

int main(int argc,char *argv[]) {
	if(argc != 2) {
		//error("Invalid no of arguments");
		return -1;
	}
	string input_file = argv[1];
	vector<Point*> points;
	readInput(input_file,points);
	//dout<<"size is "<<points.size()<<endl;
	/*for(int i=0;i<points.size();i++) {
		dout<< (points.at(i))->get_string()<<endl;
	}*/
	ManhattanFinder finder = ManhattanFinder(points);
	finder.find();
	return 0;
}	

void readInput(string input_file,vector<Point*> &points) {
	ifstream in;
	in.open(input_file.c_str());
	string inputLine;
	int x,y;
	string end;
	while (getline(in, inputLine)) {
		if(inputLine == "done") {
			break;
		}
		istringstream iss;
		iss.str(inputLine);
		if(inputLine.length()>0) {
			iss >> x>>y>>end;
			if (end.compare("") != 0) {
				cout <<"Error (Incorrect Input Format)\n";
				exit(0);
			}
			Point *point = new Point(x,y);
			points.push_back(point);
			end.clear();
		} 
	}
}
