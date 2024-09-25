#include "rprintf.h"
void putc(int data){
   char *ptr = 0x3F215040;
   *ptr = data;
}


