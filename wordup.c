//Name: Mateo Lorenzi
//Purpose: Project 10
//Date: 4/25/2025

#include <stdio.h>
#include <stdbool.h>
#define WORD "word.txt"
#define MAX_GUESSES 6
#define MAX_LENGTH 6


bool peekFile(char word[]);
bool validate(char guess[]);
bool winCheck(char word[], char guess[]);
void victory(char word[], int attempt);
void compare(char word[], char guess[], char result[], char hint[]);
void display(int attempt, char result[][MAX_LENGTH], char hint[][MAX_LENGTH]);

int main(){
	char word[MAX_LENGTH];
	if(!peekFile(word)){
		printf("Cannot open word.txt file.\nGoodbye.\n");
		return 1;
	}
	
	
    int attempt = 0;
	char guess[MAX_GUESSES][MAX_LENGTH];
	char result[MAX_GUESSES][MAX_LENGTH];
	char hint[MAX_GUESSES][MAX_LENGTH];
    do{
        if(attempt != MAX_GUESSES - 1){
			printf("GUESS %d! Enter your guess: ", attempt + 1);
		}
		else{
			printf("FINAL GUESS : ");
		}
		
		bool valid = false;
		while(!valid){
			scanf("%s", guess[attempt]);
			
			for(int i = 0; guess[attempt][i] != '\0'; i++){
				if(guess[attempt][i] >= 'A' && guess[attempt][i] <= 'Z'){
					guess[attempt][i] = guess[attempt][i] - 'A' + 'a';
				}
			}
			
			
			if(validate(guess[attempt])){
				valid = true;
				
				compare(word, guess[attempt], result[attempt], hint[attempt]);
				
				if(winCheck(word, guess[attempt])){
					victory(word, attempt);
					return 0;
				}
				
				display(attempt + 1, result, hint);
				
				attempt++;
			}
		}
	}while(attempt < MAX_GUESSES);
	
	if(attempt == MAX_GUESSES){
		printf("\nYou lost. Better luck next time!\n");
	}
	
    return 0;
}



bool peekFile(char word[]){
	FILE *peek;
	peek = fopen(WORD, "r");
	if(peek == NULL){
		return false;
	}
	fscanf(peek, "%s", word);
	fclose(peek);
	return true;
}



bool validate(char guess[]){
	int error = 0;
	
	if(guess[5] != '\0' && guess[5] != '\n'){
		error = 1;
		printf("\nYour guess must be 5 letters long.");
	}
	
	for(int i = 0; i < 5; i++){
		if(!((guess[i] >= 'a' && guess[i] <= 'z') || (guess[i] >= 'A' && guess[i] <= 'Z'))){
			error = 1;
			printf("\nYour guess must contain only letters.");
			break;
		}
	}
	
	if(error == 0){
		return true;
	}
	else{
		printf("\nPlease try again: ");
		
		return false;
	}
}



bool winCheck(char word[], char guess[]){
	for(int i = 0; i < 5; i++){
		if(word[i] != guess[i]){
			return false;
		}
	}
	return true;
}



void victory(char word[], int attempt){
	char capitalized[6];
	for(int i = 0; i < 5; i++){
		if(word[i] >= 'a' && word[i] <= 'z'){
			capitalized[i] = word[i] - 'a' + 'A';
		}
		else{
			capitalized[i] = word[i];
		}
	}
	capitalized[5] = '\0';
	
	printf("================================\n");
	printf("		%s\n", capitalized);
	if(attempt == 0){
		printf("	You won in 1 guess!\n");
	}
	else{
		printf("	You won in %d guesses!\n", attempt + 1);
	}
	printf("		GOATED!\n");
}



void compare(char word[], char guess[], char result[], char hint[]){
	bool partMatch[5] = {false};
	bool exactMatch[5] = {false};
	
	for(int i = 0; i < 5; i++){
		hint[i] = ' ';
		if(guess[i] == word[i]){
			result[i] = guess[i] - 'a' + 'A';
			partMatch[i] = true;
			exactMatch[i] = true;
		}
		else{
			result[i] = guess[i];
		}
	}
	for(int i = 0; i < 5; i++){
		if(!exactMatch[i]){
			for(int j = 0; j < 5; j++){
				if(!partMatch[j] && guess[i] == word[j]){
				hint[i] = '^';
				partMatch[j] = true;
				j = 5;
				}
			}
		}
	}
	result[5] = '\0';
	hint[5] = '\0';
}

void display(int attempt, char result[][MAX_LENGTH], char hint[][MAX_LENGTH]){
	printf("================================\n");
	for(int i = 0; i < attempt; i++){
		printf("%s\n", result[i]);
		printf("%s\n", hint[i]);
	}
}
