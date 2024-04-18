#include "testing.h"

void test_token_dispose() {
  t_test_run();

  typedef struct s_case {
    char *name;
    t_token *token;
    t_token *expected_token;
    t_token *expected_token_data;
    enum check_type { CHECK_NULL, CHECK_NORMAL } type;
  } t_case;

  t_token *t0_token_root = NULL;

  t_case test_cases[] = {
      {
          .name = "should do nothing when token is null",
          .token = t0_token_root,          // NULL
          .expected_token = t0_token_root, // NULL
          .expected_token_data = NULL,
          .type = CHECK_NULL,
      },
  };

  int64_t size = sizeof(test_cases) / sizeof(t_case);
  int64_t i = 0;
  while (i < size) {
    t_case tc = test_cases[i];
    token_dispose(&tc.token);
    switch (tc.type) {
    case CHECK_NORMAL:
      expect_null(tc.name, tc.expected_token);
      expect_null(tc.name, tc.expected_token_data);
      break;
    case CHECK_NULL:
      expect_equal_ptr(tc.name, tc.expected_token, tc.token);
      expect_null(tc.name, tc.expected_token_data);
      break;
    }
    i++;
  }

  t_test_end();
}

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
  t_token *t3_token_root = NULL;

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
      {
          .name = "null node",
          .token = t3_token_root,
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

// void test_token_separate_by_pipe() {
//   t_test_run();

//   typedef struct s_case {
//     char *name;
//     t_token *token;
//     t_token **expected;
//     int64_t _size;
//   } t_case;

//   t_token *t0_token_root = token_new(ft_strdup("test_root"), NONE);
//   token_add_last(t0_token_root, token_new(ft_strdup("test_node_1"), NONE));
//   token_add_last(t0_token_root, token_new(ft_strdup("test_node_2"), PIPE));
//   token_add_last(t0_token_root, token_new(ft_strdup("test_node_3"), NONE));
//   token_add_last(t0_token_root, token_new(ft_strdup("test_node_4"), ARG));
//   token_add_last(t0_token_root, token_new(ft_strdup("test_node_5"), PIPE));
//   token_add_last(t0_token_root, token_new(ft_strdup("test_node_6"), NONE));
//   token_add_last(t0_token_root, token_new(ft_strdup("test_node_7"), ARG));
//   t_token *t0_expected_list_elem_1 = token_new(ft_strdup("test_root"), NONE);
//   token_add_last(t0_expected_list_elem_1,
//                  token_new(ft_strdup("test_node_1"), NONE));
//   t_token *t0_expected_list_elem_2 = token_new(ft_strdup("test_node_3"), NONE);
//   token_add_last(t0_expected_list_elem_2,
//                  token_new(ft_strdup("test_node_4"), ARG));
//   t_token *t0_expected_list_elem_3 = token_new(ft_strdup("test_node_6"), NONE);
//   token_add_last(t0_expected_list_elem_3,
//                  token_new(ft_strdup("test_node_7"), ARG));
//   t_token *t0_expected[3] = {
//       t0_expected_list_elem_1,
//       t0_expected_list_elem_2,
//       t0_expected_list_elem_3,
//   };

//   t_case test_cases[] = {
//       {
//           .name = "should delete pipes and return three separated token node "
//                   "list when there is two pipe exist",
//           .token = t0_token_root,
//           .expected = t0_expected,
//           ._size = 3, // used as metadata from test
//       },
//   };

//   int64_t size = sizeof(test_cases) / sizeof(t_case);
//   int64_t i = 0;
//   while (i < size) {
//     t_case tc = test_cases[i];
//     t_token **actual = token_separate_by_pipe(tc.token);
//     for (int64_t j = 0; j < tc._size; j++) {
//       t_token *a = (t_token *)(*actual);
//       t_token *e = (t_token *)(*tc.expected);
//       expect_equal_token_list(tc.name, a, e);
//     }
//     token_dispose_all(&tc.token);
//     i++;
//   }

//   t_test_end();
// }

void run_token_test() {
  t_group_run();
  test_token_dispose();
  test_token_count_pipe();
  // test_token_separate_by_pipe();
  t_group_finish();
}
