#include "Header.cpp"


#define INT_MIN -9999
class Info {
public:
	Info() {
		leader = NULL;
		votes = 0;	
	}	
	Vote* leader;
	int votes;
};

Info* findLeader(Vote* voteArray[],int start,int end);

int findLeader(Vote* voteArray[],int n) {
	// To be implemented.
        // returns index in the array of any object representing the leader, if a leader exists for the array.
	// returns -1 otherwise.
	//cout<<"----------------------";
	Info* leader = findLeader(voteArray,0,n-1);
	if(leader == NULL||leader->leader ==NULL) {
		//no leader found	
		return -1;
	} else {
		//check for the index of the leader			
		for(int i = 0;i<n;i++) {
			Vote* voteItr = voteArray[i];
			if((leader->leader)->isEqual(voteItr)) {
				return i;		
			}
		}	
		//wont happen
		return -1;	
	}
	return -2;
};

int noOfVotesBy(Vote* voteArray[],Vote* toFind,int start,int end) {
	int votes = 0;	
	for(int i = start;i<=end;i++) {
		Vote* voteItr = voteArray[i];
		if(toFind->isEqual(voteItr)) {
			votes++;		
		}
	}
	return votes;
}
 
Info* findLeader(Vote* voteArray[],int start,int end) {
	Info* info_full = new Info();	
	if(start < end) {
		int mid = (start + end)/2;
		//find in left array
		Info* info_left = findLeader(voteArray,start,mid);
		//find in right array
		Info* info_right = findLeader(voteArray,mid+1,end);
		int totalVotes = end-start+1;
		//int votesLeft = mid - start + 1;
		//int votesRight = end - mid;
		int halfVotes = totalVotes/2 + 1;
		
		//Combine strategy
		if((info_left != NULL) && (info_right != NULL)) {
			Vote* leader_left = info_left->leader;
			int vote_left_leader = info_left->votes;

			Vote* leader_right = info_right->leader;
			int vote_right_leader = info_right->votes;
			
			if(leader_left != NULL && leader_right != NULL) {
				if(leader_left->isEqual(leader_right)) {
					//both equal hence return					
					info_full->leader = leader_left;
					info_full->votes = vote_left_leader + 				vote_right_leader;
										
				} else {//combine
					//check for leader_left in right array
					//vote in right subarray by leader_left					
					int votes1 = noOfVotesBy(voteArray,leader_left,mid+1,end);
					int totalVotes1 = votes1 + vote_left_leader;					
					if(totalVotes1 >= halfVotes) {
						info_full->leader = leader_left;
						info_full->votes = totalVotes1;					
					}				
					//check for leader_right in left array
					//vote in left subarray by leader_right	
					int votes2 = noOfVotesBy(voteArray,leader_right,start,mid);
					int totalVotes2 = votes2 + vote_right_leader;					
					if(totalVotes2 >= halfVotes) {
						info_full->leader = leader_right;
						info_full->votes = totalVotes2;					
					}	
				}	
			} else if(leader_left !=NULL && leader_right == NULL) {
				//check for leader_left in right array
				int votes1 = noOfVotesBy(voteArray,leader_left,mid+1,end);
				int totalVotes1 = votes1 + vote_left_leader;					
				if(totalVotes1 >= halfVotes) {
					info_full->leader = leader_left;
					info_full->votes = totalVotes1;					
				}
						
			} else if(leader_right !=NULL && leader_left == NULL) {
				//check for leader_right in left array
				int votes2 = noOfVotesBy(voteArray,leader_right,start,mid);
				int totalVotes2 = votes2 + vote_right_leader;					
				if(totalVotes2 >= halfVotes) {
					info_full->leader = leader_right;
					info_full->votes = totalVotes2;					
				}

			} else {
				//no leader exists			
			}
		}
		
	} else if(start == end) {
		//base case when one vote considered
		info_full->leader = voteArray[start];
		info_full->votes = 1;
	}
	return info_full; 			
}

int findMaxSubmatrixSum(Matrix mat) {
	int rows = mat.getNumRows();
	int columns = mat.getNumColumns();
	int sum[rows][columns];
	sum[0][0] = mat.get(0,0);
	for(int i=0;i<rows;i++) {
		for(int j=0;j<columns;j++) {
			if(i == 0 && j==0)
				continue;
			//max sum doesnt include mat[i][j]
			int top_sum = 0;			
			if(i!= 0)
				top_sum = sum[i-1][j];
			
			int bottom_sum = 0;
			if(j!=0)
				bottom_sum = sum[i][j-1];
			
			int center_sum = 0;
			if(i!= 0 && j!=0)
				center_sum = sum[i-1][j-1];
			//max sum includes mat[i][j]
			int include_sum =  top_sum + bottom_sum - center_sum + mat.get(i,j);
			//find max of all the 4 sums
			int max_top_bottom;
			int max_center_include;
			if(top_sum > bottom_sum) {
				max_top_bottom = top_sum;			
			} else {
				max_top_bottom = bottom_sum;
			}
			if(center_sum > include_sum) {
				max_center_include = center_sum;			
			} else {
				max_center_include = include_sum;
			}
			int max_sum;
			if(max_top_bottom > max_center_include) {
				max_sum = max_top_bottom;			
			} else {
				max_sum = max_center_include;
			}
			sum[i][j] = max_sum;
		}	
	}
	return sum[rows-1][columns-1];
    /*
     
     
     * Given a 
     * This function takes a matrix object in which
     * the entries in each row AND each colum are decreasing.
     * It assumes that at least one entry in the matrix (in particular
     * the top left entry) is non-negative.
     * It returns the 
     * sum of the entries in the maximum weight submatrix.
     * 
     * For example, if given the matrix

	15      12      4
	13      -1      -3
	8       -9      -10

     * your answer must be 40. (Do you see why?)
     * 
     * 
     
     
     */

	// To be implemented.
	//return -1;
}
