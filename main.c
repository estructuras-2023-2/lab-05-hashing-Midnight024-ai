#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} Bucket;

typedef struct {
    int (*hashFn)(int);
    Bucket table[TABLE_SIZE];
} HashTable;

