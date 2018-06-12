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

void print_format_arg(format_status* fs, va_list** args){
  char* par;
  char* par_result;
  if(fs->s)
    par = va_arg(**args, char*);
  else if(fs->d)
    par = my_itoa(va_arg(**args, int));
  else
    return;

  if(fs->padding){
    char fill_c;
    if(fs->zero)
      fill_c = '0';
    else
      fill_c = ' ';
    int shift = fs->padding - strlen(par);
    if(shift > 0){
      // printf("SHIFT: %d\n", shift);
      par_result = (char*) calloc((strlen(par)+shift+1),sizeof(char));
      memset(par_result, fill_c, shift);
      par_result[shift] = '\0';
      strcat(par_result, par);
    }
    else
      par_result = par;
  }
  else
    par_result = par;
  printf("%s", par_result);
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
int percent(const char** c, va_list** args){
  format_status status = {0};
  char cur = **c; 
  if(**c == '%'){
    printf("%c", **c); 
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
  print_format_arg(&status, args);
  //print_status(&status);
  return 1;
}

int check(const char** c, va_list** args){
  if(!**c)
    return 0;
  if(**c == '%'){
    (*c)++;
    return percent(c, args);
  }
  printf("%c", **c); 
  (*c)++;
  return 1;
}

int my_printf(const char *format, ...){
   va_list args;
   va_start(args, format);

   va_list* args_ptr = &args;
   va_list** args_dptr = &args_ptr;


   //
    // va_arg(**args_dptr, int);
    // va_arg(**args_dptr, int);
    // char* val = va_arg(**args_dptr, char*);
    // va_arg(**args_dptr, int);
    // printf("%s", val);
    // return 0;
   //

   const char** c = &format; 
   while (check(c, args_dptr)){};
} 
// int main(){
  
//  //  printf("%05d %s\n %%%%" ,121, "was padded on 10");
//  //  char i_str[20];
//  // // itoa(5, i_str, 10);
//  //  printf("MYITOA: %s\n", my_itoa(5));
  
//  //  printf("Padding of %s: [%05d]\n %d", "five", -42);
//  //  printf("Padding of %s: [%5d]\n", "five", -42);
//  //  printf("Padding of %s: [%-----5d]\n", "five", -42);
  
//   test_val = malloc(sizeof(char));
//   *test_val = 'E';
//    // my_printf("3%-0dA\n%5dB%-08sCD%%%d[d]", 12, 13, "LOL",17);
//   //my_printf("3%-03dA\n%dB%-0sCD%%%d[d]", 12, 13, "LOL",17);
  

//   my_printf("%s\n", "Hello Printf");
//   my_printf("We need 100%% of %s\n", "use case");
//   my_printf("It's %s's %s (%s)\n", "iGor", "phone", "TEXT");
//   my_printf("[%10s] [%4s] [%8s] [%12s]\n", "THIS", "IS", "PADDED", "TEXT");
//   my_printf("%d\n", 42);
//   my_printf("%d %s\n", 42, "is the answer");
//   my_printf("%010d %s\n", 42, "was padded on 10");
//   my_printf("%10d %s\n", 42, "was also padded using spaces");

// }
