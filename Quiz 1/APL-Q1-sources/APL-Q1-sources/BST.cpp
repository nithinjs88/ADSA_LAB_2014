#include "Node.h"
#include "BST.h"


BST::BST() {
	ROOT = NULL;
}

Node* BST::getRoot() {
	return ROOT;
}

int BST::insert(Node* newnode) {
	// adds newnode to BST. returns 1 if success, 0 otherwise.
	return add(getRoot(), newnode);
}


Node* BST::search(int id) {
	 return find(ROOT, id); 
}
void BST::printTree(){
	RecPOPrint(getRoot());
}

int BST::add(Node* currRoot, Node* newnode) {
	// adds newnode to BST. returns 1 if success, 0 otherwise.
	if (NULL == currRoot) {
		//This happens only once for the first time.
		ROOT = newnode; 
		ROOT->setParentPtr(NULL); 
		return 1;
	}
	else {
		if (currRoot->getJobId() == newnode->getJobId()){
			cout << "Duplicate JobId during insertion. "<< newnode->getJobId() <<" Insert unsuccessful. \n"; 
			return 0;
		}
		else if (currRoot->getJobId() > newnode->getJobId()) {
			//newnode belongs to left subtree of currRoot.
			if (NULL == currRoot->getLeftPtr()) {
				currRoot->setLeftPtr(newnode); 
				newnode->setParentPtr(currRoot); 
				return 1;
			} else {
				return add(currRoot->getLeftPtr(), newnode);
			}
		} else if(currRoot->getJobId() < newnode->getJobId()){
			//newnode belongs to right subtree of currRoot.
			if (NULL == currRoot->getRightPtr()) {
				currRoot->setRightPtr(newnode); 
				newnode->setParentPtr(currRoot); 
				return 1;	
			}
			else {
				return add(currRoot->getRightPtr(), newnode);
			}
		}
	}
	return 0;
}

Node* BST::find(Node* currRoot, int id) {
	if (NULL == currRoot || currRoot->getJobId() == id) {
		return currRoot;
	}
	if (currRoot->getJobId() > id)  {
		return find(currRoot->getLeftPtr(), id);
	} else  {
		return find(currRoot->getRightPtr(), id); 
	}
}


void BST::RecPOPrint(Node* currRoot){
	//prints tree in preorder form.
	if (currRoot != NULL) {
    		cout<<"  " << currRoot->getJobId() <<"  "<< currRoot->getPriority()<<"  "<<currRoot->getDuration()<<"\n";
    		RecPOPrint(currRoot->getLeftPtr());
    		RecPOPrint(currRoot->getRightPtr());
  	}
}

