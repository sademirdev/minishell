#include "testing.h"

void test_separate_prompt_by_space() {
  t_test_run();
  t_test_end();
}

void run_separator_test() {
  t_group_run();
  test_separate_prompt_by_space();
  t_group_finish();
}
