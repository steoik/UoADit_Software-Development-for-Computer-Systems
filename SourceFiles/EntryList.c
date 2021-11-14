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

#include "EntryList.h"
#include "DataStructs.h"
#include "BKTree.h"
#include "core.h"

List *create_list(void){

    List *list = (List *)malloc(sizeof(List));
    if(!list) return NULL;
    list->head = list->tail = NULL; 
    list->size = 0;
    return list;
}

ErrorCode destroy_node(listnode *ln, ListType type){

    if (!ln) return EC_FAIL;
    // ErrorCode ret;
    switch(type){   //Can be expanded
        case entry: destroy_entry((Entry *)(ln->data)); break;
        default: break; //Do nothing
    }
    //if (ret) return EC_FAIL;  //Mixes things up in the supposedly-never-gonna-occur-case where an entry list contains a NULL entry
    free(ln);
    return EC_SUCCESS;
}

ErrorCode destroy_list(List *l, ListType type){

    if (!l) return EC_FAIL;

    listnode *temp = l->head, *tbdestr;
    while (temp){
        tbdestr = temp;
        temp = temp->next;
        destroy_node(tbdestr, type);
    }
    free(l);
    return EC_SUCCESS;
}

List *insert_list(List *l, void *data){

    if (!l) return NULL;

    listnode* node = (listnode *)malloc(sizeof(listnode));
    if (!node) return NULL;
    node->next = NULL; 
    node->data = (void *)data;   //Data initialization
    (l->size)++;
    
    if (!(l->head)) {l->head = node; l->tail = node;}        //If list is empty, make new data head and tail
    else {
        l->tail->next = node;   //Data concatination
        l->tail = node;         //Update tail pointer
    }
    return l;
}

ErrorCode create_entry_list(List **l){
    
    *l = create_list();
    return (*l) ? EC_SUCCESS : EC_FAIL;
}

Entry *create_entry(const char *word, void *payload){

    if (!word) return NULL;
    int wlen = strlen(word) + 1;    // +1 for the terminating \0;
    if (wlen > MAX_WORD_LENGTH + 1 || wlen < MIN_WORD_LENGTH + 1) return NULL;

    
    Entry *ent = (Entry *)malloc(sizeof(Entry));
    if (!ent) return NULL;
    ent->payload = payload;
    ent->word = (char *)malloc(wlen*sizeof(char));
    if (!(ent->word)) { free(ent); return NULL; }
    strcpy(ent->word, word);
    return ent;
}

ErrorCode destroy_entry(Entry *e){

    if (!e) return EC_FAIL;
    
    e->payload = NULL;  //Might revisit to support any added payload functionality
    free(e->word);
    free(e);
    return EC_SUCCESS;
}

unsigned int get_number_entries(const List *el){  //Might replace with a variable in the List struct
    
    return (el) ? el->size: 0;

    /*if (!el || !(el->head)) return 0;   //Works thanks to short-circuiting
    unsigned int count = 1;             //Since the program execution reached this,
    listnode *temp = el->head;          //there is at least 1 data in the list
    while (temp->next && temp != el->tail){ //Either of those conditions should work, using both is overkill
        count++;
        temp = temp->next;
    }
    return count;*/
}

ErrorCode add_entry(List *l, const Entry *entry){   //Might change up so it creates the entry itself aswell by calling create_entry()

    return (insert_list(l, (Entry *)entry)) ? EC_SUCCESS : EC_FAIL;
}

Entry *get_first(const List* el){

    return (el) ? (el->head) ? (Entry *)(el->head->data) : NULL : NULL;
}

Entry *get_next(const listnode* ln){    //Placeholder implementation, might change up the whole approach
    
    return (ln) ? (ln->next) ? (Entry *)(ln->next->data) : NULL : NULL;
}

ErrorCode destroy_entry_list(List *l){

    if (!l) return EC_FAIL;
    
    destroy_list(l, entry);
    return EC_SUCCESS;
}

Entry *copy_entry(const Entry *e){
    
    return (!e) ? NULL : create_entry(e->word, e->payload);
}

void print_entry_list(const List *l){
    if (!l) return;
    listnode *ln = l->head;
    printf("EntryList contains: \n");
    while (ln) {
        printf("%s\n", ((Entry *)(ln->data))->word);
        ln = ln->next;
    }
    printf("End of EntryList\n");
}

ErrorCode build_entry_index(const List *el, MatchType type, Index ix){

	if (!el) return EC_FAIL;

    *ix = BKT_Create(type);
	listnode *ln = el->head;
	while (ln){
		BKT_Insert(*ix, (Entry *)(ln->data));
		ln = ln->next;
	}

	return EC_SUCCESS;
}
ErrorCode lookup_entry_index(const char *w, Index ix, int threshold, List **result){

    *result = NULL;
    List *list;
	if (!(list = BKT_Search(*ix, w, threshold))) return EC_FAIL;
    *result = list;
    return EC_SUCCESS;
}

ErrorCode destroy_entry_index(Index ix){
    return (BKT_Destroy(*ix)) ? EC_FAIL : EC_SUCCESS;
}