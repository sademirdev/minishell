#include "testing.h"

void test_token_new() {
  t_test_run();
  int64_t a = 1;
  expect_null("basic ata test a", NULL);
  t_test_end();
}

void run_token_test() {
  t_group_run();
  test_token_new();
  t_group_finish();
}
