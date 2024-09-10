#include <stdio.h>
#include "list.h"

void list_add(struct list_element *list_head,struct list_element *new_element){
   new_element->next=list_head->next;
   list_head->next=new_element;
}
void list_remove(struct list_element *list_head,struct list_element *old_element){
   struct list_element cursor = list_head;
   if(list_head==old_element){
   list_head=list_head->next;
   } else {
      while(cursor->next!=old_element){
         cursor=cursor->next;
      }
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



