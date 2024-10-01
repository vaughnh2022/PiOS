#include <stddef.h>
#include "page.h"
struct ppage physical_page_array[128];
struct ppage *free_cur_page;
void init_pfa_list(void){
   struct ppage *head = &physical_page_array[0];
   free_cur_page=head;
   free_cur_page->prev=NULL;
   for(int a=1;a<sizeof(physical_page_array)/sizeof(*head);a++){
      struct ppage *mover = &physical_page_array[a];
      free_cur_page->next=mover;
      mover->prev=free_cur_page;
      free_cur_page=mover;
   }
   free_cur_page->next=NULL;
   free_cur_page=head;
}
struct ppage *allocate_physical_page(unsigned int npages){
    struct ppage *returnHead = free_cur_page;
    for(int a=0;a<npages;a++){
       if(free_cur_page==NULL){
           return NULL;
       }
       free_cur_page=free_cur_page->next;
    }
    struct ppage *tempPoint = free_cur_page;
    free_cur_page=free_cur_page->next;
    tempPoint->next=NULL;
    free_cur_page->prev=NULL;
    returnHead->prev=NULL;
    return returnHead;
}
void free_physical_pages(struct ppage *ppage_list){
   struct ppage *listHolder = ppage_list;
   while(ppage_list->next!=NULL){
      ppage_list=ppage_list->next;
   }
   ppage_list->next=free_cur_page;
   free_cur_page->prev=ppage_list;
   free_cur_page=listHolder;
}

