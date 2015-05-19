#include "TreeNode.h"
#include <iostream>
using namespace std;
#define LESSER -1
#define EQUAL 0
#define GREATER 1

	TreeNode::TreeNode(int jobId,int duration,int priority) {
		this->jobId = jobId;
		this->priority = priority;
		this->duration = duration;
		this->left = NULL;
		this->right= NULL;
	}
	
	int TreeNode:: getJobId() {
		return jobId;
	}
	
	int TreeNode::getPriority() {
		return priority;
	}
	
	int TreeNode::getDuration() {
		return duration;
	}

	void TreeNode::pointToLeft(TreeNode *leftnode) {
		this->left = leftnode;
	}
	
	TreeNode* TreeNode:: getLeft() {
		return left;
	}
	
	void TreeNode::pointToRight(TreeNode *rightnode) {
		this->right = rightnode;
	}
	
	TreeNode* TreeNode::getRight() {
		return right;
	}
	
	void TreeNode::pointToParent(TreeNode *parentnode) {
		this->parent = parentnode;
	}
	
	TreeNode* TreeNode::getParent() {
		return parent;
	}
	
	int TreeNode::compareTo(TreeNode *compare) {
		int compJobId = compare->jobId;
		//int compId = compare->getJobId();
		if(jobId < compJobId) {
			return LESSER;	
		} else if(jobId == compJobId) {
			return EQUAL;
		} else {
			return GREATER;
		}
	}

	void TreeNode::swapValues(TreeNode* ptr) {
		int tempJobId = this-> jobId;
		this->jobId = ptr->jobId;
		ptr->jobId = tempJobId;

		int tempPriority = this-> priority;
		this->priority = ptr->priority;
		ptr->priority = tempPriority;

		int tempDuration = this-> duration;
		this->duration = ptr->duration;
		ptr->duration = tempDuration;
	}
	
	void TreeNode::printNode() {
		cout<<jobId<<" "<<duration<<" "<<priority<<endl;
	}
	
