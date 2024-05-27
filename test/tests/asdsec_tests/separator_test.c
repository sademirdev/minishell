#include "../../libs/tin/testing.h"

void test_separate_prompt_by_space() {
  t_test_run();

	char *str = "at";
	expect_equal_int64("strlen", ft_strlen(str), 1);

  t_test_end();
}

void run_separator_test() {
  t_group_run();
  test_separate_prompt_by_space();
  t_group_finish();
}
