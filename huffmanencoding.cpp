//Anthony Hoang and Charles Chain
#include<cstdio>


int main(int argc, const char* argv[]){

int alpha[26] = {0};
int sp = 0;

int letter = getchar();
	while (letter != EOF){	
		// check if a-z or space
		if (letter >= 97 && letter <= 122 | letter == 32){		
			alpha[letter-97] += 1;
		}	
		if (letter == 32){
				sp++;
		}
		
		letter = getchar();
	}

int i;
	for (i=0 ; i< 24 ; i=i+3){
	printf("%c : %i || %c : %i || %c : %i\n", i+97, alpha[i], i+98, alpha[i+1], i+99, alpha[i+2] );
	}
	printf("y : %i || z : %i || space : %i\n",alpha[24],alpha[25], sp);
}

