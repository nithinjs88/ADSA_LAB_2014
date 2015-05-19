#include <bits/stdc++.h>
using namespace std;
#define DEBUG 0
#define dout if(DEBUG) cout
#define debug if(DEBUG)
#define LESSER -1
#define EQUAL 0
#define GREATER 1
#define MAX_VALUE 9999
#define GRAPH_KEYWORD "graph"
#define DIR_GRAPH_KEYWORD "digraph"
#define NODES_SEP "//nodes"
#define EDGES_SEP "//edges"
#define DIR_EDGE "->"
#define UNDIR_EDGE "--"
#define NODE_INCL_CLR "blue"
#define NODE_NOT_INCL_CLR "black"
#define EDGE_INCL_CLR "blue"
#define EDGE_NOT_INCL_CLR "black"
class Node {
	
	public:
	
		Node(string nodeName) {
			this->nodeName = nodeName;
			distFrmSrc = MAX_VALUE;
			noOfPathsFrmSrc = 0;
			inclInPath = false;
			predecessors = new vector<Node*>();
			
		}
				
		string getNodeName() {
			return 	nodeName;	
		}
		
		int getDistFrmSrc(){
			return 	distFrmSrc;	
		}
		
		void setDistFrmSrc(int distFrmSrc) {
			this->distFrmSrc = distFrmSrc;	
		}
		
		int getNoOfPathsFrmSrc(){
			return 	noOfPathsFrmSrc;	
		}
		
		void setNoOfPathsFrmSrc(int noOfPathsFrmSrc) {
			this->noOfPathsFrmSrc = noOfPathsFrmSrc;	
		}
		
		string toString() {
			ostringstream oss;
			oss<<nodeName<<" dist "<<distFrmSrc<< " paths "<<noOfPathsFrmSrc;
			return oss.str();
		}
		
		int compareTo(Node* toCompare) {
			int compare;
			if(distFrmSrc < toCompare->distFrmSrc) {
				compare = LESSER;
			} else if(distFrmSrc == toCompare->distFrmSrc) {
				compare = EQUAL;
			} else {
				compare = GREATER;
			}
			return compare;
		}
		
		vector<Node*>* getPredecessors() {
			return predecessors;
		}
		
		void setPredecessors(vector<Node*>* preds) {
			 predecessors = preds;
		}
		
		bool getInclInPath() {
			return inclInPath;
		}
		
		void setInclInPath(bool include) {
			inclInPath = include;
		}
		
		string getGraphString() {
			ostringstream oss;
			oss<<nodeName<<" [label=\""<<nodeName;
			if(inclInPath)
				oss<<" ("<<noOfPathsFrmSrc<<" "<<"sp)";
			oss<<"\"";
			oss<<",color=";
			if(inclInPath) {
				oss<<NODE_INCL_CLR;
			} else {
				oss<<NODE_NOT_INCL_CLR;
			}
			oss<<",penwidth = 2.0];";
			return oss.str();
		}
		
		private:	
		string nodeName;
		int distFrmSrc;
		int noOfPathsFrmSrc;
		vector<Node*>* predecessors;
		bool inclInPath;
};

class MinHeap {
	private:
		int size;
		vector<Node*> nodes;
		map<Node*,int>* nodeVsIndex;
	public:
		MinHeap(vector<Node*> nodes) {
			this->nodes = nodes;
			size = nodes.size();
			nodeVsIndex = new map<Node*,int>();
			for(int i=0;i<nodes.size();i++) {
				nodeVsIndex->insert ( pair<Node*,int>(nodes[i],i) );
			}
		}
		
		int getSize() {
			return size;
		}
		
		static int getParentIdx(int idx) {
			return ((idx + 1)/2)-1;
		}

		static int getLeftChildIdx(int idx) {
			return (idx*2)+1;
		}

		static int getRightChildIdx(int idx) {
			return ((idx + 1)*2);
		}
		
		void swap(int idx1,int idx2) {
			Node* temp = nodes[idx1];
			nodes[idx1] = nodes[idx2];
			nodes[idx2] = temp;
			
			(*nodeVsIndex)[nodes[idx1]] = idx1;
			(*nodeVsIndex)[nodes[idx2]] = idx2;
		}
		
		bool isValidIdx(int idx) {
			return idx <=(size-1);
		}
		
