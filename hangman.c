#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

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
void printGuessed(char answer[],char guessed[], int sizeOfAnswer, int sizeOfGuessed){
	for (int i = 0; i < sizeOfAnswer; i++){
		if (charInArray(guessed,answer[i],sizeOfGuessed)){
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
	//this number must be the same as numOfLettesrs.
	char guessed[7] = "";
	int numOfTries = 3;
	char guess;
	while (numOfTries > 0) {
		clear();
		printHangmanArt(numOfWrongGuesses);
		printGuessed(anwser,guessed, answerLength, numOfLetters);
		printf("\nEnter Your Guess\n");
		scanf(" %c", &guess);
		flushStdin();
		if (charInArray(anwser,guess,answerLength) && !charInArray(guessed,guess,numOfLetters)){
			guessed[numOfCorrectGuesses] = guess;
			numOfCorrectGuesses++;
			if (numOfCorrectGuesses >= numOfLetters){
				printf("\033[?1049l");
				printf("You Won!!\n");
				return 1;
			}
		}
		else if (!charInArray(anwser,guess,answerLength)){

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

