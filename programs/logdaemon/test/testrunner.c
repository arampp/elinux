#include <check.h>
#include "testcases.h"

int
main (void)
{
  int number_failed;
  Suite *s = suite_create ("Logdaemon TestSuite");

  TCase *testc_util = tc_util();
  suite_add_tcase (s, testc_util);
  suite_add_tcase (s, tc_logdaemon());

  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  
  number_failed = srunner_ntests_failed (sr);
  srunner_free(sr);
  return number_failed;
}
