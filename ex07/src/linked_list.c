#include<stdio.h>
#include<stdlib.h>
#include"linked_list.h"
#include <string.h>

void list_print(node_t *head){
  printf("\n----LIST:----\n");
  node_t* e = head;
  for(int i = 0;e!=NULL;e=e->next, i++)
    printf("%d)%s\n", i, e->data);
}

node_t  *list_create(void *data){
  node_t* node = malloc(sizeof(node_t));
  node->data = malloc(strlen((char*) data)+1);
  strcpy(node->data, data);
  node->next = NULL;
}

void destroy_rec(node_t **head, void (*fp)(void *data)){
 (*fp)((**head).data);
 if((**head).next == NULL)
  return;
 (*head)++;
 destroy_rec(head, fp);
 free((**head).next);
}
void  list_destroy(node_t **head, void (*fp)(void *data)){
 if(!(*head))
  return;
 destroy_rec(head, fp);
 free((*head));
}



void    list_push(node_t *head, void *data){
  node_t* e = head;
  while((e->next) != NULL){e = e->next;};
  

  node_t* next =(node_t*) malloc(sizeof(node_t));
  char* next_data =(char*) malloc(strlen(data)+1);
  strcpy(next_data, data);
  next->data = next_data;
  next->next = NULL;
  e->next = next;



}
void    list_unshift(node_t **head, void *data){

}

void    *list_pop(node_t **head){

}
void    *list_shift(node_t **head){

}
void    *list_remove(node_t **head, int pos){

}

void    list_visitor(node_t *head, void (*fp)(void *data)){

}

/*
void test_destroy_noop(void *data)
{
  data;
}

int test_create()
{
  node_t  *head;
  char    *valid;

  head = list_create("test");
  valid = head->data;

  printf("LIST:\n-----\n");
  list_print(head);
  list_destroy(&head, &test_destroy_noop);
  list_print(head);
  return strcmp(valid, "test");
}
*/
/*
int main(){
  test_create();
}
*/
