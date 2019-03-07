#include "hashtable.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct student{
    char *name;
    int age;
} Student;


int main(){
    HashTable *ht = createHashTable(100);

    Student prithu = {"Prithu", 19};
    Student nilesh = {"Nilesh", 21};

    HashTableInsert("name", "Prithu", ht);
    HashTableInsert("age", "19", ht);
    HashTableInsert("age1", "20", ht);
    HashTableInsert("intrests", "programming;graphic_designing", ht);
    HashTableInsert("country",  "India",  ht);
    HashTableInsert("country2", "Russia", ht);
    HashTableInsert("country3", "USA",    ht);
    HashTableInsert("student_prithu", &prithu, ht);
    HashTableInsert("student_nilesh", &nilesh, ht);


    // checking values from HashTable
    assert(!strcmp(HashTableGet("name", ht), "Prithu"));
    assert(!strcmp(HashTableGet("age",  ht), "19"));
    assert(!strcmp(HashTableGet("age1", ht), "20"));
    assert(!strcmp(HashTableGet("intrests", ht), "programming;graphic_designing"));
    assert(!strcmp(HashTableGet("country",  ht), "India"));
    assert(!strcmp(HashTableGet("country2", ht), "Russia"));
    assert(!strcmp(HashTableGet("country3", ht), "USA"));

    // for Student structure
    assert( ((Student *)HashTableGet("student_prithu", ht))->age == 19);
    assert( ((Student *)HashTableGet("student_nilesh", ht))->age == 21);
    assert(!strcmp(((Student *)HashTableGet("student_nilesh", ht))->name, "Nilesh"));

    // checking length and capacity
    assert(ht->length==9);
    assert(ht->capacity==100);

    // existing key should not be added
    bool added = HashTableInsert("country", "India", ht);
    assert(!added);

    // non-existent key must return NULL
    char *non = HashTableGet("non-existent-key", ht);
    assert(non == NULL);

    fprintf(stderr, "\033[32;1mSUCCESS!\033[0m\n");
    free(ht);
}
