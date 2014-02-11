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

int i;
	/*for (i=0 ; i< 24 ; i=i+3){
	printf("%c : %i || %c : %i || %c : %i\n", i+97, alpha[i], i+98, alpha[i+1], i+99, alpha[i+2] );
	}
	printf("y : %i || z : %i || space : %i\n",alpha[24],alpha[25], sp);*/

int count = 0;
	for(i = 0; i <26; i++){
		if(alpha[i] != 0){

			count +=1;
		}
	}
	if(sp!=0){
		count += 1;
	}
	

int j = 0; // incremented for unsorted array
Letter *unsorted; //dynamically allocated Letter array
	unsorted = new Letter[count];
	for(i = 0; i < 26 ; i++){
		if(alpha[i] != 0){
			unsorted[j].setAsc(i+97); //adding non zero values to array
			unsorted[j].setNum(alpha[i]);
			j++;
		}
	}
	unsorted[j].setAsc(32);
	unsorted[j].setNum(sp);

	printf("Unsorted:\n");
for (i = 0 ; i <count-1; i++){
	printf("%c : %i\n", unsorted[i].getAsc(), unsorted[i].getNum());
} 
	printf("sp: %i\n\n\n", unsorted[i].getNum());


//sort
Letter *lowest;
lowest = new Letter(100, 100);
Letter *blank = new Letter(100,100);
Letter *sorted;
	sorted = new Letter[count];
int k;
int filled;
for(filled=0; filled < count; filled++){
	for(i = 0 ; i<count; i++){
		
		if(unsorted[i].getNum() < lowest->getNum()){
			*lowest = unsorted[i];	
			k=i;
		}else if(unsorted[i].getNum() == lowest->getNum()){
			
			if(unsorted[i].getAsc() < lowest->getAsc()){
				*lowest = unsorted[i];
				k=i;
			}
		}
	}

	sorted[filled].setNum(lowest->getNum());
	sorted[filled].setAsc(lowest->getAsc());
	unsorted[k].setNum(100);
	lowest->setNum(100);
	
}


	printf("Sorted:\n");
for (i = 0 ; i <count; i++){
	if(sorted[i].getAsc()==32){
		printf("sp: %i\n", sorted[i].getNum());
	}else{
	printf("%c : %i\n", sorted[i].getAsc(), sorted[i].getNum());
	}
} 
	
}