		void heapify(int index){
			Node* eleAtIdx = nodes[index];
			int leftIdx = getLeftChildIdx(index);
			int rightIdx = getRightChildIdx(index);
			if(isValidIdx(leftIdx)) {
				if(isValidIdx(rightIdx)) {
					int minIdx = index;
					if(nodes[leftIdx]->compareTo(eleAtIdx) == LESSER) {
						minIdx = leftIdx;
					}
					if(nodes[rightIdx]->compareTo(nodes[minIdx]) == LESSER) {
						minIdx = rightIdx;
					}
					if(minIdx != index) {
						swap(minIdx,index);
						heapify(minIdx);
					}
				} else {
					if(nodes[leftIdx]->compareTo(eleAtIdx) == LESSER) {
						swap(index,leftIdx);
						heapify(leftIdx);
					}
				}
			}
		}
		
		void decreaseKey(Node* ele,int newKey) {
			int idx = nodeVsIndex->at(ele);
			int oldKey = nodes[idx]->getDistFrmSrc();
			if(newKey >= oldKey) {
				throw "Cannot decrease key";
			} else {
				int parentIdx = getParentIdx(idx);
				Node* parentKey = nodes[parentIdx];
				Node* keyItr = ele;
				keyItr->setDistFrmSrc(newKey);
				while(( parentIdx>=0 && parentKey->compareTo(keyItr) == GREATER)) {
					swap(parentIdx,idx);
					idx = parentIdx;
					parentIdx = getParentIdx(parentIdx);
					if(parentIdx < 0)
						break;
					keyItr = nodes[idx];
					parentKey = nodes[parentIdx];
				}
			}	
		}
		
		Node* extractMin() {
			if(size == 0)
				throw "heap is empty";
			 Node* ele = nodes[0];
			 swap(0,size-1);
			 size--;
			 heapify(0);
			 return ele;
		}
		
};
class Edge {
	public:
		
		Edge(Node* start,Node* end,int length) {
			this->start = start;
			this->end = end;
			this->length = length;
			inclInPath = false;
		}
		
		Node* getStart() {
			return start;
		}

		Node* getEnd() {
			return end;
		}
		
		int getLength() {
			return length;
		}
		
		Node* getDestinationVertex(Node* srcVertex,bool directed) {
			if(directed) {
				return end;
			} else {
				if(start == srcVertex) {
					return end;
				}
				return start;
			}
		}
		
		bool isEqual(Edge* edge) {
			bool equal = ((start == edge->start) && (end == edge->end) && (length == edge->length));
			return equal;
		}
		
		bool getInclInPath() {
			return inclInPath;
		}
		
		void setInclInPath(bool include) {
			inclInPath = include;
		}
		
		string getGraphString(bool directed) {
			ostringstream oss;
			oss<<start->getNodeName();//<<" [label=\""<<" "<<len;
			oss<<" ";
			if(directed) {
				oss<<DIR_EDGE;
			} else {
				oss<<UNDIR_EDGE;
			}
			oss<<" ";
			oss<<end->getNodeName();
			oss<<" [label=\""<<length<<"\"";
			oss<<",color=";
			if(inclInPath) {
				oss<<EDGE_INCL_CLR;
			} else {
				oss<<EDGE_NOT_INCL_CLR;
			}
			oss<<",penwidth = 2.0];";
			return oss.str();
		}
		
	private:
		
		Node* start;
		Node* end;
		int length;
		bool inclInPath;
		
};
class Graph {
	
	private:
		string graphName;
		bool directed;
		Node* source;
		Node* sink;
		vector<Edge*> edges;
		vector<Node*> nodes;
		map<Node*,vector<Edge*>* >* nodeVsEdges;
	
		static Node* getNodeFromName(vector<Node*> nodes,string name) {
				Node* node = NULL;
				for(int i=0;i<nodes.size();i++) {
					node = nodes.at(i);
					if(node->getNodeName() == name)
						return node;
				}
				return NULL;
		}
		
		static vector<string> getStringsInLine(string inputLine) {
			istringstream iss;
			iss.str(inputLine);
			vector<string> words;
			while(iss.good()) {
				string str;
				iss>>str;
				if(str.length() > 0) {
					words.push_back(str);
				}
			}
			return words;
		}
	
		void addNode(Node* node,int index) {
			vector<Edge*>* edges = new vector<Edge*>();;
			nodeVsEdges->insert (pair<Node*,vector<Edge*>* >(node,edges));
		}
		
