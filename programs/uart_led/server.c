/*
  This code is the led server which runs on the target. It reads from UART and
  turns the leds on or off
*/

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "util.h"

#define DEBUG 0

#if DEBUG == 1
#define DEVICE "stdin"
#define LED_A "/tmp/led"
#else
#define DEVICE "/dev/ttyS0"
#define LED_A "/sys/class/leds/a/brightness"
#endif 
#define BUFSIZE 255


int
main( char argc, char** argv ) {
  /* Set up the serial device */
#if DEBUG == 0
  int uart_fd = open( DEVICE, O_RDWR );
#else
  int uart_fd = STDIN_FILENO;
#endif
  int led_fd = open( LED_A, O_WRONLY );

  if( uart_fd < 0 ) { perror( DEVICE ); exit ( -1 ); }
  if( led_fd < 0 ) { perror( LED_A ); exit ( -1 ); }

#if DEBUG == 0    
  //    setup_uart(uart_fd);
#endif

  int stop = 0;
  char buf[BUFSIZE];
  while(1) {
    
    int bytes_read = read( uart_fd, buf, BUFSIZE );
    if(  bytes_read > 0 ) {
#if DEBUG == 1
      /* in debug, the string comes from stdin and is \n terminated instead of \0 */
      /* TODO this one with regexps */
      buf[ strcspn( buf, "\n" ) ] = '\0';
      printf("%s\n", buf);
#endif
      if( strcmp( "on", buf ) == 0 ) {
        if( write( led_fd, "1", 1) < 0 ) { perror( "Could not write to LED_A" ); }
      }
      else if( strcmp( "off", buf ) == 0 ) {
        if( write( led_fd, "0", 1 ) < 0) { perror( "Could not write to LED_A"); }
      }
    }
    else {
      perror( "Could not read from DEVICE" );
    }
  }
  close(led_fd);
  close(uart_fd);
  return 0;
}
