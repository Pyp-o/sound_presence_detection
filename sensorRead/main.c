#include "readGpio20.h"
#include <stdio.h>

int main()
{
   
   while(1){
   if(readGpio20() == -1)
   {
	return -1;
   }
   printf("%d", readGpio20());
   }
  return 0;
}
