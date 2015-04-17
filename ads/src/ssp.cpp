#include <stdio.h>
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include "Fibonacci.h"
#include "Dijkstra.h"
#include "AdjGraph.h"
using namespace std;

int main(int argc, char *argv[]){
	if(argc!=4){
		cerr<<"Not enough arguments followed by ./ssp"<<endl;
		exit(0);
	}
	clock_t start;
	start = clock();
	// Get Graph
	ifstream infile;
	string n_tmp;
	string m_tmp;
	string k_tmp;
	char inputf [50];
	sprintf(inputf,"../data/%s",argv[1]);
	infile.open(inputf);
	getline(infile,n_tmp,' ');
	getline(infile,m_tmp,'\n');
	static int numOfVex = stoi(n_tmp);
	static int numOfEdge = stoi(m_tmp);
	
	int n;
	int m;
	int k;
	AdjGraph *graph=new AdjGraph(numOfVex);
	while(!infile.eof()){
		n_tmp.clear();
		m_tmp.clear();
		k_tmp.clear();
		getline(infile,n_tmp,' ');
		getline(infile,m_tmp,' ');
		getline(infile,k_tmp,'\n');
		if(n_tmp.length()&&m_tmp.length()&&k_tmp.length()){
			n = stoi(n_tmp);
			m = stoi(m_tmp);
			k = stoi(k_tmp);
			if(n!=m){
				graph->addEdge(n,m,k);
			}
		}
	}
	//Calculate the shortest paths
	int *dist = new int[numOfVex];
	int *prev = new int[numOfVex];
	int *nextHop = new int[numOfVex];
	int src = atoi(argv[2]);
	int dst = atoi(argv[3]);
	if(dst>=numOfVex){
		cerr<<"Illegal index of nodes!"<<endl;
		exit(0);
		}
	ShortestPaths(graph,src,prev,dist,nextHop);

	vector<int> path;
	path.push_back(dst);

	int pre=dst;
	while(pre!=src){
		pre = prev[pre];
		if(pre<0)break;
		path.push_back(pre);
	}
	if(path.size()==1){
			cout<<"There isn no legal path found!"<<endl;
	}else{
		//make the path: src->...->dst
		reverse(path.begin(),path.end());
		//cost from source to destination
		cout<<dist[dst]<<endl;
		//print nodes in the path
		for(int i=0;i<path.size();i++){
			cout<<path[i]<<" ";
		}
	}
	cout<<endl;
	double duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    cout<<"Duration: "<< duration <<"seconds\n";
	return 0;
}
