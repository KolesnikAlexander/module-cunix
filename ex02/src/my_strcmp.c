#include <stdio.h>


int my_strcmp(char *str1, char *str2){
  int i=0;
 // printf("LOL");
  while((str1[i] != '\0') && (str2[i] != '\0') && 
      (str1[i] == str2[i]))
       {
         printf("First: %c\n", str1[i]);
         printf("Second: %c\n", str2[i]);
          i++;
       }
  printf("i=%d\n", i);
  if ((str1[i] == '\0') && (str2[i] == '\0'))
      return 0; 
  else if(str1[i] < str2[i])
      return -1;
  else
    return 1;
}

/*
int main(){
  int res =  my_strcmp("AB", "AC");
  printf("%d\n", res);
}
*/


