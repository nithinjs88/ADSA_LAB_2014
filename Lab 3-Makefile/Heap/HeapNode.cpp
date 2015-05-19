#include "HeapNode.h"
#include <iostream>

	HeapNode::HeapNode(int jobId,int priority,int duration) {
		this->jobId = jobId;
		this->priority = priority;
		this->duration = duration;
		this->left = NULL;
		this->right= NULL;
	}
	
	int HeapNode:: getJobId() {
		return jobId;
	}
	
	int HeapNode::getPriority() {
		return priority;
	}
	
	int HeapNode::getDuration() {
		return duration;
	}

	void HeapNode::pointToLeft(HeapNode *leftnode) {
		this->left = leftnode;
	}
	
	HeapNode* HeapNode:: getLeft() {
		return left;
	}
	
	void HeapNode::pointToRight(HeapNode *rightnode) {
		this->right = rightnode;
	}
	
	HeapNode* HeapNode::getRight() {
		return right;
	}
	
	void HeapNode::pointToParent(HeapNode *parentnode) {
		this->parent = parentnode;
	}
	
	HeapNode* HeapNode::getParent() {
		return parent;
	}
	
	bool HeapNode::isLessThan(HeapNode *compare) {
		int compPrior = compare->getPriority();
		//int compId = compare->getJobId();
		if(priority < compPrior) {
			return true;	
		} else if(priority == compPrior) {
			return jobId < compare->getJobId();
		} else {
			return false;
		}
	}

	void HeapNode::swapValues(HeapNode* ptr) {
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
	