		void addEdge(Edge* edge) {
			Node* start = edge->getStart();
			if(start != NULL) {
				vector<Edge*>* edges = nodeVsEdges->at(start);
				edges->push_back(edge);
				dout<<"Pushed an edge in "<<start->getNodeName()<<endl;
				dout<<"size is "<<nodeVsEdges->at(start)->size()<<endl;
				//}
					
				if(!directed) {
					edges = nodeVsEdges->at(edge->getEnd());
					edges->push_back(edge);
					dout<<"Pushed an edge in "<<edge->getEnd()->getNodeName()<<endl;
					dout<<"size is "<<nodeVsEdges->at(edge->getEnd())->size()<<endl;
					//}
				}
			}
		}	
		
		static bool isEdgeExists(vector<Edge*> edges,Edge* edge) {
			for(int i=0;i<edges.size();i++) {
				if(edge->isEqual(edges.at(i))) {
					return true;
				}
			}
			return false;
		}
		
		void updateInclInfo(Node* vertex) {
			if(!vertex->getInclInPath()) {
				//flag the node
				vertex->setInclInPath(true);
				vector<Node*>* pred = vertex->getPredecessors();
				if(pred->size() > 0) {
					for(int i = 0;i< pred->size();i++) {
						Node* predVertex = pred->at(i);
						//flag the edge
						vector<Edge*>* edges = nodeVsEdges->at(predVertex);
						for(int j = 0;j< edges->size();j++) {
							Edge* edge = edges->at(j);
							if((edge->getStart() == vertex)||
								(edge->getEnd() == vertex)) {
								edge->setInclInPath(true);
							}
						}
						if(!predVertex->getInclInPath()) {
							updateInclInfo(predVertex);
						}
					}
				}
			}
		}
		
		
	public:
		Graph(){
			nodeVsEdges = new map<Node*,vector<Edge*>* >();
		}
		
		void initGraph(vector<Node*> nodes,vector<Edge*> edges) {
			this->nodes = nodes;
			this->edges = edges;
			for(int i = 0;i<nodes.size();i++) {
				addNode(nodes.at(i),i);		
			}
			for(int i = 0;i<edges.size();i++) {
				addEdge(edges.at(i));		
			}
			source = nodes.at(0);
			sink = nodes.at(nodes.size()-1);
		}
		
		void calcShortestPath() {
			source->setDistFrmSrc(0);
			source->setNoOfPathsFrmSrc(1);
			MinHeap minHeap(nodes);
			Node* minNode = NULL;
			while(minHeap.getSize() > 0) {
				minNode = minHeap.extractMin();
				vector<Edge*>* edgesFrmMin = nodeVsEdges->at(minNode);
				int distance;
				for(int i=0;i<edgesFrmMin->size();i++) {
					Edge* edge = edgesFrmMin->at(i);
					Node* destVertex;
					int distFrmSrcDest;
					if(edge != NULL) {
						//d(u) + w(u,v)
						distance = minNode->getDistFrmSrc() + edge->getLength();
						destVertex = edge->getDestinationVertex(minNode,directed);
						//d(v)
						distFrmSrcDest = destVertex->getDistFrmSrc();
						//d(u) + w(u,v) < d(v)
						if(distance < distFrmSrcDest) {
							minHeap.decreaseKey(destVertex,distance);
							destVertex->setNoOfPathsFrmSrc(minNode->getNoOfPathsFrmSrc());
							vector<Node*>* predecessors= destVertex->getPredecessors();
							predecessors->clear();
							predecessors->push_back(minNode);
						} else if(distance == distFrmSrcDest) {
							int noOfPaths = minNode->getNoOfPathsFrmSrc() +
								destVertex->getNoOfPathsFrmSrc();
							destVertex->setNoOfPathsFrmSrc(noOfPaths);	
							vector<Node*>* predecessors= destVertex->getPredecessors();
							predecessors->push_back(minNode);
						}
					}
					 
				}
			}
			int distFrmSrcToSink = sink->getDistFrmSrc();
			if(distFrmSrcToSink == MAX_VALUE) {
				//cout<<numeric_limits<float>::infinity();
				cout<<"∞";
			} else {
				cout<<sink->getDistFrmSrc();
			}
			//cout<<sink->getDistFrmSrc()
			cout<<" "<<sink->getNoOfPathsFrmSrc()<<endl;
			updateInclInfo(sink);
		}
		
