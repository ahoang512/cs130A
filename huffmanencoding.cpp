//Anthony Hoang and Charles Chain
#include<cstdio>
#include <iostream>
#include <string>

using namespace std;

//Letter Class--------------------------------------------
class Letter{
	private:
  		int asc;	       
 		int num;

	public:
		Letter();
		Letter(int a, int n);
		Letter(const Letter& );
		int getAsc();
		int getNum();
  		Letter *left;
  		Letter *right;
		std::string path;
		void setAsc(int a);
		void setNum(int n);
		bool isTrie();
};

Letter::Letter(){
		asc =  -1;
		num = 0;
		left = NULL;
		right = NULL;
		path = "";
}

Letter::Letter(const Letter& l){
  asc = l.asc;
  num = l.num;
  left = l.left;
  right = l.right;
  path = l.path;
}

Letter::Letter(int a, int n){
	asc = a;
	num = n;
	left = NULL;
	right = NULL;
	path = "";
}

int Letter::getAsc(){
		return asc;	
}

int Letter::getNum(){
		return num;
}

void Letter::setAsc(int a){
	asc = a;
}

void Letter::setNum(int n){
	num = n;
}

bool Letter::isTrie(){
	if(left == NULL && right == NULL)
		return false;
	return true;
}


//main methods------------------------------------------------------------------------
void printHeap(Letter *sorted,int  count ){
	for (int i = 0 ; i <count; i++){
	if(sorted[i].isTrie()){
		cout << "Trie ";
		printf(" count: %i\n",sorted[i].getNum());
	}
	else if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
}
printf("\n\n"); 
}

// returns number of unique characters
int getUniqueCount(int *alpha, int sp){
	int count = 0;
	for(int i = 0; i <26; i++){
		if(alpha[i] != 0){

			count +=1;
		}
	}
	if(sp!=0){
		count += 1;
	}

	return count;

}

// turns alpha array into Letter array with only used characters
void shrinkArray(Letter* unsorted,int *alpha, int sp){
	int i;
	int j = 0;
	for(i = 0; i < 26 ; i++){
		if(alpha[i] != 0){
			unsorted[j].setAsc(i+97); //adding non zero values to array
			unsorted[j].setNum(alpha[i]); // add the count for each character
			j++;
		}
	}
	unsorted[j].setAsc(32); // add 'space' to last spot in array
	unsorted[j].setNum(sp); // add count for space

}

int readIn(int *alpha, int sp){
	int letter = getchar();
	while (letter != EOF){	
		// check if a-z
		if (letter >= 97 && letter <= 122){		
			alpha[letter-97] += 1;
		}
		//check for spaces	
		if (letter == 32){
				sp++;
		}
		
		letter = getchar();
	}
	return sp;
}

void sortArray(Letter *sorted, Letter *unsorted, int count){
	Letter *lowest;
	lowest = new Letter(100, 100);
	int k; //keeps track of where in unsorted the lowest was so we can lazy delete it
	int filled;
for(filled=0; filled < count; filled++){
	for(int i = 0 ; i<count; i++){
		
		if(unsorted[i].getNum() < lowest->getNum()){ // checks num
			*lowest = unsorted[i];	
			k=i;
		}else if(unsorted[i].getNum() == lowest->getNum()){ // if num are equal
			
			if(unsorted[i].getAsc() < lowest->getAsc()){// check ascii
				*lowest = unsorted[i];
				k=i;
			}
		}
	}

	sorted[filled].setNum(lowest->getNum()); // fill in the sorted array
	sorted[filled].setAsc(lowest->getAsc());
	unsorted[k].setNum(100); // lazy delete
    lowest->setNum(100);// lazy delete
	
}
}

