#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include "../include/env.h"
#include "../include/hash.h"
#define ENV_TABLE_CAP 100

int arr_size = 0;
hashtable_t *ht;
char* vars[ENV_TABLE_CAP];
char* vals[ENV_TABLE_CAP];

void noop(void *data)
{
  data;
}

void new_var(char* key, char* value){
  hash_set(ht, key, value, &noop);
  vars[arr_size] = key;
  vals[arr_size] = value;
  arr_size++;
}

void init_env_table(){
    ht = hash_create(ENV_TABLE_CAP);
}

void print_env_table(){
    for (int i = 0; i < arr_size; ++i)
    {
        char* key = vars[i];
        char* val = hash_get(ht, vars[i]);
        printf("%s: %s\n", key, val);
    }
}

void free_env_table(){
    for (int i = 0; i < arr_size; ++i)
    {
        free(vars[i]);
        free(vals[i]);
    }
    hash_destroy(ht, &noop);
}

static int env(int c, char *v[]){
    printf("\n");
    print_env_table();
    return 1;
}

int env_validate(int argc, char** args){
    if(args[1]){
        printf ("Too many arguments\n");
        return 0;
    }
    return 1;
}

int env_execute(int argc, char** args){
    return env(argc, args);
}
