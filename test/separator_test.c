#include "testing.h"

void test_separate_prompt_by_space() {
  t_test_run();
  t_token *sut = separate_prompt_by_space("at | ahmet");
  t_token exp = { .data = "at", .type = NONE};
  t_token exp1 = { .data = "|", .type = NONE};
  t_token exp2 = {"ahmet", NONE};
  exp.next = &exp1;
  exp1.prev = &exp;
  exp1.next = &exp2;
  exp2.prev = &exp1;
  expect_equal_token_list("son test", sut, &exp);
  t_test_end();
}

void run_separator_test() {
  t_group_run();
  test_separate_prompt_by_space();
  t_group_finish();
}
