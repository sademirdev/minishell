#include "testing.h"

void test_separator_by_space() {
  t_test_run();
  int64_t a = 1;
  expect_notnull("aaaa", &a);
  expect_notnull("vvv", &a);
  t_test_end();
}

void run_separator_test() {
  t_group_run();
  test_separator_by_space();
  t_group_finish();
}