// delete
Letter deleteMin(Letter *array, int count){
  Letter deleted = array[0];
  Letter tmp;
  if(array[0].getNum() == -1){ // check for empty array
    return deleted;
  }
int i;
  for(i=count-1; i>-1; i--){//search array from end
    if (array[i].getNum() != -1){ //check end of array for num = -1
      break;
    }
  }
  // i is the index of the node we want to move to the root.  
  array[0] = array[i];
  array[i].setNum(-1);
  array[i].left = NULL;
  array[i].right = NULL;
  int index = 0;
  //perculate
  if( i == index){ // no children
    return deleted;
  } 
while((2*index+2) < count || (2*index+1)<count ){
	//printf("index: %i\n", index);
  if(array[2*index+2].getNum() == -1 && array[2*index+1].getNum() == -1){
  	//at bottom of heap,
  	return deleted;
  }else if(array[2*index+2].getNum() == -1){ // check for only one child
    if(array[index].getNum() > array[2*index+1].getNum()){ 
    	
      // check if left child is greater then parent
      tmp = array[index];
      array[index]=array[2*index+1];
      array[2*index+1] = tmp; 
      return deleted;
  	}else{
  		return deleted;
  	}
  }else{
    	if(array[2*index+1].getNum() >= array[2*index+2].getNum()){
    		//printf("left number is %i\n", array[2*index+1].getNum());
    		//printf("right number is %i\n", array[2*index+2].getNum());
       		if(array[index].getNum() > array[2*index+2].getNum()){
    			//if parent is greater then right child, switch
    			tmp = array[index];
    			array[index]=array[2*index+2];
    			array[2*index+2]= tmp;
    			index= 2*index+2;
    		}else{
    			break;
    		}
    	}else{
    		if(array[index].getNum() > array[2*index+1].getNum()){
    		// else switch with left
    		tmp = array[index];
    		array[index]=array[2*index+1];
    		array[2*index+1]= tmp;
    		index=2*index+1;
    		}else{
    			break;
    		}
    	}
  	}
  }
  
  return deleted;
}

//inserts Trie back into minHeap
void insertTrie(Letter let, Letter *array, int count){
	Letter tmp;
	int index;
  for(index=count-1; index>-1; index--){//search array from end
    if (array[index].getNum() != -1){ //check end of array for num = -1
      break;
    }
  }
  index++; 		//index is now at right most leaf
  array[index] = let;
  
  while(array[(index-1)/2].getNum() > array[index].getNum()){
	tmp = array[(index-1)/2];
	array[(index-1)/2] = array[index];
	array[index] = tmp;
	index = (index-1)/2;

  }

}

Letter buildTrie(Letter *array, int count){
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
	Letter root = deleteMin(array,count);
	return root;
}

void codeMap(Letter *l,string c){
	//cout<< "Shit is crazy\n";
	string left = c;
	string right = c;
	if((l->getAsc()==-2)){
		left.append("1");
		codeMap(l->left,left);
		right.append("0");
		codeMap(l->right,right);
	}else{
		l->path = c;
		printf("%s : %c\n",c.c_str(), l->getAsc());
	}
}
void getCode(Letter *trie, int l, string *s){ //gets the path to each letter
	if((trie->getAsc()==-2)){
		getCode(trie->left,l,s);
		getCode(trie->right,l,s);
	}else if(trie->getAsc() == l){
		s->append(trie->path);
		return;
	}
	return;
}

void printEncoded(Letter *trie, int *buffer,int count){ //prints I Like Apples in encoded form
	string *code = new string();
	for(int i=0;i < count;i++){
		getCode(trie,buffer[i], code);
	}
	cout << *code + "\n";
	
}

void decode(Letter *trie, int *buffer,int length){
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
		if(buffer[i] == 10){ //skips past the new line
			i++;
			cout << "\n";
		}
		if(buffer[i] != 49 && buffer[i] != 48)
			break;
	}

}



