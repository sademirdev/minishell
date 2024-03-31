#include "testing.h"

void test_token_new() {
  t_test_run();
  int64_t a = 1;
  expect_null("basic ata test a", NULL);
  t_test_end();
}

void test_token_new_2() {
  t_test_run();
  int64_t a = 1;
  expect_notnull("at", NULL);
  expect_notnull("be", NULL);
  t_test_end();
}

void run_token_test() {
  t_group_run();
  test_token_new();
  test_token_new_2();
  t_group_finish();
}
