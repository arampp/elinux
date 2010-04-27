#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "testcases.h"
#include "../src/logdaemon.h"

#define FILE_LED_ON "test/led_on"
#define FILE_LED_OFF "test/led_off"

START_TEST (test_update_led_state)
{
  printf( "\n TEST_UPDATE_LED_STATE\n\n" );
    struct state test_state = {
    .filename = FILE_LED_ON,
    .data = malloc(1), /* I do a malloc(1) here to test the reallocatin */
    .message_prefix = "Test ",
    .updated = 0
  };
    
    /* initial call */
    fail_if( update_led_state(&test_state) != 0, "return of update_led_state != 0\n");
    fail_unless(test_state.updated == 1, "state was not marked as updated");

    /* now updated must be set to 0 */
    printf( "Updated should be 0 - INPUT:\nFile: %s\nData: %s\nMessage_Prefix: %s\nUpdated: %d\n**********\n",
            test_state.filename, test_state.data, test_state.message_prefix, test_state.updated );
    fail_if( update_led_state(&test_state) != 0, "return of update_led_state != 0\n");
    fail_unless(test_state.updated == 0, "state was errorrous marked as updated\n");

    /* now we switch the led off */
    printf( "Led is on - INPUT:\nFile: %s\nData: %s\nMessage_Prefix; %s\nUpdated: %d\n**********\n",
            test_state.filename, test_state.data, test_state.message_prefix, test_state.updated );
    test_state.filename = FILE_LED_OFF;
    fail_if( update_led_state(&test_state) != 0, "return of update_led_state != 0\n");
    fail_unless(test_state.updated == 1, "state was not marked as updated\n");
}
END_TEST






TCase*
tc_logdaemon(void)
{
  TCase *tc = tcase_create ("tc_logdaemon");
  tcase_add_test (tc, test_update_led_state);
  return tc;
}
