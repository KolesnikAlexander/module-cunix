#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdarg.h>
char* my_itoa(int);

char* test_val;
void  my_putc(const char *c){
  write(1, c , sizeof(char));
}

int check(const char* c, va_list* args){
 c++;
 if(!c){
   my_putc(test_val);
   return 0; 
 }
 else
   my_putc(c);
}

int my_printf(const char *format, ...){
   va_list args;
   va_start(args, format);
   const char* c  = format; 

  while (*c){
    check(c++, &args);
  }; 
  /* 
   for (int i = 0; i < strlen(format); i++){  
    my_putc(&format[i]);
   }
   */

  // int val=va_arg(args, int);
  // printf("PRINTF: %d", val);
   
  // va_end (args);
   return 0;
}

int main(){
  /*
  printf("%05d %s\n %%%%" ,121, "was padded on 10");
  char i_str[20];
 // itoa(5, i_str, 10);
  printf("MYITOA: %s\n", my_itoa(5));
  
  printf("Padding of %s: [%05d]\n %d", "five", -42);
  printf("Padding of %s: [%5d]\n", "five", -42);
  printf("Padding of %s: [%-----5d]\n", "five", -42);
  */
  test_val =(char*) malloc(sizeof(char));
  *test_val = 'E';
  my_printf("%dABCD%%[d]", 12);
}
