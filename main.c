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

Node *create_node(int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

HashTable *init_table(int (*hashFunc)(int)) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->hashFn = hashFunc;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i].head = NULL;
    }
    return ht;
}

void add_value(HashTable *ht, int value) {
    int index = ht->hashFn(value);
    Node *newNode = create_node(value);
    newNode->next = ht->table[index].head;
    ht->table[index].head = newNode;
}

int search_value(HashTable *ht, int value) {
    int index = ht->hashFn(value);
    Node *current = ht->table[index].head;
    while (current) {
        if (current->data == value) {
            return current->data;
        }
        current = current->next;
    }
    return -1;
}

void free_table(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = ht->table[i].head;
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht);
}

int modHash(int value) {
    return value % TABLE_SIZE;
}

int randomHash(int value) {
    return rand() % TABLE_SIZE;
}

int main() {
    printf("%d\n", modHash(52));
    printf("%d\n", modHash(3235235));

    HashTable *ht = init_table(modHash);

    int x = 1234567;
    add_value(ht, x);
    printf("%d\n", search_value(ht, x));

    free_table(ht);

    return 0;
}
