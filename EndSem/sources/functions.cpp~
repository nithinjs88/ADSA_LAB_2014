#include "BinaryTree.cpp"
#include<bits/stdc++.h>

int getMax(int a,int b) {
	return a>b?a:b;
}

int getMin(int a,int b) {
	return a<b?a:b;
}

int getParent(int idx) {
	return idx/2;
}

int getLeftIdx(int idx) {
	return 2*idx;
}

int getRightIdx(int idx) {
	return 2*idx+1;
}



bool BinaryTree::DFS_visit(int node) {
	if(pre[node] == -1) {
		pre[node] = visit_time;
		visit_time++;
		int leftIdx = 2*node;
		int rightIdx = 2*node + 1;
		bool isLeftPre = nodes[leftIdx];
		bool isRightPre = nodes[rightIdx];
		int leftHeight = 0;
		int rightHeight = 0;		
		if(isLeftPre) {
			DFS_visit(leftIdx);
			leftHeight = height[leftIdx];
		} else {
			//do nothing		
		}
		if(isRightPre) {
			DFS_visit(rightIdx);
			rightHeight = height[rightIdx];	
		} else {
			//do nothing		
		}
		int maxHeight = getMax(leftHeight,rightHeight);
		height[node] = maxHeight + 1;
		post[node] = visit_time;
		visit_time++;
	}
	 /*
                Recursive call to execute DFS.
                During this execution, the pre-visit and post-visit numbers must be computed and stored
                in the pre and post arraygs.
                
                For each node i, you must store the height of the subtree rooted at i in height[i].
        
        */
	
	return true;
}

int populateAncestors(BinaryTree tree, int nodeIdx,int *ancestors) {
	int idxItr = nodeIdx;	
	int size = 0;	
	while(idxItr >=1 ) {
		if(tree.isNode(idxItr)) {
			for(int j = size;j > 0;j--) {
				ancestors[j] = ancestors[j-1];		
			}
			ancestors[0] = idxItr; 
			size++;
		}
		idxItr = idxItr/2;
	}
	return size;
}

void printArray(int *array,int size) {
	for(int i=0;i<size;i++) {
		cout<<array[i]<<" ";		
	}
	cout<<endl;
}

bool isAncestor(BinaryTree tree, int anc, int desc) {
	/*
		This function must return true if the node anc is an ancestor of node desc in tree. 
		You may assume that anc and desc are valid nodes in tree.
	*/
	if((tree.getPre(anc) < tree.getPre(desc))&&( tree.getPost(desc) < tree.getPost(anc))) {
		return true;	
	}
	return false;
}
	
int LCA(BinaryTree tree, int n1, int n2) {
	int ancestor1[4096];
	int ancestor2[4096];
	int anc1Size = populateAncestors(tree,n1,ancestor1);
	//cout<<"Print anc of "<<n1<<endl;
	//printArray(ancestor1,anc1Size);
	int anc2Size = populateAncestors(tree,n2,ancestor2);
	//Print anc2
	//cout<<"Print anc of "<<n2<<endl;	
	//printArray(ancestor2,anc2Size);
	int limit = getMin(anc1Size,anc2Size);
	int LCA = -1;	
	for(int i = 0;i<limit;i++) {
		int anc1Itr = ancestor1[i];
		int anc2Itr = ancestor2[i];
		if(anc1Itr == anc2Itr) {
			LCA =  anc1Itr;		
		} else {
			break;		
		}
	}
	return LCA;
	/*
		This function must take two valid nodes n1 and n2 in tree and return the lowest common ancestor. 
		The lowest common ancestor of n1 and n2 is a node in the tree which is a ancestor of both n1 and n2, 
		but neither of its children and common ancestors to both n1 and n2.
	*/
	//return -1;
}
int subTreeSize(BinaryTree tree, int node){
	return (tree.getPost(node) - tree.getPre(node) + 1)/2;
		/*
			Must return the number of nodes in the subtree rooted at node.
			The function must run in $O(1)$ time.
		*/
		return -1;
}
	
bool isBalanced(BinaryTree tree, int node) {
	int leftChildIdx = getLeftIdx(node);
	int rightChildIdx = getRightIdx(node);
	bool isBalancedLeft = false;
	bool isBalancedRight = false;
	//bool isBalancedAtParent = false;
	int leftHeight = 0;
	int rightHeight = 0;
	//calc leftHeight and isBalancedLeft for left subtree
	if(tree.isNode(leftChildIdx)) {
		isBalancedLeft = isBalanced(tree,leftChildIdx);
		leftHeight = tree.getHeight(leftChildIdx);
	} else {
		leftHeight = 0;
		isBalancedLeft = true;
	}
	//calc rightHeight and isBalancedRight for right subtree
	if(tree.isNode(rightChildIdx)) {
		isBalancedRight = isBalanced(tree,rightChildIdx);
		rightHeight = tree.getHeight(rightChildIdx);
	} else {
		rightHeight = 0;
		isBalancedRight = true;	
	}
	//tree is balanced only if left subtree is balanced and right subtree is balanced
	//and their respective heights differ by at most 1
	if(isBalancedLeft && isBalancedRight) {
		if(leftHeight == rightHeight || (leftHeight - rightHeight ==1)
			|| (leftHeight - rightHeight ==-1) ) {
			return true;		
		}	
	}
	return false;
	/*
		Must return true iff the subtree (in tree) that is rooted at node is height balanced.
		A (sub)tree is height balanced if, for every node in the (sub)tree, the heights of its two children 
		differ by at most 1.
		
		
	*/
	return false;
}

int getDiameter(BinaryTree tree,int idx) {
	int leftChildIdx = getLeftIdx(idx);
	int rightChildIdx = getRightIdx(idx);
	int leftDiameter = 0;
	int rightDiameter = 0;
	int leftHeight = 0;
	int rightHeight = 0;
	//calculate left diameter	
	if(tree.isNode(leftChildIdx)) {
		leftDiameter = getDiameter(tree,leftChildIdx);
		leftHeight = tree.getHeight(leftChildIdx);
	} else {
		leftDiameter = 0;
	}
	//calculate left diameter
	if(tree.isNode(rightChildIdx)) {
		rightDiameter = getDiameter(tree,rightChildIdx);
		rightHeight = tree.getHeight(rightChildIdx);
	} else {
		rightDiameter = 0;
	}
	//candidateDiameter sum of left diameter and right diameter
	int candidateDiameter = leftHeight + rightHeight;
	//return max of the diameters
	return getMax(leftDiameter,getMax(rightDiameter,candidateDiameter));
}
	
int diameter(BinaryTree tree) {
	return getDiameter(tree,1);
	//return -1;
}
