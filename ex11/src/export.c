#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include "../include/export.h"
#include "../include/env.h"

#define BUFSIZE 10

char **split_line(char *line, int* argc)
{
  int bufsize = BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, "=");
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, "=");
  }
  tokens[position] = NULL;
  *argc = position;
  return tokens;
}
void free_str(int argc, char** args){
    for(int i = 0; i < argc; i++){
        
    }
}
int put_to_env(int c, char* arg1, char* arg2) {
    char *k = malloc((strlen(arg1)+1)*sizeof(char));
    char *v = malloc((strlen(arg2)+1)*sizeof(char));
    strcpy(k, arg1);
    strcpy(v, arg2);
    new_var(k, v);
}

static int export (int c, char *args[]){
    for(int i = 1; i < c; i++){
        int evalc;
        char** evaluated = split_line(args[i], &evalc);
        if(evalc != 2){
            printf("Wrong argument: %s\n", args[i]);
            if(evaluated)
                free(evaluated);
            return 1;
        }
        else{
            put_to_env(evalc, evaluated[0], evaluated[1]);
            free(evaluated);
        }
        printf("\n");
    }
}

int export_validate(int argc, char** args){
    return 1;
}

int export_execute(int argc, char** args){
    return export(argc, args);
}
