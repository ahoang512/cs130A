#include<cstdio>
#include <iostream>
#include <string>
#include "huffmanencoding.cpp"

using namespace std;

//Trie Class--------------------------------------//

class Trie{
	private:
		Letter *root;

	//-----Methods-----//	
		void codeMap(Letter *, string *);  //head is private variable so can only pass in head within Trie
		void getCode(Letter *, int, string*); 
		void decode(Letter*,int*, int);


	public:
	//-----Constructor-----/
		Trie(Letter *, int); //input sorted array and its length
	
	//-----Methods-----//	
		void getCode(int, string *);
		void codeMap(string *);    
		void printEncoded(int *, int);
		void decode(int *, int);
};



//----------Implementation----------//

Trie::Trie(Letter *array, int count){  //Constructor
	int filled = count;
	Letter *first, *second, *head;
	first = new Letter[count-1];
	second = new Letter[count-1];
	head = new Letter[count-1];
	
	int i = 0;
	while(filled > 1){
	first[i] = deleteMin(array,count);
	second[i] = deleteMin(array,count);
	head[i].right = &first[i];
	head[i].left = &second[i];
	head[i].setNum(first[i].getNum() + second[i].getNum());
	head[i].setAsc(-2);
	insertTrie(head[i],array,count);

	filled--;
	i++;
	}
	Letter h = deleteMin(array,count);
	this->root = &h;
}

void Trie::codeMap(string *c){
	codeMap(root,c);
}
void Trie::codeMap(Letter *l,string *c){
	string *left = c;
	string *right = c;
	if((l->getAsc()==-2)){
		left->append("1");
		codeMap(l->left,left);
		right->append("0");
		codeMap(l->right,right);
	}else{
		l->path.append(c->c_str());
		printf("%s : %c\n",c->c_str(), l->getAsc());
	}
}

void Trie::getCode(int l, string *s){
	getCode(root,l,s);
}

void Trie::getCode(Letter *trie, int l, string *s){
	if((trie->getAsc()==-2)){
		getCode(trie->left,l,s);
		getCode(trie->right,l,s);
	}else if(trie->getAsc() == l){
		s->append(trie->path);
		return;
	}
	return;
}

void Trie::decode(int *buffer, int length){
	decode(root,buffer,length);
}
void Trie::decode(Letter *trie, int *buffer, int length){
	Letter *travel = trie;
	int i=0;
	while(i < length){
		while(travel->getAsc() == -2){
			if(buffer[i] == 49){
				travel = travel->left;
				i++;
			}
			else if(buffer[i] == 48){
				travel = travel->right;
				i++;
			}
		}
		printf("%c",travel->getAsc());
		
		travel = trie;
	}
	cout << "\n";
}

void Trie::printEncoded(int *buffer,int count){ //prints I Like Apples in encoded form
	string *code = new string();
	for(int i=0;i < count;i++){
		getCode(root,buffer[i], code);
	}
	cout << *code + "\n";
	
}






