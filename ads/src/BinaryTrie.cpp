#include <iostream>
#include <string>
#include "BinaryTrie.h"
#include <deque>
using namespace std;

bool binaryTrie::insert(string str,int np){
		if(str.empty()){
			cout<<"The string is empty!"<<endl;
			return false;
		}
		trieNode *tmp = root;
		int bittmp;
		for(int i=0;i<str.length()-1;i++){
			bittmp = tmp->bit;
			if(str[bittmp]=='0'){
				if(tmp->lChild==NULL){
					tmp->lChild = new trieNode(false,i+1,"",-1,tmp,NULL,NULL);
				}
				tmp = tmp->lChild;
			}else if(str[bittmp]=='1'){
				if(tmp->rChild==NULL){
					tmp->rChild = new trieNode(false,i+1,"",-1,tmp,NULL,NULL);
				}
				tmp = tmp->rChild;
			}else{
				cout<<"Invalid ip bit!"<<endl;
				return false;
			}
		}
		bittmp = str.length()-1;
		if(str[bittmp]=='0'){
			if(tmp->lChild==NULL){
				tmp->lChild = new trieNode(true,-1,str,np,tmp,NULL,NULL);
			}else{
				if(str.compare(tmp->lChild->value)==0)cout<<"This element has occured!"<<endl;
				else cout<<"Error occured!"<<endl;
				}
		}else if(str[bittmp]=='1'){
			if(tmp->rChild==NULL){
				tmp->rChild = new trieNode(true,-1,str,np,tmp,NULL,NULL);
			}else{
				if(str.compare(tmp->rChild->value)==0)cout<<"This element has occured!"<<endl;
				else cout<<"Error occured!"<<endl;
				}
		}else{
				cout<<"Invalid ip bit!"<<endl;
				return false;
		}
		return true;
}

trieNode* binaryTrie::search(string str){
		if(str.empty()){
			cout<<"The string is empty!"<<endl;
			return NULL;
		}
		trieNode *tmp = root;
		int bittmp;
		while(tmp->isElement!=true){
			if(tmp==NULL){
				cout<<"No such node!"<<endl;
				return NULL;
			}
			bittmp = tmp->bit;
			if(str[bittmp]=='0'){
				if(tmp->lChild==NULL){
					cout<<"No such node!"<<endl;
					return NULL;
				}else 
					tmp = tmp->lChild;
			}else if(str[bittmp]=='1'){
				if(tmp->rChild==NULL){
					cout<<"No such node!"<<endl;
					return NULL;
				}else 
					tmp = tmp->rChild;
			}else{
				cout<<"Invalid ip bit!"<<endl;
				return NULL;
			}
		}
		std::size_t found = tmp->value.find('*');
		if(found!=std::string::npos){
			string substr1=str.substr(0,found);
			string substr2=tmp->value.substr(0,found);
			if(substr2.compare(substr1)==0){
				//cout<<"Found it!"<<endl;
				return tmp;
			}else{
			cout<<"No such node!"<<endl;
			return NULL;
			}
		}else if(str.compare(tmp->value)==0){
					//cout<<"Found it!"<<endl;
					return tmp;
		}else{
			cout<<"No such node!"<<endl;
			return NULL;
		}
		return NULL;
}

bool binaryTrie::Merge(){
	postOrdExamine(root);
	return true;
}

bool binaryTrie::postOrdExamine(trieNode *pLoc){
	if(pLoc){
		if(pLoc->lChild)postOrdExamine(pLoc->lChild);
		if(pLoc->rChild)postOrdExamine(pLoc->rChild);
		if(pLoc->lChild && pLoc->rChild&&pLoc->lChild->isElement && pLoc->rChild->isElement){
			if(pLoc->lChild->nextHop==
				pLoc->rChild->nextHop){
					string substr = pLoc->lChild->value.substr(0,pLoc->bit)+'*';							
					pLoc->isElement = true;
					pLoc->bit = -1;
					pLoc->value = substr;
					pLoc->nextHop= pLoc->rChild->nextHop;
					trieNode *tmp1 = pLoc->lChild;
					trieNode *tmp2 = pLoc->rChild;
					pLoc->lChild = NULL;
					pLoc->rChild = NULL;
					delete tmp1;
					delete tmp2;
					return true;
					}
		}else if(pLoc->lChild && NULL==pLoc->rChild &&pLoc->lChild->isElement){						
					pLoc->isElement = true;
					pLoc->bit = -1;
					pLoc->value = pLoc->lChild->value;
					pLoc->nextHop= pLoc->lChild->nextHop;
					trieNode *tmp1 = pLoc->lChild;
					trieNode *tmp2 = pLoc->rChild;
					pLoc->lChild = NULL;
					pLoc->rChild = NULL;
					delete tmp1;
					delete tmp2;
					return true;
		}else if(pLoc->rChild && NULL==pLoc->lChild &&pLoc->rChild->isElement){
					pLoc->isElement = true;
					pLoc->bit = -1;
					pLoc->value = pLoc->rChild->value;
					pLoc->nextHop= pLoc->rChild->nextHop;
					trieNode *tmp1 = pLoc->lChild;
					trieNode *tmp2 = pLoc->rChild;
					pLoc->lChild = NULL;
					pLoc->rChild = NULL;
					delete tmp1;
					delete tmp2;
					return true;
		}
	}else{
		return true;
	}
}

