CC=gcc
CFLAG=-I.

# hashtable_test: hashtable.c hashtable.test.c
# 	$(CC) hashtable.c hashtable.test.c -o hashtable_test && ./hashtable_test\
# 	&& rm ./hashtable_test

hashtable_test: hashtable.c hashtable.test.c
	$(CC) hashtable.c hashtable.test.c -o hashtable_test && ./hashtable_test
