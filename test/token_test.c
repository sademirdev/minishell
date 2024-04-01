#include "testing.h"

void test_token_new() {
  t_test_run();
  int64_t a = 1;
  expect_null("basic ata test a", NULL);
  t_test_end();
}

void test_token_new_2() {
  t_test_run();
  int32_t a = 1;
  bool e = true;
  expect_null("at", NULL);
  expect_equal_bool("at", e, true);
  expect_equal_int32("be", a, (int32_t)1);
  t_token token = {.data = "at1", .type = ARG};
  t_token expected = {.data = "at", .type = ARG};
  t_token *pt = &token;
  t_token *pe = &expected;
  expect_equal_token("ooo", (t_token *)pt, (t_token *)pe);
  t_test_end();
}

void run_token_test() {
  t_group_run();
  test_token_new();
  test_token_new_2();
  t_group_finish();
}
