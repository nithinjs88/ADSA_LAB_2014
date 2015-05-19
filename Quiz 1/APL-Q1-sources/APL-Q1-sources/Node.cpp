#include "Node.h"

Node::Node() {
  	this->left=NULL; 
  	this->right=NULL;
  	this->parent=NULL;
}

Node::Node(int jobid, int priority, int duration) {
	this->jobid = jobid;
	this->priority = priority;
	this->duration = duration;	
  	this->left = NULL; 
  	this->right = NULL;
  	this->parent = NULL;
}
int Node::getJobId() {
	return jobid;
}

int  Node::getPriority() {
	return priority;
}
                                
int Node::getDuration() {
	return duration;
}
                                
void Node::setJobId(int x) {
  	jobid = x;
}
                                      
void Node::setPriority(int x) {
	priority = x;
}
                                      
void  Node::setDuration(int x) {
	duration = x;
}
                                      
Node* Node::getLeftPtr() {
	return left;
}
                                      
Node* Node::getRightPtr() {
	return right;
}
                                      
Node*  Node::getParentPtr() {
	return parent;
}
                                
void Node::setLeftPtr(Node* y) {
  	left = y;
}
      
void Node::setRightPtr(Node * y) {
  	right = y;
}
      
void Node::setParentPtr(Node* y) {
	parent = y;
}
