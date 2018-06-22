#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/command.h"
#include"../include/binary_tree.h"
#include"../include/hash.h"
#include "../include/ls.h"
#include "../include/exit.h"
#include "../include/env.h"
#include "../include/export.h"
#include "../include/echo.h"

typedef struct command_t{
    char* name;
    int (*validate)(int argc, char** args);
    int (*execute)(int argc, char** args);
} command_t;

static int command_num = 0;
static int commands_list_size = 20;
command_t* commands_list = NULL;

void create_command(char* name,int (*validate)(int argc, char** args),int (*execute)(int argc, char** args)){
    command_t* cmd = commands_list + command_num;
    cmd->name = strdup(name);
    cmd->validate = validate;
    cmd->execute = execute;
    command_num++;
    if(command_num >= commands_list_size){
        commands_list_size += 20;
        commands_list = realloc(commands_list, commands_list_size*sizeof(command_t*));
        if (!commands_list){
            fprintf(stderr, "Allocation error\n");
            exit(EXIT_FAILURE);
        }
    }
}

void create_commands(){
    create_command("ls", &ls_validate, &ls_execute);
    create_command("exit", &exit_validate, &exit_execute);
    create_command("env", &env_validate, &env_execute);
    create_command("export", &export_validate, &export_execute);
    create_command("echo", &echo_validate, &echo_execute);
}

void init_commands_list(){
    commands_list = malloc(commands_list_size*sizeof(command_t));
    create_commands();
    init_env_table();
}

void free_commands_list(){
    for(int i = 0; i < command_num; i++){
        free(commands_list[i].name);
    }
    free(commands_list);
    free_env_table();
}

static command_t* get_command(char* name){
    for(int i = 0; i < command_num; i++){
        if(!strcmp(commands_list[i].name, name))
            return commands_list + i;       
    }
    return NULL;
}

int exec_cmd(int argc, char** args){
    command_t* cmd = get_command(args[0]);
    if (cmd){
        if ((*(cmd->validate))(argc, args)) 
            return ((*(cmd->execute))(argc, args));
        else
            return 1;
    }
    else{
        printf("Unknown command: %s\n", args[0]);
        return 1;
    } 
}

