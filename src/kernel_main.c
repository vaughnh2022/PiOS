#include <stdio.h> 
unsigned long get_timer_count(){
   unsigned long *time_count_register =0x3f003004;
   return *time_count_register;
}
void wait(){
   unsigned long first = get_timer_count();
   unsigned long second =0;
   while(second<first){
      second=get_timer_count();
   }
}
int kernel_main() {
   extern int __bss_start,__bss_end;
   char *begin_bss = &__bss_start;
   char *end_bss = &__bss_end;
   for (char *ptr=begin_bss;ptr<=end_bss;ptr++){
      *ptr=0;
   }
   unsigned long timer_count= get_timer_count();
   unsigned long tempLong = timer_count+0;
   wait();
   return 0;
}

