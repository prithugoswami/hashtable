# hashtable
## Simple HashTable implementation 

Inserting Into the hastable can be done with:
`HashTableInsert(<key>, <value>, <hashtable pointer>);`

Accessing the hastable can be done with:
`HashTableGet(<key>, <hashtable pointer>);`

EXAMPLE USAGE:

```c
HashTable *ht = createHashTable(100);
int rc = HashTableInsert("name", "Prithu", ht);
if(rc)
   fprintf(stderr, "Cannot Insert the data into the Hashtable");

char *my_name = (char *)HashTableGet("name", ht);

FILE *fp = fopen("my_file.txt", "r");
HashTableInsert("file", fp, ht);

FILE *my_file = (FILE *)HashTableGet("file", ht);
```
