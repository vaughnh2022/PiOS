#include <stdio.h> 

int kernel_main() {
   extern int __bss_start,__bss_end;
   char *begin_bss = &__bss_start;
   char *end_bss = &__bss_end;
   for (char *ptr=begin_bss;ptr<=end_bss;ptr++){
      *ptr=0;
   }
   return 0;
}

