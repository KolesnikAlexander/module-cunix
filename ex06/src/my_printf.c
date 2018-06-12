#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdarg.h>
char* my_itoa(int);

void  my_putc(const char *c){
  write(1, c , sizeof(char));
}

void  my_puts(const char *c){
  write(1, c, (strlen(c))*sizeof(char));
}

typedef struct status{
  int minus;
  int zero;
  int padding;
  int d;
  int s;
} format_status;

void print_format_arg(format_status* fs, va_list** args){
  char* par;
  char* par_result;
  int val_list_negative = 0;
  if(fs->s)
    par = va_arg(**args, char*);
  else if(fs->d){
    par = my_itoa(va_arg(**args, int));
    if (par[0] == '-'){
      val_list_negative = 1;
    }
  }

  if(fs->padding){
    char fill_c;
    if(fs->zero)
      fill_c = '0';
    else
      fill_c = ' ';
    int shift = fs->padding - strlen(par);
    if(shift > 0){
      par_result = (char*) calloc((strlen(par)+shift+1),sizeof(char));
      if(fs->minus){
        char* filling = (char*)calloc(shift+1, sizeof(char));
        memset(filling, fill_c, shift);
        filling[shift] = '\0';
        strcpy(par_result, par);
        strcat(par_result, filling);
      }
      else{
        memset(par_result, fill_c, shift);
        par_result[shift] = '\0';
        strcat(par_result, par); 

        if(val_list_negative && (fill_c == '0')){
          par_result[0] = '-';
          par_result[strlen(par_result) - strlen(par)] = '0';
        }
      }
    }
    else
      par_result = par;
  }
  else
    par_result = par;
  my_puts(par_result);
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
  print_format_arg(&status, args);
  return 1;
}

int check(const char** c, va_list** args){
  if(!**c)
    return 0;
  if(**c == '%'){
    (*c)++;
    return percent(c, args);
  }
  my_putc(*c);
  (*c)++;
  return 1;
}

int my_printf(const char *format, ...){
   va_list args;
   va_start(args, format);
   va_list* args_ptr = &args;
   va_list** args_dptr = &args_ptr;

   const char** c = &format; 
   while (check(c, args_dptr)){};
} 