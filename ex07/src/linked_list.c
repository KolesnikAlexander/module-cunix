#include<stdio.h>
#include<stdlib.h>
#include"linked_list.h"
#include <string.h>

void list_print(node_t *head){
  printf("\n----LIST:----\n");
  if(!head)
      printf("NULL");
  node_t* e = head;
  int i = 0;
  while(e!=NULL){
       printf("%d)%s\n", i, (char*)e->data);
       e=e->next;
       i++;
  }
}

node_t  *list_create(void *data){
  node_t* node = malloc(sizeof(node_t));
  node->data = data;
  node->next = NULL;
  return node;
}

void destroy_rec(node_t *head, void (*fp)(void *data)){
    if(head == NULL)
        return;
    destroy_rec(head->next, fp);
    (*fp)(head->data);
    free(head);
    head = NULL;
    return;
}

void  list_destroy(node_t **head, void (*fp)(void *data)){
  destroy_rec(*head, fp);
  *head = NULL;
}

void    list_push(node_t *head, void *data){
  node_t* e = head;
  while((e->next) != NULL){e = e->next;};
  e->next=list_create(data);
}

void  list_unshift(node_t **head, void *data){
  node_t* first = (node_t*) malloc(sizeof(node_t));
  first->data = data;
  first->next = *head;
  *head = first;
}

void nop(__attribute__((unused)) void* data){}

void free_data(void* data){
    free(data);
}
node_t* list_pop_rec(node_t* node){
    if(!node->next){
        list_destroy(&node, &free_data);
        return NULL;
    }
    node->next = list_pop_rec(node->next);
    return node;
    
}
void *list_pop(node_t **head){
    if(!*head)
        return NULL;
    return list_pop_rec(*head);
}

void *list_shift(node_t **head){
  node_t* new_head = (*head)->next;
  free((*head)->data);
  free(*head);
  *head = new_head;
	return head;
}

void *list_remove(node_t **head, int pos){
  if(pos == 0)
    list_shift(head);
  node_t* p = *head;
  for(int i = 0; i < pos-1; i++)
    p = p->next;
  
  if(p->next == NULL){
    list_pop(head);
  }
  else{
    free(p->data);
    (p-1)->next = p->next ;
    free((*head)->data);
    free(*head); 
  }
	return *head;
}

void list_visitor(node_t *head, void (*fp)(void *data)){
  node_t* e = head;
  while(e != NULL){
    (*fp)(e->next);
    e=e->next;
  }
}

