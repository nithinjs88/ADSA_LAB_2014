#ifndef _NODE_H
#define _NODE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


class Node {
public:
      Node();   
      Node(int jobid, int priority, int duration);

      int getJobId();
      int getPriority();
      int getDuration();

      void setJobId(int x);
      void setPriority(int x);
      void setDuration(int x);
                                      
      Node* getLeftPtr();
      Node* getRightPtr();
      Node* getParentPtr();
                                
      void setLeftPtr(Node* y);
      void setRightPtr(Node* y);
      void setParentPtr(Node* y);
private:
          int jobid;
          int priority;
          int duration;
          Node* parent;
          Node* left;
          Node* right;
};

#endif
