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





int main(int argc, const char* argv[]){

int alpha[26] = {0};
int sp = 0;

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

//get count of how many different characters including space
int i;
int count = 0;
	for(i = 0; i <26; i++){
		if(alpha[i] != 0){

			count +=1;
		}
	}
	if(sp!=0){
		count += 1;
	}
	
//seperate the used characters into a new array
int j = 0; // increment for unsorted array
Letter *unsorted; //dynamically allocated Letter array
	unsorted = new Letter[count];
	for(i = 0; i < 26 ; i++){
		if(alpha[i] != 0){
			unsorted[j].setAsc(i+97); //adding non zero values to array
			unsorted[j].setNum(alpha[i]); // add the count for each character
			j++;
		}
	}
	unsorted[j].setAsc(32); // add space to last spot in array
	unsorted[j].setNum(sp); // add count for space


printf("Unsorted:\n");
for (i = 0 ; i <count-1; i++){
	printf("%c : %i\n", unsorted[i].getAsc(), unsorted[i].getNum());
} 
printf("sp: %i\n\n\n", unsorted[i].getNum());


//sorted
Letter *lowest;
lowest = new Letter(100, 100);
Letter *sorted;
	sorted = new Letter[count];
int k; //keeps track of where in unsorted the lowest was so we can lazy delete it
int filled;
for(filled=0; filled < count; filled++){
	for(i = 0 ; i<count; i++){
		
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



