#include<stdio.h>
#include<stdlib.h>
#include"linked_list.h"
#include <string.h>

void list_print(node_t *head){
  printf("\n----LIST:----\n");
  node_t* e = head;
  int i = 0;
  while(e!=NULL){
       printf("%d)%s\n", i, e->data);
       e=e->next;
       i++;
  }
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

void  list_unshift(node_t **head, void *data){
  node_t* first = (node_t*) malloc(sizeof(node_t));
  first->data = data;
  first->next = *head;
  *head = first;
}

void nop(void* data){
}

void *list_pop(node_t **head){
 node_t* e = *head;
  while(e->next->next != NULL){
    e = e->next;
  }
  node_t* e_to_del = e+1;
  list_destroy(&(e_to_del), &nop);
  e->next = NULL;

}

void    *list_shift(node_t **head){
  node_t* new_head = (*head)->next;
  free((*head)->data);
  free(*head);
  *head = new_head;
}

void    *list_remove(node_t **head, int pos){
  node_t* p = (*head)+pos;
  if(p == *head)
   list_shift(head);
  if(p->next == NULL){
    list_pop(head);
  }
  else{
    (*head - 1)->data = (*head - 1)->data;
    free((*head)->data);
    free(*head); 
  }
}

void list_visitor(node_t *head, void (*fp)(void *data)){
  node_t* e = head;
  while(e != NULL){
    (*fp)(e->next);
    e=e->next;
  }
}

