#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h> 
#include <time.h>
#include "readGpio20.h"




int readGpio20()
{
   int fd = open("/sys/class/gpio/gpio20/value", O_RDONLY);
   if(fd < 0)
   {
      printf("Error reading gpio20\n");
      return -1;
   }

   char value_str[3];
   read(fd, value_str, 3);

   close(fd);
   return (atoi(value_str));
}
