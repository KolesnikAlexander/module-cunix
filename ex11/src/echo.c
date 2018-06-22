#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include "../include/echo.h"
#include "../include/hash.h"

extern hashtable_t *ht;

int echo_validate(int argc, char** args){
    return 1;
}
char* eval_arg(char* arg){
    char* evaluated;  
    if(arg[0] == '$'){
        if(arg[1] == '\0'){
            return NULL;
        }
        char* val = hash_get(ht, arg + 1);
        if(val == NULL)
            return NULL;
             
        evaluated = malloc((strlen(val) + 1) * sizeof(val));
        strcpy(evaluated, val);

    }
    else{
        evaluated = malloc((strlen(arg) + 1) * sizeof(arg));
        strcpy(evaluated, arg);
    }
    return evaluated;
}

int echo_execute(int argc, char** args){
    for(int i = 1; i < argc; i++){
        char* evaluated = eval_arg(args[i]);
        if(evaluated == NULL){
            printf("Wrong argument: %s\n", args[i]);
            return 1;
        }
        else{
            printf("%s ", evaluated);
            free(evaluated);
        }
    }
    printf("\n");
    return 1; 
}
