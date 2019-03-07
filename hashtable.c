#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"


/* --------------------- */
/* Linked List Functions */
/* --------------------- */

static List * ListInit(){
    List *list = (List *)malloc(sizeof(List));
    return list;
}

static bool ListIsEmpty(const List *plist){
    return plist->first == NULL;
}

static bool ListAppend(void * data, List *plist){
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL){
        fprintf(stderr, "Error: No Memory Available");
        return false;
    }
    if(ListIsEmpty(plist)){
        newNode->data = data;
        newNode->next = NULL;

        plist->first=newNode;
        plist->length++;
        return true;
    }

    Node *temp;
    temp = plist->first;
    while(temp->next != NULL)
        temp = temp->next;

    newNode->data = data;
    newNode->next = NULL;

    temp->next=newNode;
    plist->length++;
    return true;
}

static bool ListInsertFront(void * data, List *plist){
    Node *newNode = (Node *)malloc(sizeof(Node));
    if(newNode == NULL){
        fprintf(stderr, "Error: No Memory Available");
        return false;
    }
    else{
        newNode->data = data;
        newNode->next = plist->first;
        plist->first = newNode;
        plist->length++;
        return true;
    }
}

static bool ListInsert(void * data, int pos, List *plist){
    if(pos >= plist->length || pos < 0){
        fprintf(stderr, LL_Err_OUTOFBOUNDS);
        return false;
    }

    if(pos==0)
        return ListInsertFront(data, plist);

    int c=0;
    Node *temp = plist->first;
    /* `temp` will point to the node that is just before the position `pos`
     * where the new node has to be added */
    while(c < pos-1){
        temp = temp->next;
        c++;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    if(newNode == NULL){
        fprintf(stderr, "Error: No Memory Available");
        return false;
    }
    else{
        newNode->data = data;
        newNode->next = temp->next;
        temp->next=newNode;
        plist->length++;
        return true;
    }
}

static void * ListGetItem(int pos, List *plist){
    if(pos >= plist->length || pos < 0){
        fprintf(stderr, LL_Err_OUTOFBOUNDS);
        exit(1);
    }

    int c=0;
    Node *temp = plist->first;
    while(c < pos){
        temp = temp->next;
        c++;
    }

    return temp->data;
}

static void * ListPopItem(int pos, List *plist){
    if(pos >= plist->length || pos < 0){
        fprintf(stderr, LL_Err_OUTOFBOUNDS);
        exit(1);
    }

    int c=0;
    Node *prevNode = plist->first;
    while(c < pos-1){
        prevNode = prevNode->next;
        c++;
    }
    Node *currNode = prevNode->next;
    Node *nextNode = currNode->next;
    prevNode->next = nextNode;

    void *data = currNode->data;
    free(currNode);
    plist->length--;
    return data;
}



/* ------------------- */
/* HashTable Functions */
/* ------------------- */

static unsigned long
hash_function(char *str, size_t capacity){
    unsigned long hash = 0;
    int c;
    char *strcpy = str;
    while(c = *strcpy++)
        hash +=c;
    return hash%capacity;
}

HashTable *
createHashTable(size_t capacity){
    HashTable *hashtable = (HashTable *)malloc(sizeof(HashTable));
    List **lists = (List **)malloc(sizeof(List*)*capacity);
    for(int i=0; i<capacity; i++)
        lists[i] = ListInit();
    hashtable->lists = lists;
    hashtable->capacity = capacity;
    return hashtable;
}

bool
HashTableInsert(char *key, void *data, HashTable *hashtable){
    unsigned long hash = hash_function(key, hashtable->capacity);
    List *list = hashtable->lists[hash];

    if(ListIsEmpty(list)){
        elem_t *elem = (elem_t *)malloc(sizeof(elem_t));
        elem->key = key;
        elem->value = data;
        ListAppend(elem, list);
        hashtable->length++;
        return true;
    }
    else{
        elem_t *elem_tmp;
        for(int i=0; i<list->length; i++){
            elem_tmp = (elem_t *)ListGetItem(i, list);
            if (strcmp(key ,elem_tmp->key)==0)
                return false;//key already exists
        }
        elem_t *elem = (elem_t *)malloc(sizeof(elem_t));
        elem->key = key;
        elem->value = data;
        ListAppend(elem, list);
        hashtable->length++;
        return true;
    }
}

void *
HashTableGet(char *key, HashTable *hashtable){
    unsigned long hash = hash_function(key, hashtable->capacity);
    List *list = hashtable->lists[hash];
    if (ListIsEmpty(list))
        return NULL;

    else if(list->length > 1){
        elem_t *elem_tmp;
        for(int i=0; i<list->length; i++){
            elem_tmp = ListGetItem(i, list);
            if(strcmp(key, elem_tmp->key)==0){
                return elem_tmp->value;
            }
        }
        return NULL;
    }

    else{// if only one element in the list
        elem_t *elem = ListGetItem(0, list);
        return elem->value;
    }
}
