class TreeNode {

public:
	TreeNode(int jobId,int priority,int duration);
	int getJobId();
	int getPriority();
	int getDuration();
	void pointToLeft(TreeNode *leftnode);
	TreeNode* getLeft();
	void pointToRight(TreeNode *rightnode);
	TreeNode* getRight();
	void pointToParent(TreeNode *parentnode);
	TreeNode* getParent();
	int compareTo(TreeNode *compare);
	void swapValues(TreeNode* ptr);
	void printNode();
	
private:
	
	int jobId;
	int priority;
	int duration;	
	TreeNode* left;
   	TreeNode* right;
    TreeNode* parent;

};
	
	
	
	
	