int main(int argc, const char* argv[]){
bool firstLine = true;
bool secLine = false;
bool thirdLine = false;
int buffer0[256];
int buffer1[512];
int buffer2[256];
int alpha[26] = {0};
int sp = 0;
int k=0;
int k1=0;
int k2=0;

//sp = readIn(alpha, sp); //counts letters and puts in array. returns the number of spaces
						//spaces will be added seperately in shrunken Letter array later
	int letter = getchar();
	buffer0[k] = letter;
	k++;
	printf("buffer0 : %c\n", letter);
	while (letter != EOF){	
		// check if a-z
		if (letter >= 97 && letter <= 122){		
			alpha[letter-97] += 1;
		}
		//check for spaces	
		if (letter == 32){
				sp++;
		}
		letter = getchar();
		

		if(thirdLine){
			if(letter == 10){
				break;
			}			

			if(letter != 10){
				buffer2[k2]=letter;
				k2++;
				printf("buffer2 : %c\n", letter);
			}
			
		}
		

		if(secLine){
			/*if(letter == 10){ // check for new line
				thirdLine=true;
				secLine = false;
				
			}*/
			
			//if(letter != 10){		
				buffer1[k1]=letter;
				k1++;
				printf("buffer1 : %c\n", letter);
			//}
			

		}


		if(firstLine){
			if(letter == 10){
				firstLine = false;
				secLine = true;
				
			}
			if(letter != 10){
				buffer0[k] = letter;
				k++;
				printf("buffer0 : %c\n", letter);
			}

			
		}	
	}


//get count of how many different characters including space
	int count = getUniqueCount(alpha, sp);


//seperate the used characters into a new array
	Letter *unsorted; //dynamically allocated Letter array
		unsorted = new Letter[count];
		shrinkArray(unsorted,alpha,sp); // unsorted now has only used Letters and spaces
					    	// spaces and its count are added to the end of the array
	

int i;
//sorted
Letter *sorted;
	sorted = new Letter[count];
	sortArray(sorted, unsorted, count);// takes the unsorted array and sorts it into sorted
	delete[] unsorted; // deallocated array no longer needed



	printf("Sorted:\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	
	}
} 
cout<<"\n \n \n";
Letter trie = buildTrie(sorted,count);
Letter *tp = &trie;
std::string c = "";
codeMap(tp,c);
printf("\n");
printEncoded(tp,buffer0,k);
decode(tp,buffer1,k1);
decode(tp,buffer2,k2);


/*printf("parent count : %i\n",trie.getNum());
printf("parent.left, count : %i asc value : %c\n",trie.left->getNum(), trie.left->getAsc());
printf("parent.right, count: %i asc value : %c\n",trie.right->getNum(),trie.right->getAsc());
printf("parent.left->left, count : %i letter: %c\n",trie.left->left->getNum(), trie.left->left->getAsc());
printf("parent.left->right, count : %i letter: %c\n",trie.left->right->getNum(), trie.left->right->getAsc());
printf("parent.right->left, count: %i letter: %c\n",trie.right->left->getNum(),trie.right->left->getAsc());
printf("parent.right->right, count: %i letter: %c\n",trie.right->right->getNum(),trie.right->right->getAsc());
printf("parent.left->left->left, count: %i letter: %c\n",trie.left->left->left->getNum(),trie.left->left->left->getAsc());
printf("parent.left->left->right, count: %i letter: %c\n",trie.left->left->right->getNum(),trie.left->left->right->getAsc());
printf("parent.left->right->left, count: %i letter: %c\n",trie.left->right->left->getNum(),trie.left->right->left->getAsc());
printf("parent.left->right->right, count: %i letter: %c\n",trie.left->right->right->getNum(),trie.left->right->right->getAsc());
printf("parent.right->left->left, count: %i letter: %c\n",trie.right->left->left->getNum(),trie.right->left->left->getAsc());
printf("parent.right->left->right, count: %i letter: %c\n",trie.right->left->right->getNum(),trie.right->left->right->getAsc());
printf("parent.right->left->left->left, count: %i letter: %c\n",trie.right->left->left->left->getNum(),trie.right->left->left->left->getAsc());
printf("parent.right->left->left->right, count: %i letter: %c\n",trie.right->left->left->right->getNum(),trie.right->left->left->right->getAsc());
*/



/*
cout << "Merge Test\n" ;
Letter first = deleteMin(sorted,count);
printf("first delete : %c\n", first.getAsc());
Letter second = deleteMin(sorted,count);
printf("second delete : %c\n", second.getAsc());
Letter parent(second,first);  
printf("right: %c\n", parent.right->getAsc());
printf("left : %c\n", parent.left->getAsc());


cout << "\nInsert Test\n";
insertTrie(parent,sorted,count);

printf("min Heap after inserted first trie\n");
printHeap(sorted, count);

Letter third = deleteMin(sorted,count);
printf("third delete : %c\n", third.getAsc());
Letter fourth = deleteMin(sorted,count);
printf("fourth delete : %c\n", fourth.getAsc());
Letter parent1(third,fourth);  
printf("right: %c\n", parent1.right->getAsc());
printf("left : %c\n", parent1.left->getAsc());

cout << "\nInsert Test 2\n";
insertTrie(parent1,sorted,count);



printf("min Heap after inserted second trie\n");
printHeap(sorted,count);
*/




}



