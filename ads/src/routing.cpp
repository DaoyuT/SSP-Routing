#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>
#include "Fibonacci.h"
#include "AdjGraph.h"
#include "Dijkstra.h"
#include "BinaryTrie.h"
using namespace std;

int main(int argc, char* argv[]){
	if(argc!=5){
		cerr<<"Not enough arguments followed by ./routing"<<endl;
		exit(0);
		}
	clock_t start;
	start = clock();
	// Get Graph
	ifstream infile1;
	string n_tmp;
	string m_tmp;
	string k_tmp;
	char inputf1 [50];
	sprintf(inputf1,"../data/%s",argv[1]);
	infile1.open(inputf1);
	getline(infile1,n_tmp,' ');
	getline(infile1,m_tmp,'\n');
	static int numOfVex = stoi(n_tmp);
	static int numOfEdge = stoi(m_tmp);
	int n;
	int m;
	int k;
	AdjGraph *graph=new AdjGraph(numOfVex);
	while(!infile1.eof()){
		n_tmp.clear();
		m_tmp.clear();
		k_tmp.clear();
		getline(infile1,n_tmp,' ');
		getline(infile1,m_tmp,' ');
		getline(infile1,k_tmp,'\n');
		if(n_tmp.length()&&m_tmp.length()&&k_tmp.length()){
			n = stoi(n_tmp);
			m = stoi(m_tmp);
			k = stoi(k_tmp);
			graph->addEdge(n,m,k);
		}
	}
	// Get IP
	ifstream infile2;
	string ip1_tmp;
	string ip2_tmp;
	string ip3_tmp;
	string ip4_tmp;
	int ip1,ip2,ip3,ip4;
	string ip1str;
	string ip2str;
	string ip3str;
	string ip4str;
	string ip_str;
	vector<string> ip_addr;
	char inputf2 [50];
	sprintf(inputf2,"../data/%s",argv[2]);
	infile2.open(inputf2);
	while(!infile2.eof()){
		ip1_tmp.clear();
		ip2_tmp.clear();
		ip3_tmp.clear();
		ip4_tmp.clear();
		getline(infile2,ip1_tmp,'.');
		getline(infile2,ip2_tmp,'.');
		getline(infile2,ip3_tmp,'.');
		getline(infile2,ip4_tmp,'\n');
		if(ip1_tmp.length()&&ip2_tmp.length()&&ip3_tmp.length()&&ip4_tmp.length()){
			ip1 = stoi(ip1_tmp);
			ip2 = stoi(ip2_tmp);
			ip3 = stoi(ip3_tmp);
			ip4 = stoi(ip4_tmp);
			bitset<8> ip1bit(ip1);
			bitset<8> ip2bit(ip2);
			bitset<8> ip3bit(ip3);
			bitset<8> ip4bit(ip4);
			ip1str = ip1bit.to_string();
			ip2str = ip2bit.to_string();
			ip3str = ip3bit.to_string();
			ip4str = ip4bit.to_string();

			ip_str = ip1bit.to_string() + ip2bit.to_string()
				+ ip3bit.to_string()+ ip4bit.to_string();

			ip_addr.push_back(ip_str.c_str());
		}
	}
	// Build Router Table
	int *dist = new int[numOfVex];//distance
	int *prev = new int[numOfVex];//previous node

	int *nextHop= new int[numOfVex];
	int src = atoi(argv[3]); 
	int dst = atoi(argv[4]);
	if(src>=numOfVex||dst>=numOfVex){
		cerr<<"Illegal index of nodes!"<<endl;
		exit(0);
	}
	vector<int> path;
	path.push_back(dst);
	//calculate all shortest paths from source node
	ShortestPaths(graph,src,prev,dist,nextHop);	
	int pre=dst;
	//from destination to source, push all the node into path
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
		//construct router table for each node in the path
		for(int ind=0;ind<path.size()-1;ind++){
			int tmpSrc = path[ind];
			string tmpIp = ip_addr[dst];
			ShortestPaths(graph,tmpSrc,prev,dist,nextHop);
			binaryTrie tmpBT;
			//for every node
			for(int jnd=0;jnd<numOfVex;jnd++){
				//j is not tmpSrc
				if(jnd!=tmpSrc){
					//insert node of IP == jnode and nextHop after tmpSrc form tmpSrc to jnode
					tmpBT.insert(ip_addr[jnd],nextHop[jnd]);
				}
			}
			tmpBT.Merge();
			//search for destination IP and print IP address
			trieNode *tmpNode = tmpBT.search(tmpIp);
			int tmpInd = tmpNode->parent->bit;
			string tmpIP = ip_addr[dst];
			cout<<" "<<tmpIP.substr(0,tmpInd+1)<<" ";
		}
		cout<<endl;
	}
	double duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    cout<<"Duration: "<< duration <<"seconds\n";
	return 0;
}
