#include <stdio.h>
#include <unistd.h>
#include "readGpio20.h"
#include "arduino-serial-lib.h"

int main()
{
   int fd =  serialport_init("/dev/ttyS0", 9600);

   if(fd == -1){ 
      printf( "Error opening serial port connection\n");
      return -1;
   }

  //char buffer[2];

   while(1){
      int value = readGpio20();

      if (value == -1) {
         serialport_flush(fd);
         serialport_close(fd);
         return -1;}
   
      if( value == 0){
        // sprintf(buffer,"%d\n",value);
        // printf("%s", buffer);
         serialport_write(fd, "1");
         usleep(500000);
      }
       serialport_flush(fd); 
   }

   serialport_flush(fd);
   serialport_close(fd);
   return 0;
}
