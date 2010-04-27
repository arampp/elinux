#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "logdaemon.h"
#include "util.h"

#define FILE_LED_A "/sys/class/leds/a/brightness"
#define FILE_LED_B "/sys/class/leds/b/brightness"
#define FILE_LED_SYS "/sys/class/leds/sys/brightness"

#define LOGNAME "elinux"
#define LED_MESSAGE_PREFIX "LED brightness is now: "
int
update_led_state(struct state* led_state)
{
  /* read new data */
  int fd = open( led_state->filename, O_RDONLY );
  if( fd == -1) {
    return 1; 
  }
  
  char data[10];
  /*  if( data == NULL ) {
    return 1;

  }*/
  int bytes_read = read( fd, data, 3 );
  assert( bytes_read > 0 );
  data[bytes_read] = '\0';

  /* when there is new data, update the struct */
  if( (strcmp( led_state->data, data ) != 0) ) {
    /* update data section */
    if( strlen( led_state->data ) < strlen( data )) {
      if( realloc( led_state->data, strlen( data ) + 1 ) == NULL ) {
      return 2;
      }
    }

    strcpy( led_state->data, data );
    /* update led_state */
    led_state->updated = 1
      /* update message */;
}
  else {
    /* update led_state */
    led_state->updated = 0;
  }

  close( fd );
#if 0    

#endif
  return 0;
}

int
main_loop(struct opt_flags* options)
{
  struct state led_a_state = {
    .filename = FILE_LED_A,
    .data = malloc(10),
    .message_prefix = "LED A brightness is now: ",
    .updated = 0
  };
  
  if( options->verbose ){
    openlog(LOGNAME, LOG_PERROR, LOG_DAEMON);
  }
  else {
    openlog(LOGNAME, 0, LOG_DAEMON);
  }
  
  syslog(LOG_DEBUG, "entering main loop...");

  while (1) {
    int result = update_led_state( &led_a_state );
    if( result != 0 ) {
      if ( result == 1 ) {
        syslog( LOG_ERR, "Could not open device file" );
      }
      else if ( result == 2 ) {
        syslog( LOG_ERR, "Could not allocate memory" );
      }
      else {
        syslog( LOG_ERR, "Unknown error" );
      }
      return result;
    }
    else if( 1 == led_a_state.updated ) {
      syslog(LOG_NOTICE, "%s %s\n", led_a_state.message_prefix, led_a_state.data);
    }
    sleep(3);
  }
}
