#include<stdio.h>
#include<stdlib.h>
#include"binary_tree.h"
#include <string.h>
#include"../include/binary_tree.h"
#include"../include/hash.h"

unsigned int hash_func(char *key){
    if(key == NULL)
        return 0;
    unsigned int hash = 0;
    while (*key)
        hash = (hash * 31) + *key++ - '0';
    return hash; 
}

hashtable_t *hash_create(unsigned int size){
    if(size == 0)
        return NULL;
    hashtable_t* ht = malloc(sizeof(hashtable_t));
    ht->size = size;
    void** table = calloc(size, sizeof(void*));
    for(int i = 0; i < size; i++)
        table[i] = NULL;
    ht->table = table;
    return ht;
}

void hash_destroy(hashtable_t *ht, void (*fp)(void *data)){
    for(int i = 0; i < ht->size;i++)
        destroy_tree((node_t*)(ht->table[i]),(void (*)(node_t *))fp);
    free(ht->table);
    free(ht);
}

void hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data)){
    if(!ht) return;
    int bucket = hash_func(key)%(ht->size);
    ht->table[bucket] = insert(ht->table[bucket], key, ptr);
}

char* find(node_t* node, char* key){
    if(!node)
        return NULL;
    if(!strcmp(node->key, key))
        return node->data;
    char* data = find(node->left, key);
    return data?data:find(node->right, key);
}

void* hash_get(hashtable_t *ht, char *key){
    int bucket = hash_func(key)%(ht->size);
    node_t* tree = ht->table[bucket];
    void* data = find(tree, key);
    return !data?NULL:data;
}
