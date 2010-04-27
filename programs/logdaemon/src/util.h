#ifndef _UTIL_H_
#define _UTIL_H_

/* flags for the command line options */
struct opt_flags {
  int verbose;
  int daemon;
};


/* Parses command line options and stores them in ops

   @param argc - argc from main
   @param argv - argv from main
   @param opts - An instance of options to store the command line options
 */
int
parse_options(int argc, char** argv, struct opt_flags* options);

void
print_usage();

void
print_help();

#endif
