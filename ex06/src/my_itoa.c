#include <stdio.h>
#include <stdlib.h>
long ten_pow(int n){
  long res = 1;
  for(int i = 0; i < n; i++){
    res = res*10;
  }
  return res;
}

char* my_itoa(int nmbr){
char* zero = malloc(sizeof(char));
*zero = '0';
  if(nmbr == 0)
    return zero; 
  char* str = calloc(12, sizeof(char));
  str[11] = '\0';
  int sign = 1;
  if(nmbr < 0){
    sign = -1;
    nmbr = nmbr*(-1);
  }
  
  long a = nmbr;
  int i = 0;
  while(a != 0){
    int k = ten_pow(i+1);
    int r = a % k;
    a = a-r;
    r = r/(k/10);
    str[10-i] = '0'+r;
    i++;
  }
  if(i == 10)
    str[1] = '1';
  //sign = -1;
  if(sign == -1){
    str[10-i] = '-';
  }
  else
    i--;

  char* res = &str[10-i];
 // free(str);
  return res;
}

/*
int main(){
  printf("STR: %s", my_itoa(0));
}
*/


