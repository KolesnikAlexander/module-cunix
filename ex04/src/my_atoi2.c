#include <stdio.h>
#include <stdlib.h>
int my_atoi(const char *nptr){
  int res = 0; 
  for (int i = 0; nptr[i] != '\0'; i++){
    res = res*10 + nptr[i] - '0';
    return res;
  }
}

