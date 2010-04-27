#include <stdio.h>
#include <unistd.h>

#include "util.h"

int
parse_options(int argc, char** argv, struct opt_flags* options)
{
  {
    int option;
    while ((option = getopt(argc, argv, "dhv")) >= 0) {
        switch (option)
        {
        case 'd':
          options->daemon = 1;
          break;

        case 'h':

          return(0);
          
        case 'v':
          options->verbose = 1;
          break;

        case '?':
          return 1;
        }
      }
  }
  return 0;
}

void
print_help()
{
  printf("Usage: logdaemon [-sv]\n\
-d \t run as daemon process\n\
-v \t verbose (print log messages also to STERR\n");
}

void
print_usage()
{
  print_help();
}

