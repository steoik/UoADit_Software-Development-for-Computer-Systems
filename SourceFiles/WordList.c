///////////////////////////////////
// University: UoA DIT
// Course : [K23a] Software Development for Computer Systems
// Semester : Fall 2021-2022
// Professor : Yannis Ioannidis 
// --------------------------------
// Students: Stylianos Oikonomou , Anastasios Triantafyllou
// ID : 1115201500243 , 1115201600173 
// --------------------------------
// Project : Assignment_1
// File : 
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordList.h"

// Create a Word List
WList WL_Create(){

	WList wl = (WList )malloc(sizeof(wlist ));
	wl->head = NULL;

	return wl != NULL ? wl : NULL;
}
// Insert a word at the tail of a Word List
WLNode WL_Insert(const WList wl, const char *word){

	if(wl == NULL || word == NULL)
		return NULL;

	WLNode wln = (WLNode )malloc(sizeof(word_list_node ));
	strcpy(wln->word, word);
	wln->next = NULL;

	if(wl->head == NULL){
		wl->head = wln;
		wl->tail = wln;
	}
	else{

		wl->tail->next = wln;
		wl->tail = wln;
	}
	return wln;
}
// Insert a word in sorted way in a Word List if it does not already exist
WLNode WL_InsertSortUnique(const WList wl, const char *word){

	if(wl == NULL || word == NULL) return NULL;

	WLNode wln = (WLNode )malloc(sizeof(word_list_node ));
	strcpy(wln->word, word);
	wln->next = NULL;

	if(wl->head == NULL){							// If the list is empty insert at the head
		
		wl->head = wln;
		wl->tail = wln;
	}
	else if(strcmp(word, wl->head->word) < 0){		// If the new word is the smallest insert at the head

		wln->next = wl->head;
		wl->head = wln;
	}
	else if(strcmp(word, wl->head->word) == 0){		// If the new word is equal to the head free it and return NULL

		free(wln);
		wln = NULL;
	}
	else{

		WLNode temp = wl->head;
		while(temp->next != NULL && strcmp(word, temp->next->word) > 0)
			temp = temp->next;
		
		if(temp->next == NULL){						// If the new word is the greatest insert it at the tail

			temp->next = wln;
			wl->tail = wln;
		}
		else if(strcmp(word, temp->next->word) < 0){		// If the next word is greatest insert the new word behind it

			wln->next = temp->next;
			temp->next = wln;
		}
		else{										// If the word exists free the new node and return NULL

			free(wln);
			wln = NULL;
		}
	}
	
	return wln;
}
// Remove the first node of a Word List
int WL_RemoveFirst(const WList wl){

	if(wl == NULL)
		return 1;

	if(wl->head == NULL)
		return 1;
	else{

		if(wl->tail == wl->head){

			WLNode temp = wl->head;
			wl->head = NULL;
			wl->tail = NULL;
			free(temp);
		}
		else{

			WLNode temp = wl->head;
			wl->head = wl->head->next;
			free(temp);
		}
	}
	return 0;
}
// Get the first node of a Word List
WLNode WL_GetFirst(const WList wl){

	if(wl == NULL)
		return NULL;
	return wl->head;
}
// Print a Word List 
int WL_Print(const WList wl){

	if(wl == NULL)
		return 1;

	WLNode temp = wl->head;
	printf("[ ");
	while(temp != NULL){

		printf("%s ", temp->word);
		temp = temp->next;
	}
	printf("]\n");
	return 0;
}
// Return 0 if the Word List is empty, 1 if not
int WL_IsEmpty(const WList wl){

	if(wl == NULL)
		return -1;
	
	return wl->head == NULL ? 0 : 1;
}
// Return the size of the Word List
int WL_GetSize(const WList wl){

	if(wl == NULL)
		return -1;

	int size = 0;
	WLNode temp = wl->head;
	while(temp != NULL){

		size++;
		temp = temp->next;
	}
	return size;
}
// Destroy a Word List
int WL_Destroy(WList wl){

	if(wl == NULL)
		return 1;

	while(wl->head != NULL)
		WL_RemoveFirst(wl);
	free(wl);
	return 0;
}