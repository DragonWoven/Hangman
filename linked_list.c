#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct linkedList{
	char data;
	struct linkedList* next;

};
typedef struct linkedList LinkedList ;
void addToList(LinkedList* listPointer, char letter){
	if (listPointer -> next == NULL){
		LinkedList * newChar = (LinkedList *) malloc(sizeof(LinkedList));
		if (newChar == NULL){
			printf("Failed to allocate memory");
		}
		newChar -> next = NULL;
		newChar -> data = letter;
		listPointer -> next = newChar;
	}
	else{
		addToList(listPointer -> next, letter);
	}

}
void printList(LinkedList* listPointer){
	LinkedList list = *listPointer;
	printf("%c ", list.data);
	if (list.next != NULL){
		printList(list.next);
	}
	else{
		printf("\n");
	}

}
bool isCharInList(LinkedList* list, char letter){
	if (letter == list -> data){
		return true;
	}
	else if (list -> next != NULL){
		return isCharInList(list -> next, letter);
	}else {
		return false;
	}
} 

