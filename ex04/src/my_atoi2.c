#include <stdio.h>
#include <stdlib.h>
int my_atoi(const char *nptr){
  int res = 0; 
  for (int i = 0; nptr[i] != '\0'; i++){
    res = res*10 + nptr[i] - '0';
    return res;
  }
}

int del(int val, int n){
  double res = val;
  for(int i = 0; i < n; i++){
    res = res/10;
  }
  return res;
}

char* my_itoa(int nmbr){
  char* str = calloc(11, sizeof(char));
  if(nmbr < 0){
    str[0] = '-';
    str[1] = '\0';
  }
  else{
    str[0] = '\0'
  }
  int num = nmbr;
  int prev = nmbr;
  for(int i = 8; i>=1; i--){
    int digit = del(nmbr, i);
    printf("%d\n", del(nmbr, i));
  }

}

int main(){
  int m = 654;
  int del_res = del(1246985683, 8);
  //printf("%d\n", del_res);
  my_itoa(6345);
}
