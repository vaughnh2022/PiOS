#include "rprintf.h"
#include "mmu.h"
#include <stdint.h>
extern struct table_descriptor_stage1 L1table[512];
unsigned long get_timer_count(){
   unsigned long *time_count_register =(unsigned long *)0x3f003004;
   return *time_count_register;
}
void wait_cycles(int plus){
   unsigned long first = get_timer_count()+plus;
   unsigned long second=0;
   while(second<first){
      second=get_timer_count();
   }
}
void wait_msec(int plus){
   unsigned long first = get_timer_count()+(plus*1000);
   unsigned long second=0;
   while(second<first){
      second=get_timer_count();
   }

}
void clearBSS(){
   extern int __bss_start,__bss_end;
   char *begin_bss = &__bss_start;
   char *end_bss = &__bss_end;
   for (char *ptr=begin_bss;ptr<=end_bss;ptr++){
      *ptr=0;
   }
}
unsigned int getEL(){
   unsigned int el;
   asm("mrs %0,CurrentEL"
       : "=r"(el)
       :
       :);
   return el;
}
void printInTerminal(){
   esp_printf(putc,"current execution level is %d\r\n",getEL());
}
void mapPager(){
   mapPages((void*)0,(void*)0);
  loadPageTable(&L1table[0]);
}
int kernel_main() {
  sd_init();
  int fatTester = fatInit();
  if(fatTester!=0){
     return 1;
  }
  uint16_t fileCluster = fatOpen("test");
  char readBuffer[512];
  fatRead(fileCluster,readBuffer);
   //this is a weird test but this should show my code works
   //readBuffer before being read was undefined
   //and if undefined this if statement will always be false
   //since this returns zero we can state something was written
   //in the readBuffer that isnt @
  if(readBuffer[1]!='@'){
      return 0;
  }
  return 1;
}

