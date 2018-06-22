#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include "../include/ls.h"

static int ls(int c, char *v[]){
        struct dirent *pDirent;
        DIR *pDir;

        if (c < 2) {
            printf ("Usage: ls <dirname>\n");
            return 1;
        }
        pDir = opendir (v[1]);
        if (pDir == NULL) {
            printf ("Dirrectory not found: '%s'\n", v[1]);
            return 1;
        }
        while ((pDirent = readdir(pDir)) != NULL) {
            if(strcmp(pDirent->d_name, ".") && strcmp(pDirent->d_name, ".."))
                printf ("%s ", pDirent->d_name);
        }
        printf("\n");
        closedir (pDir);
        return 1;
}

int ls_validate(int argc, char** args){
    return 1;
}

int ls_execute(int argc, char** args){
    return ls(argc, args);
}
