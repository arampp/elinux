#include "util.h"

/* represents the state of an observed device */
struct state {
  char* filename;        /* name of the dev file to read */
  char* data;            /* buffer for the raw data from the file */
  char* message_prefix;  /* prefix for the log message */
  int updated;           /* 1 if there is a new message otherwise 0 */
};

int
main_loop(struct opt_flags* options);

/* Updates the state of leds.

   @param led_state - A struct to save the current led state
   @return 0 if everything was ok
           1 if the file could not be read
           2 if there was a problem with allocating memory
*/
   
int
update_led_state(struct state* led_states);
