//Anthony Hoang and Charles Chain
#include<cstdio>


class Letter{
	private:
		int asc;
		int num;

	public:
		Letter();
		Letter(int a, int n);
		int getAsc();
		int getNum();
		void setAsc(int a);
		void setNum(int n);
};

Letter::Letter(){
		asc =  -1;
		num = 0;
}

Letter::Letter(int a, int n){
	asc = a;
	num = n;
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


//main methods------------------------------------------------------------------------
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
Letter *delete(Letter *array, int count){
  Letter *tmp = array[0];
  for(int i=count-1; i>-1; i--){//search array from end
    if (array[i].getNum() != -1){ //check end of array for num = -1
      break;
    }
  }
    
  array[0] = array[i];
  array[i].setNum(-1);
  
  //perculate
  if( i == 0){
    return *tmp;
  }

}






int main(int argc, const char* argv[]){

int alpha[26] = {0};
int sp = 0;

sp = readIn(alpha, sp); //counts letters and puts in array. returns the number of spaces
						//spaces will be added seperately in shrunken Letter array later

printf("letter count:\n");
for(int o = 0; o < 26; o++){
	printf("%c : %i\n", o+97, alpha[o]);
}


//get count of how many different characters including space
	int count = getUniqueCount(alpha, sp);


//seperate the used characters into a new array
	Letter *unsorted; //dynamically allocated Letter array
		unsorted = new Letter[count];
		shrinkArray(unsorted,alpha,sp); // unsorted now has only used Letters and spaces
					    	// spaces and its count are added to the end of the array
	

int i;
printf("Unsorted:\n");
for (i = 0 ; i <count; i++){
	if(unsorted[i].getAsc() == 32){
		printf("sp: %i\n", unsorted[i].getNum());
	}else{
	printf("%c : %i\n", unsorted[i].getAsc(), unsorted[i].getNum());
	}
} 


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
	
}



