#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int my_atoi(const char *nptr){
  int n = strlen(nptr);
  int res = 0;
  int mult = 1;
  char c;

  int i = n-1;
  int x = ('0'<=nptr[i]) && (nptr[i] <= '9');
  printf("Bool val: %d",x);
  while ((i>=0) && !(('0'<=nptr[i])&&(nptr[i]<='9'))){
    i--;
  }

  printf("Symbol:%c\n", nptr[i]);
   for(; i>=0 ; i--){
     printf("Loop: %c\n", nptr[i]);
     c = nptr[i];
     if(c == '-')
      break;

     if (!(('0' <= c)&&( c <= '9')))
      break;   

    res = res + mult*(c - '0' );
    mult = mult*10;
  }
   if(c == '-')
     return -res;
   return res;

}
/*
int main(){
  printf("%d", my_atoi("123456789"));
} 
*/

