#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include <stdbool.h>
#include <stddef.h>
#define LL_Err_OUTOFBOUNDS "ListError: Index Out of Bounds\n"


/* Simple HashTable implementation 
 *
 * Inserting Into the hastable can be done with:
 * HashTableInsert(<key>, <value>, <hashtable pointer>);
 *
 * Accessing the hastable can be done with:
 * HashTableGet(<key>, <hashtable pointer>);
 *
 * EXAMPLE USAGE:
 *
 * HashTable *ht = createHashTable(100);
 * int rc = HashTableInsert("name", "Prithu", ht);
 * if(rc)
 *    fprintf(stderr, "Cannot Insert the data into the Hashtable");
 *
 * char *my_name = (char *)HashTableGet("name", ht);
 *
 * FILE *fp = fopen("my_file.txt", "r");
 * HashTableInsert("file", fp, ht);
 *
 * FILE *my_file = (FILE *)HashTableGet("file", ht);
 *
 *
*/

/* -------------------- */
/* LinkedList Protoypes */
/* -------------------- */

typedef struct node{
    void *data;
    struct node *next;
} Node;

typedef struct list{
    Node *first;
    size_t length;
} List;

static List * ListInit();
static bool ListIsEmpty(const List *plist);
static bool ListAppend(void *data, List *plist);
static bool ListInsertFront(void *data, List *plist);
static bool ListInsert(void *data, int position, List *plist);
static void * ListPopItem(int pos, List *plist);
static void * ListGetItem(int pos, List *plist);


/* -------------------------------------------------- */
/* Hashtable Type Definitions and Function Prototypes */
/* -------------------------------------------------- */

typedef struct hash_table{
    size_t capacity;
    size_t length;
    List **lists;
} HashTable;

typedef struct elem_s{
    char *key;
    void *value;
} elem_t;

/* Create a hashtable and returns a pointer to it */
/* capcity decides the number of array indeces for data */
HashTable * createHashTable(size_t capacity);

/* Inserts the value into the HashTable `hashtable` along with the key*/
bool HashTableInsert(char *key, void *value, HashTable *hashtable);

/* Returns a pointer to the data mapped to the key in the 
 * Hashtable pointed by `hashtable` */
void * HashTableGet(char *key, HashTable * hashtable);

#endif
