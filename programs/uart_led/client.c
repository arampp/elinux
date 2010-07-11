/*
  This file is the client running on the host computer.
  With the help of the client, you can send commands over UART to toggle the leds.
*/

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "util.h"

#define DEBUG 0

#if DEBUG == 1
#define DEVICE "/tmp/uart_test"
#else
#define DEVICE "/dev/ttyUSB0"
#endif 
#define BUFSIZE 255

int
main( char argc, char** argv ) {

  /** Set up the serial device */
  int fd = open( DEVICE, O_RDWR );
  if( fd > 0 ) {
#if DEBUG == 0    
    //setup_uart(fd);
#endif
  }
  else{
    perror( DEVICE );
    exit( -1 );
  }
  
  /* This loop will read chars and send it over UART.  Giving a '.' as first
     character of a line will exit the program */
  int stop = 0;
  char buf[BUFSIZE];
  while ( !stop ) {

    if( fgets( buf, BUFSIZE, stdin ) != NULL ) {
      if( buf[0] == '.' ) {
        stop = 1;
      }
      /* We have to \0 terminate the string */
      /* FIXME this could lead to ab buffer overflow if the string is 255 long */
      buf[ strcspn( buf, "\n" ) + 1 ] = '\0';

      if( write( fd, buf, strlen( buf )) < 0 ) {
        perror( "Could not write to DEVICE" );
      }
      
      /* TODO this is just a dirty hack */
      char inbuf[ BUFSIZE ];
      int bytes_read;
      while (bytes_read = read( fd, inbuf, BUFSIZE > 0)) {
        printf("%s", inbuf);
        }
      
      
    }

    else {
      perror( "Could not read from STDIN" );      
    }
  }

  printf( "Bye\n" );
  return 0;
}
