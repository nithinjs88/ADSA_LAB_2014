class HeapNode {

public:
	HeapNode(int jobId,int priority,int duration);
	int getJobId();
	int getPriority();
	int getDuration();
	void pointToLeft(HeapNode *leftnode);
	HeapNode* getLeft();
	void pointToRight(HeapNode *rightnode);
	HeapNode* getRight();
	void pointToParent(HeapNode *parentnode);
	HeapNode* getParent();
	bool isLessThan(HeapNode *compare);
	void swapValues(HeapNode* ptr);
	
private:
	
	int jobId;
	int priority;
	int duration;	
	HeapNode* left;
   	HeapNode* right;
    	HeapNode* parent;

};
	
	
	
	
	
