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

int zero(const char** c, va_list* args){
   (*c)++;
   while(**c == '0'){};//skipping zeroes
   (*c)--;
}

typedef struct status{
  int minus;
  int zero;
  int padding;
  int d;
  int s;
} format_status;

void print_status(format_status* s){
  printf("\n----STATUS----\n");
  printf("MINUS: %d\n", s->minus);
  printf("ZERO: %d\n", s->zero);
  printf("PADDING: %d\n", s->padding);
  printf("D: %d\n", s->d);
  printf("S: %d\n", s->s);
}
int parse_integer(const char** str){
  const char* c = *str;
  int i = 0;
  while(c[i] && ('0'<= c[i] ) && (c[i]<='9')){
    i++;
  }
  char substr[i+1];
  memcpy(substr, *str, i);
  substr[i] = '\0';
  *str=*str+i;
  return atoi(substr);
}
int percent(const char** c, va_list* args){
  format_status status = {0};
  char cur = **c; 
  if(**c == '%'){
    my_putc(*c);
    (*c)++;
    return 1;
  }
  if(**c == '-'){ 
    status.minus = 1;
    (*c)++;
    if(!**c)
     return 0; 
  }
  if(**c == '0'){
    status.zero = 1;
    (*c)++;
    if(!**c)
      return 0;
  }

  if(('0'<=**c) && (**c <= '9'))
    status.padding = parse_integer(c);
  if(!**c)
    return 0;

  if(**c == 'd'){
    status.d = 1;
    (*c)++;
  }
  else if(**c == 's'){
    status.s = 1;
    (*c)++;
  }
  print_status(&status);
  return 1;
}

int check(const char** c, va_list* args){
  if(!**c)
    return 0;
  if(**c == '%'){
    (*c)++;
    return percent(c, args);
  }
   printf("\nUnhandled: %c\n", **c); 
   (*c)++;
  //my_putc(*c);
  return 1;
}

int my_printf(const char *format, ...){
   va_list args;
   va_start(args, format);
   const char** c = &format; 

   while (check(c, &args)){
   };
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
  test_val = malloc(sizeof(char));
  *test_val = 'E';
  my_printf("3%-0dA%32B%-032sCD%%[d]", 12);
}
