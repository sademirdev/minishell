#include "testing.h"

void test_token_count_pipe() {
  t_test_run();

  typedef struct s_case {
    char *name;
    t_token *token;
    int64_t expected;
  } t_case;

  t_token *t0_token_root = token_new(ft_strdup("test_root"), NONE);
  token_add_last(t0_token_root, token_new(ft_strdup("test_node_1"), NONE));
  token_add_last(t0_token_root, token_new(ft_strdup("test_node_2"), PIPE));
  token_add_last(t0_token_root, token_new(ft_strdup("test_node_3"), NONE));
  token_add_last(t0_token_root, token_new(ft_strdup("test_node_4"), PIPE));
  t_token *t1_token_root = token_new(ft_strdup("test_root"), NONE);
  token_add_last(t1_token_root, token_new(ft_strdup("test_node_1"), NONE));
  token_add_last(t1_token_root, token_new(ft_strdup("test_node_2"), ARG));
  token_add_last(t1_token_root, token_new(ft_strdup("test_node_3"), NONE));
  token_add_last(t1_token_root, token_new(ft_strdup("test_node_4"), RED_L));
  t_token *t2_token_root = token_new(ft_strdup("test_root"), NONE);

  t_case test_cases[] = {
      {
          .name = "basic test success",
          .token = t0_token_root,
          .expected = 2,
      },
      {
          .name = "zero test success",
          .token = t1_token_root,
          .expected = 0,
      },
      {
          .name = "single node test success",
          .token = t2_token_root,
          .expected = 0,
      },
  };

  int64_t size = sizeof(test_cases) / sizeof(t_case);
  int64_t i = 0;
  while (i < size) {
    t_case tc = test_cases[i];
    int64_t actual = token_count_pipe(tc.token);
    expect_equal_int64(tc.name, (int64_t)actual, (int64_t)tc.expected);
    token_dispose_all(&tc.token);
    i++;
  }

  t_test_end();
}

void run_token_test() {
  t_group_run();
  test_token_count_pipe();
  t_group_finish();
}
