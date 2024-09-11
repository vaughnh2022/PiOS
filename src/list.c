#include <stdio.h>
#include "list.h"

void list_add(struct list_element *list_head,struct list_element *new_element){  
   struct list_element *cursor=list_head;
   while(cursor->next!=null){
      cursor=cursor->next;
   }
   cursor->next=new_element;
}
void list_remove(struct list_element *list_head,struct list_element *old_element){
   struct list_element *cursor=list_head;
   if(cursor==old_element){
      cursor=cursor->next;
      list_head=cursor;
   } else {
      while(cursor->next!=NULL&&cursor->next!=old_element){
         cursor=cursor->next;
      }
      if(cursor->next!=NULL){
         cursor->next=cursor->next->next;
      }
}
int main(){
   struct list_element c = {NULL,0};
   struct list_element b = {&c,0};
   struct list_element a = {&b, 0};
   struct list_element *head = &a;
   return 0;
}



