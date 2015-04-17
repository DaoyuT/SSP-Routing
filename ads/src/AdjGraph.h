#ifndef ADJGRAPH_H
#define ADJGRAPH_H

#include <iostream>
using namespace std;
// A structure to represent an adjacency list node
struct AdjListNode{
	AdjListNode(int d,int w){
		dest = d;
		weight = w;
		next = NULL;
	}
	AdjListNode(int d, int w, AdjListNode *tmpN){
		dest = d;
		weight = w;
		next = tmpN;
	}

    int dest;
	int weight;
	AdjListNode* next;
};
 
// A structure to represent an adjacency liat
struct AdjList{
    AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
class AdjGraph{	
public: 
    int numV;
    AdjList* vexList;
	// A utility function that creates a graph of V vertices
	AdjGraph(int n=0){ 
		// Create an array of adjacency lists.  Size of array will be V
		numV = n;
		vexList = (AdjList*) malloc(n*sizeof(AdjList));
		for (int i = 0; i < numV; ++i)vexList[i].head = NULL;
	}
	// Adds an edge to an undirected graph
	void addEdge(int src, int dest, int w){
		// Add an edge from src to dest.  A new node is added to the adjacency
		// list of src.  The node is added at the begining
		AdjListNode *newNode = new AdjListNode(dest,w);
		if(vexList[src].head==NULL){			
			newNode->next=NULL; 
			vexList[src].head = newNode; 
		}else{
			newNode->next = vexList[src].head;
			vexList[src].head = newNode; 
		}
		// Since graph is undirected, add an edge from dest to src also
		newNode = new AdjListNode(src,w);
		if(vexList[dest].head==NULL){			
			newNode->next=NULL; 
			vexList[dest].head = newNode; 
		}else{
			newNode->next = vexList[dest].head;
			vexList[dest].head = newNode; 
		}
	}
	// A utility function to print the adjacenncy list representation of graph
	void printGraph(){
		for (int indV = 0; indV < numV; ++indV){        
			AdjListNode* pCrawl = vexList[indV].head;
			cout<<endl<<"Adjacency list of vertex"<<indV<<" head "<<endl;
			while (pCrawl){
				cout<<"->"<<pCrawl->dest;
				pCrawl = pCrawl->next;
			}
		}
	}

};
 

 

#endif