		void writeOutputFile(string outputFile) {
			ostringstream oss;
			//1st line
			if(directed) {
				oss<<DIR_GRAPH_KEYWORD;
			} else {
				oss<<GRAPH_KEYWORD;
			}
			oss<<" "<<graphName<<"_no_of_paths {"<<endl;
			
			//nodes sep
			oss<<NODES_SEP<<endl;
			//print nodes
			
			int distFrmSrc = sink->getDistFrmSrc();
			bool pathExists = (sink->getNoOfPathsFrmSrc() !=0);
			
			if(nodes.size() == 1) {
				//print src and dest
				oss<<source->getNodeName()<<" [label=\""<<source->getNodeName()<<" (source) (destination) ";
				oss<<"("<<sink->getNoOfPathsFrmSrc()<<" sp)\"";
				oss<<",color="<<(pathExists?NODE_INCL_CLR:NODE_NOT_INCL_CLR);
				oss<<",penwidth=2.0];"<<endl;
				
			} else {
			
			//print src
			oss<<source->getNodeName()<<" [label=\""<<source->getNodeName()<<" (source)\"";
			oss<<",color="<<(pathExists?NODE_INCL_CLR:NODE_NOT_INCL_CLR);
			oss<<",penwidth=2.0];"<<endl;
			
			//print intermediate
			for(int i=1;i<nodes.size()-1;i++) {
				Node* node = nodes[i];
				oss<<node->getGraphString()<<endl;
			}
			
			//print sink
			oss<<sink->getNodeName()<<" [label=\""<<sink->getNodeName()<<" (destination) (";
			oss<<sink->getNoOfPathsFrmSrc()<<" sp)\"";
			oss<<",color="<<(pathExists?NODE_INCL_CLR:NODE_NOT_INCL_CLR);
			oss<<",penwidth=2.0];"<<endl;
			
			}
				
			//edges sep
			oss<<EDGES_SEP<<endl;
			
			//print edges
			for(int i=0;i<edges.size();i++) {
				Edge* edge = edges[i];
				oss<<edge->getGraphString(directed)<<endl;
			}
			
			//print last line
			oss<<"}";
			
			ofstream op_stream;
			op_stream.open (outputFile.c_str());
			op_stream<<oss.str();
			op_stream.close();
			
		}
		void readInputFile(string inputFile) {
			
			vector<Node*> nodes;
			vector<Edge*> edges;
			
			ifstream in;
			in.open(inputFile.c_str());
			string inputLine;
			bool validLine = getline(in, inputLine);
			vector<string> words;
			if(validLine) {
				words = getStringsInLine(inputLine);
				if(words.size() == 3) {
					if(words.at(0) == GRAPH_KEYWORD) {
						directed = false;
					} else {
						directed = true;
					}
					graphName = words.at(1);
				}
			}
			validLine = getline(in, inputLine);
			if(inputLine == NODES_SEP) {
				string vertexName = "";
				while(getline(in, inputLine) && inputLine !=EDGES_SEP) {
					if(inputLine.length() > 0) {
						char lastCh = inputLine.at(inputLine.length() - 1);
						if(lastCh == ';') {
							vertexName = inputLine.substr(0,inputLine.length()-1);
							Node* node = new Node(vertexName);
							nodes.push_back(node);
						}
					}
				}
			}
			if(inputLine == EDGES_SEP) {
				Node *start,*end;
				int firstOccur,lastOccur,length; 
				Edge *edge;
				while(getline(in, inputLine) && inputLine !="}") {
					if(inputLine.length() > 0) {
						words = getStringsInLine(inputLine);
						start = getNodeFromName(nodes,words.at(0));
						end = getNodeFromName(nodes,words.at(2));
						firstOccur = words.at(3).find_first_of('\"',0);
						lastOccur = words.at(3).find_last_of('\"');
						string subString = words.at(3).substr(firstOccur+1,lastOccur-firstOccur-1);
						length = atoi(subString.c_str());
						if(start !=NULL && end!=NULL) {
							edge = new Edge(start,end,length);
							edges.push_back(edge);
						}
					}
				}
			}
			initGraph(nodes,edges);
		}
	
};

int main(int argc,char* argv[]) {
	if(argc == 3) {
		Graph* graph = new Graph();
		graph->readInputFile(argv[1]);
		graph->calcShortestPath();
		graph->writeOutputFile(argv[2]);
		
	} else {
		cout<<"Invalid arguments.";
		cout<<" Correct syntax $<executable> <input dot file> <output dot file>"<<endl;
	} 
	return 0;
	
}
