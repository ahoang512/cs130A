//Anthony Hoang and Charles Chain
#include<cstdio>
#include <iostream>

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
		Letter(Letter, Letter);
		int getAsc();
		int getNum();
  		Letter *left;
  		Letter *right;
		void setAsc(int a);
		void setNum(int n);
		bool isTrie();
};

Letter::Letter(){
		asc =  -1;
		num = 0;
		left = NULL;
		right = NULL;
}

Letter::Letter(const Letter& l){
  asc = l.asc;
  num = l.num;
  left = l.left;
  right = l.right;
}

Letter::Letter(int a, int n){
	asc = a;
	num = n;
	left = NULL;
	right = NULL;
}
Letter::Letter(Letter first, Letter second){
	asc = -2;
	num = first.getNum() + second.getNum();
	left = &second;
	right = &first;
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
/* Doesnt work
Letter merge(Letter first, Letter sec){
	Letter parent(first,sec);
	return parent;
}
*/

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
	while(filled > 1){
	Letter first = deleteMin(array,count);
	Letter second = deleteMin(array,count);
	Letter head(first,second);
	insertTrie(head,array,count);
	printHeap(array,count);
	filled--;
	}
	Letter root = deleteMin(array,count);
	return root;
}

void codeMap(Letter *l){
	cout<< "Shit is crazy\n";
	if((l->isTrie())){
		cout<<0;
		codeMap(l->left);
		cout<<1;
		codeMap(l->right);
	}else{
		printf(" : %c\n", l->getAsc());
	}
}



int main(int argc, const char* argv[]){

int alpha[26] = {0};
int sp = 0;

sp = readIn(alpha, sp); //counts letters and puts in array. returns the number of spaces
						//spaces will be added seperately in shrunken Letter array later


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
//codeMap(tp);

printf("parent count : %i\n",trie.getNum());
printf("parent.left, count : %i asc value : %i\n",trie.left->getNum(), trie.left->getAsc());
printf("parent.right, count: %i asc value : %i\n",trie.right->getNum(),trie.right->getAsc());
printf("parent.left->left, count : %i letter: %c\n",trie.left->left->getNum(), trie.left->left->getAsc());
printf("parent.left->right, count : %i letter: %c \n",trie.left->right->getNum(), trie.left->right->getAsc());
printf("parent.right->left, count: %i letter: %c\n",trie.right->left->getNum(),trie.right->left->getAsc());
printf("parent.right->right, count: %i letter: sp\n",trie.right->right->getNum());
printf("parent.left->left->left, count: %i letter: %c\n",trie.left->left->left->getNum(),trie.left->left->left->getAsc());
printf("parent.left->left->right, count: %i letter: %c\n",trie.left->left->right->getNum(),trie.left->left->right->getAsc());
printf("parent.left->right->left, count: %i letter: %c\n",trie.left->right->left->getNum(),trie.left->right->left->getAsc());
printf("parent.left->right->right, count: %i letter: %c\n",trie.left->right->right->getNum(),trie.left->right->right->getAsc());
printf("parent.right->left->left, count: %i letter: %c\n",trie.right->left->left->getNum(),trie.right->left->left->getAsc());
printf("parent.right->left->right, count: %i letter: %c\n",trie.right->left->right->getNum(),trie.right->left->right->getAsc());
printf("parent.right->left->left->left, count: %i letter: %c\n",trie.right->left->left->left->getNum(),trie.right->left->left->left->getAsc());
printf("parent.right->left->left->right, count: %i letter: %c\n",trie.right->left->left->right->getNum(),trie.right->left->left->right->getAsc());



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



/*

deleteMin(sorted,count);
	printf("Deleted 1\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].isTrie()){
		cout << "Trie\n";
	}
	else if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
} 

deleteMin(sorted,count);
	printf("Deleted 2:\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
} 

deleteMin(sorted,count);
	printf("Deleted 3:\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
} 

deleteMin(sorted,count);
	printf("Deleted 4:\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
} 

deleteMin(sorted,count);
	printf("Deleted 5:\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
} 

deleteMin(sorted,count);
	printf("Deleted 6:\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
} 
deleteMin(sorted,count);
	printf("Deleted 7:\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
} 
deleteMin(sorted,count);
	printf("Deleted 8:\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
} 

deleteMin(sorted,count);
	printf("Deleted 9:\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
}
*/

}



