#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <climits>
#include "AdjGraph.h"
#include "Fibonacci.h"
#include <set>
class pathNode{	
public:
	int weight;
	int vex;
	pathNode(){
		weight = 0.0;
		vex = 0;
	}
	pathNode(int w, int v){
		weight = w;
		vex = v;
	}
	pathNode &operator = (const pathNode &nodeB){
		weight = nodeB.weight;
		vex = nodeB.vex;
		return *this;
	}
	bool operator < (pathNode nodeB){
		return (weight<nodeB.weight);
	}
	
	bool operator > (pathNode nodeB){
		return (weight>nodeB.weight);
	}
	
	bool operator <= (pathNode nodeB){
		return (weight<=nodeB.weight);
	}

	
	bool operator >= (pathNode nodeB){
		return (weight>=nodeB.weight);
	}
	
	bool operator == (pathNode nodeB){
		return (weight==nodeB.weight);
	}


};
//Graph and source node v are given, then *prev, *dist, *nextHop are calculated
//In array prev, prev[i] stores the previous node before i in the path from v to i
//In array dist, dist[i] stores the distance of the path from v to i
//In array nextHop, nextHop[i] stores the next node after v in the path from v to i
void ShortestPaths(AdjGraph *graph, int v, int *prev,int *dist,int *nextHop)
{
	int numofVex = graph->numV;
	long * heapNodeAddList = (long *)malloc(sizeof(char*)* numofVex);
	FibonacciHeap<pathNode> disHeap; 
	set<int> S;
	for(int i=0;i< numofVex ;i++){
		dist[i] = INT_MAX;
		prev[i] = -1;
		pathNode tmpNode(dist[i],i);
		heapNodeAddList[i] = reinterpret_cast<long>(disHeap.insert(tmpNode));
	}
	prev[v] = v;
	dist[v] = 0;
	 
	pathNode newNode(0,v);					
	disHeap.decreaseKey(reinterpret_cast<heapNode<pathNode>*>(heapNodeAddList[v]),newNode);
	
	while(!disHeap.isEmpty()){
		int u = disHeap.removeMinimum().vex;
		S.insert(u);
		  // Determine n - 1 paths from v.
         /* Choose u from among those vertices not
               in S such that dist[u] is minimum;*/
		  AdjListNode* pCrawl = graph->vexList[u].head;
		  while (pCrawl != NULL){
			  int tmpv = pCrawl->dest;
			  // If shortest distance to v is not finalized yet, and distance to v
			  // through u is less than its previously calculated distance
			  //!S[tmpv] &&
			  if (dist[u] != INT_MAX && 
                     pCrawl->weight + dist[u] <= dist[tmpv]){
					 dist[tmpv] = dist[u] + pCrawl->weight;
					 
					 // update distance value in min heap also
					 pathNode newNode(dist[tmpv],tmpv);			
					if(S.find(tmpv)==S.end()){
						//tmpv has not removed from the heap;
						disHeap.decreaseKey(reinterpret_cast<heapNode<pathNode>*>(heapNodeAddList[tmpv]),newNode);
					}
					 prev[tmpv] = u;
            }
		pCrawl = pCrawl->next;
        }
    }
	for(int i=0;i<numofVex;i++){
		int src = v;
		int dst = i;
		if(src==dst)nextHop[i] = i;
		else{
			int pre = prev[dst];
			int np = dst;
			while(pre!=src){				
				if(pre<0){
					np=-1;
					break; 
				}
				np = pre;
				pre = prev[pre];
			}
			nextHop[i] = np;
		}
	}
	
}

#endif
