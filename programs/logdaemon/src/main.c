#include <stdio.h>
#include <unistd.h>

#include "util.h"
#include "logdaemon.h"

int
main(int argc, char** argv)
{
  struct opt_flags options = {
    .verbose = 0,
    .daemon = 0
  };
  if( 0 != parse_options( argc, argv, &options )) {
    return 1;
  }

  /* here we daemonify the program if the option was set */
  if( options.daemon ) {
    if( daemon( 0, 0 ) != 0) {
      perror("main(): could not start daemon process");
      return 1;
    }
  }
  
  int result = main_loop(&options);
  return result;
}
  
