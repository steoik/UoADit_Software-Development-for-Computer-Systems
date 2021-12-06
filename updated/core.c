#include <stdlib.h>
#include <string.h>

#include "core.h"

#include "DataStructs.h"
#include "EntryList.h"
#include "QueryList.h"
#include "HashTable.h"
#include "BKTree.h"
#include "HashTable.h"
//#include "distance.h" //Not needed (?)
#include "common_types.h"

//Will use, unfortunately and unevadably, global structures

static List *el, *ql;
static BKTree bke, bkh[MAX_WORD_LENGTH-MIN_WORD_LENGTH+1];
static HashTable hte;


ErrorCode InitializeIndex(){
    //Typical null initialization
    el = ql = NULL;
    bke = NULL;
    hte = NULL;
    int i;
    for (i = 0; i < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; i++) bkh[i] = NULL;
    //Actual initialization with proper memory deallocation in case of error
    if (create_entry_list(&el) != EC_SUCCESS) return EC_FAIL;
    if (create_entry_list(&ql) != EC_SUCCESS) { destroy_entry_list(el); return EC_FAIL;}
    if (!(bke = BKT_Create(MT_EDIT_DIST))) { destroy_entry_list(el); destroy_query_list(ql); return EC_FAIL;}
    if (!(hte = HT_Create(entry))) { destroy_entry_list(el); destroy_query_list(ql); BKT_Destroy(bke); return EC_FAIL;}
    int j;
    for (i = 0; i < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; i++){
        if (!(bkh[i] = BKT_Create(MT_HAMMING_DIST))) {
            for (j = 0; j < i; j++) BKT_Destroy(bkh[j]);
            destroy_entry_list(el); destroy_query_list(ql); BKT_Destroy(bke); HT_Destroy(hte); return EC_FAIL;
        }
    }
    //Getting down to business...
    
    //Might be done here, will expand if needed

    return EC_SUCCESS;
}

ErrorCode DestroyIndex(){
    //Definitely not complete
    destroy_entry_list(el);
    destroy_query_list(ql);
    BKT_Destroy(bke);
    HT_Destroy(hte);
    int i;
    for (i = 0; i < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; i++) BKT_Destroy(bkh[i]);
    return EC_SUCCESS;
}

ErrorCode StartQuery(QueryID query_id, const char *query_str, MatchType match_type, unsigned int match_dist){
    //...

    //Crete query and initialize entry list as empty

    Query q = createQuery(query_id, match_type, match_dist);
    //Add query to main index.querylist
    
    //Create entries or update existing entries based on the query string tokens and update query's entry list pointers/contents



    //Update Index pointers on any new entries and update all entries' payloads to contain new query



    // Below code will be converted to tokenize each word and follow the above guideline
    // Split the query string into words and insert them in the query words List
    char *word = (char *)malloc(sizeof(char ) * (MAX_WORD_LENGTH + 1));
    int index = 0;
    for(; ; query_str++){
        if(*query_str == 32 || *query_str == '\0'){
            word[index] = '\0';
                
            LL_InsertTail(newQuery->query_words, createString(word));

            index = 0;
            free(word);
            if(*query_str == '\0') break;
            word = (char *)malloc(sizeof(char ) * (MAX_WORD_LENGTH + 1));
        }
        else{
            word[index] = *query_str;
            index++;
        }
    }


    return EC_SUCCESS;
}

ErrorCode EndQuery(QueryID query_id){

    return EC_SUCCESS;
}

ErrorCode MatchDocument(DocID doc_id, const char *doc_str){

    return EC_SUCCESS;
}

ErrorCode GetNextAvailRes(DocID *p_doc_id, unsigned int *p_num_res, QueryID **p_query_ids){

    return EC_SUCCESS;
}