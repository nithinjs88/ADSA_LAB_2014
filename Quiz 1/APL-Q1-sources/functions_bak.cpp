#include "Node.h"
#include "BST.h"

int isEqualNode(Node* n1, Node* n2) {
	//Checks if the data contained in the two nodes is equal.
	//Returns 1 if they are equal; 0 otherwise.
	if(n1 != NULL && n2!=NULL) {
		bool flag = (n1->getJobId() == n2->getJobId()) &&
			(n1->getPriority() == n2->getPriority()) &&
			(n1->getDuration() == n2->getDuration());
		if(flag)
			return 1;
		else
			return 0;	
	}
	if(n1 == NULL && n2 == NULL)
		return 1;
	
	//cout << "isEqualNode to be implemented\n";
	return 0;
}

int isEqualNodeWithPointers (Node* n1, Node* n2) {
	
	//Checks if the two BSTs T1 and T2 are equal.
	//See problem statement for the definition of equal.
	//Returns 1 if the trees are equal; 0 otherwise.
	//cout << "isEqualBST to be implemented\n";
	int status = isEqualNode(n1,n2);
	if(status == 1) {
		if(n1 != NULL && n2!= NULL) {
			return isEqualNodeWithPointers(n1->getLeftPtr(),n2->getLeftPtr()) &&
				isEqualNodeWithPointers(n1->getRightPtr(),n2->getRightPtr());		
		}
		if(n1 == NULL && n2 == NULL)
			return 1;
	}	
	return 0;
}

void inorderTraversal(Node* root,Node* nodeArray[],int &length) {
	//Node* nodeArray[100];
	if(root != NULL) {	
		inorderTraversal(root->getLeftPtr(),nodeArray,length);
		nodeArray[length] = root;
		length++;
		inorderTraversal(root->getRightPtr(),nodeArray,length);	
	}
	
}

void inorderTraversal(BST bst,Node* nodeArray[],int &length) {
	//Node* nodeArray[100];
	//int length = 0;	
	inorderTraversal(bst.getRoot(),nodeArray,length);
	return; 
}



int isEqualBST (BST T1, BST T2) {
	

	//Checks if the two BSTs T1 and T2 are equal.
	//See problem statement for the definition of equal.
	//Returns 1 if the trees are equal; 0 otherwise.
	//cout << "isEqualBST to be implemented\n";
	return isEqualNodeWithPointers(T1.getRoot(),T2.getRoot());
	//return -1;
}



int isEquivBST (BST T1, BST T2) {
	//Checks if the two BSTs T1 and T2 are equivalent.
	//See problem statement for the definition of equivalent.
	//Returns 1 if the trees are equivalent; 0 otherwise.
	//cout << "isEquivBST to be implemented\n";
	Node* node1Array[100];
	int length1 = 0;	
	Node* node2Array[100];
	int length2 = 0;
	inorderTraversal(T1,node1Array,length1);
	inorderTraversal(T2,node2Array,length2);
	if(length1 == length2) {
		for(int i=0;i<length1;i++) {
			//if(inorderTraversal(T1,node1Array,length1);)		
			Node* node1 = node1Array[i];
			Node* node2 = node2Array[i];
			if(isEqualNode(node1,node2) == 0) {
				return 0;				
			}	
		}
		return 1;
	} else {
		return 0;	
	}
	//return -1;
}

void BST::POPrint() {
	//Prints the tree in preorder format. The code needs to be non-recursive.
	//cout <<"POPrint (PreOrderPrint) to be implemented\n";
	Node* ptr = getRoot();
	Node* leftPtr = NULL;
	Node* rightPtr = NULL;
	Node* parentPtr = NULL;
	//left - 0,left up 1,right 2,right up 3
	int direction = 0;
	while(ptr != NULL) {
		if(direction == 0 || direction ==2) {	
			cout<<"  " << ptr->getJobId() <<"  "<< ptr->getPriority()<<"  "<<ptr->getDuration()<<"\n";
		}
		leftPtr = ptr->getLeftPtr();
		rightPtr = ptr->getRightPtr();
		parentPtr = ptr->getParentPtr();
		if(direction == 0 || direction == 2) {
			//coming left or right
			if(leftPtr != NULL) {
				direction = 0;
				ptr = leftPtr;
			} else {
				if(rightPtr!= NULL) {
					direction = 2;
					ptr = rightPtr;				
				} else {
					if(direction == 0) {
						direction = 1;
					} else if(direction == 2) {
						direction =3;
					} 
					//direction = 1;
					ptr = parentPtr;
				}
			}
		} else if(direction == 1) {
			if(rightPtr!= NULL) {
				direction = 2;
				ptr = rightPtr;				
			} else {
				if(parentPtr == NULL)
				break;
				if(parentPtr->getLeftPtr() == ptr) {
					direction = 1;			
				} else {
					direction = 3;			
				}
				ptr = parentPtr;
				//direction = 1;
				//ptr = parentPtr;
			}	
		} else if(direction == 3) {
			//direction = 1;
			if(parentPtr == NULL)
				break;
			if(parentPtr->getLeftPtr() == ptr) {
				direction = 1;			
			} else {
				direction = 3;			
			}
			ptr = parentPtr;
		}
	}
}
