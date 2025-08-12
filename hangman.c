#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "linked_list.c"
void clear(){
	printf("\033[2J");
	printf("\033[H");
}

bool charInArray(char list[], char letter, int arrayLength) {
	for (int i = 0; i < arrayLength; i++){
		if (list[i] == letter){
			return true;
		}
	}
	return false;
}
void printHangmanArt(int numOfWrongGuesses){
	switch (numOfWrongGuesses) {
		case 0:
			printf("         |----|\n");
			printf("         |   \n");
			printf("         |  \n");
			printf("         |\n");
			printf("         |\n");
			printf("         |\n");
			printf("         |\n");
			printf("         |\n");
			printf("-------------------\n");
			break;
		case 1:
			printf("         |----|\n");
			printf("         |    - \n");
			printf("         |   | |\n");
			printf("         |    -\n");
			printf("         |\n");
			printf("         |\n");
			printf("         |\n");
			printf("         |\n");
			printf("-------------------\n");
			break;
		case 2:
			printf("         |----|\n");
			printf("         |    - \n");
			printf("         |   | |\n");
			printf("         |    - \n");
			printf("         |   \\|/\n"  );
			printf("         |    |\n");
			printf("         |\n");
			printf("         |\n");
			printf("-------------------\n");
			break;
		case 3:
			printf("         |----|\n");
			printf("         |    - \n");
			printf("         |   | |\n");
			printf("         |    - \n");
			printf("         |   \\|/\n"  );
			printf("         |    |\n");
			printf("         |    |\n");
			printf("         |   / \\\n");
			printf("-------------------\n");
			break;



	} 

}
void makeScreen(void){
	printf("\033[?1049h");

    // ANSI escape code to clear the screen
	clear();


}
bool checkLetter(char Letter, char anwser[]){
	for (int i = 0; i < 8; i++){
		if (Letter == anwser[i]){
			return true;
		}
	} 
	return false;
}
void printcorrectGuesses(char answer[],char correctGuesses[], int sizeOfAnswer, int sizeOfGuessed){
	for (int i = 0; i < sizeOfAnswer; i++){
		if (charInArray(correctGuesses,answer[i],sizeOfGuessed)){
			printf("%c ", answer[i]);

		}
		else{
			printf("_ ");
		}
	}
	
}
void flushStdin(void){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
void forceQuit(int sig){
	printf("Game was forced to quit");
	printf("\033[?1049l");
	exit(sig);

	
}
int main(void){
	signal(SIGINT, forceQuit);
	makeScreen();
	int answerLength = 8;
	int numOfLetters = 7;
	int numOfCorrectGuesses = 0;
	int numOfWrongGuesses = 0;
	char anwser[] = "password";
	LinkedList guesses;
	bool firstGuess = true;
	//this number must be the same as numOfLettesrs.
	char correctGuesses[7] = "";
	const int MAX_TRIES = 3;
	int numOfTries = MAX_TRIES;
	char guess;
	while (numOfTries > 0) {
		clear();
		printHangmanArt(numOfWrongGuesses);
		printcorrectGuesses(anwser,correctGuesses, answerLength, numOfLetters);
		printf("\n\nYour Guesses: ");
		printList(&guesses);	
		printf("\nEnter Your Guess\n");
		scanf(" %c", &guess);
		flushStdin();
		bool alreadyGuessed = isCharInList(&guesses, guess);
		if (firstGuess){
			firstGuess = false;
			guesses.data = guess;
		}else if (!alreadyGuessed){
			addToList(&guesses, guess);
		}
		if (charInArray(anwser,guess,answerLength) && !charInArray(correctGuesses,guess,numOfLetters)){
			correctGuesses[numOfCorrectGuesses] = guess;
			numOfCorrectGuesses++;
			if (numOfCorrectGuesses >= numOfLetters){
				printf("\033[?1049l");
				printf("You Won!!\n");
				return 1;
			}
		}
		else if (!charInArray(anwser,guess,answerLength) && !alreadyGuessed){

		numOfTries--;
		numOfWrongGuesses++;
		}

	}
	clear();
	printHangmanArt(numOfWrongGuesses);
	sleep(1);
	printf("\033[?1049l");
	printf("You Lost!!\n");
	return 1;

}

