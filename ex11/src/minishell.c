#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/command.h"

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
int sh_exit(int c, char *v[]){
        printf("$_> \n");
        return 0;
}

char *lsh_read_line(void){
  char *line = NULL;
  size_t bufsize = 0; 
  getline(&line, &bufsize, stdin);
  return line;
}

char **lsh_split_line(char *line, int* argc)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  *argc = position;
  return tokens;
}

int execute(int argc, char **v){
    if(v[0]){
      // Here can be other types of input
      return exec_cmd(argc, v);
    }
    return 1;
}

void lsh_loop(void){
  char *line;
  char **args;
  int argc;
  int status;

  do {
    printf("$_>");
    line = lsh_read_line();
    args = lsh_split_line(line, &argc);
    
    status = execute(argc, args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv){
    init_commands_list();
    lsh_loop();
    free_commands_list();
}



