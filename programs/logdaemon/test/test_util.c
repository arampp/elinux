#include <stdio.h>
#include <check.h>
#include "../src/util.h"
#include "testcases.h"

START_TEST (test_parse_options_verbose)
{
  struct opt_flags opts = { .verbose = 0};
  
  char* t_argv[] = {"bla", "-v"};
  int t_argc = 2;
  parse_options(t_argc, t_argv, &opts);
  fail_unless(opts.verbose == 1,
              "-v was set, but opts->verbose != 1");
}
END_TEST

START_TEST (test_parse_options_none)  
{
  struct opt_flags opts = { .verbose = 1 };
  
  char* t_argv[] = {"bla", ""};
  int t_argc = 1;
  parse_options(t_argc, t_argv, &opts);
  fail_unless(opts.verbose == 0,
              "-v was not set, but opts-verbose != 0");
}
END_TEST

TCase*
tc_util(void)
{
  TCase *tc = tcase_create ("tc_util");
  tcase_add_test (tc, test_parse_options_verbose);
  tcase_add_test (tc, test_parse_options_none);
  return tc;
}
