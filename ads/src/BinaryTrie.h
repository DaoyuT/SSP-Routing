#ifndef BINARYTRIE_H
#define BINARYTRIE_H
#include <iostream>
#include <string>
using namespace std;
class trieNode{
public:
	bool isElement;
	int bit;//starting from 0
	string value;
	int nextHop;
	trieNode *lChild;
	trieNode *rChild;
	trieNode *parent;
	trieNode(bool e = false,int b=-1,string v="",int nh=-1,trieNode *p=NULL,trieNode *l=NULL,trieNode *r=NULL){
		isElement = e;
		bit = b;
		value=v;
		nextHop = nh;	
		parent=p;
		lChild = l;
		rChild = r;
	}
	~trieNode(){
	}
};
class binaryTrie{

private:
	trieNode *root;	
	bool postOrdExamine(trieNode *);
public:
	binaryTrie(){
		root=new trieNode(false,0,"",-1,NULL,NULL,NULL);
	}
	bool insert(string,int);
	trieNode *search(string);
	bool Merge();
};
#endif
