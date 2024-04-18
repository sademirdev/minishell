#ifndef TESTING_H
#define TESTING_H

#include "equal_primitive.h"
#include "minishell.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int err;
extern int err_in;

#define _RED "\x1B[31m"
#define _GRN "\x1B[32m"
#define _YEL "\x1B[33m"
#define _BLU "\x1B[34m"
#define _MAG "\x1B[35m"
#define _CYN "\x1B[36m"
#define _WHT "\x1B[37m"
#define _RESET "\x1B[0m"

#define _ERR_T "\t\t  Error Trace:\t%s\n"
#define _NOT_E "\t\t  Error:\tNot equal:\n"
#define _T_END "\t\t  Test:\t\t%s\n"
#define __ACT "\t\t\t\tactual  : "
#define __EXP "\t\t\t\texpected: "
#define _A_PTR __ACT "%p\n"
#define _E_PTR __EXP "%p\n"

#ifdef __GNUC__
#define _E_PTR_NOT_NULL __EXP "(not nil)\n"
#elif
#define _E_PTR_NOT_NULL __EXP "(0x0)\n"
#endif
#define _A_STR __ACT "%s\n"
#define _E_STR __EXP "%s\n"
#define _A_I64 __ACT "%" PRId64 "\n"
#define _E_I64 __EXP "%" PRId64 "\n"
#define _A_I32 __ACT "%d\n"
#define _E_I32 __EXP "%d\n"
#define _A_BOOL __ACT "%s\n"
#define _E_BOOL __EXP "%s\n"
#define _bool_tostr(x) x ? "true" : "false"
#define _E_TOKEN                                                               \
  __EXP "{\n\t\t\t\t    data: %s,\n\t\t\t\t    type: %s\n\t\t\t\t}\n"
#define _A_TOKEN                                                               \
  __ACT "{\n\t\t\t\t    data: %s,\n\t\t\t\t    type: %s\n\t\t\t\t}\n"
#define _TOKEN_LIST                                                            \
  "\t\t\t\t  {\n\t\t\t\t      data: %s,\n\t\t\t\t      type: %s\n\t\t\t\t  "   \
  "},\n"

#define t_test_run()                                                           \
  {                                                                            \
    err_in = 0;                                                                \
    printf("\t=== RUN %s " _WHT "(%s:%d)\n" _RESET, __func__, __FILE__,        \
           __LINE__);                                                          \
  }

#define t_test_end(test)                                                       \
  {                                                                            \
    if (err_in <= 0) {                                                         \
      char *group = _basename(__FILE__);                                       \
      printf(_CYN "\t--- PASS: %s/%s\n" _RESET, group, __func__);              \
      free(group);                                                             \
    }                                                                          \
  }

#define t_group_run()                                                          \
  {                                                                            \
    char *group = _basename(__FILE__);                                         \
    printf("=== RUN %s " _WHT "(%s)\n" _RESET, group, __FILE__);               \
    free(group);                                                               \
  }

#define t_group_finish()                                                       \
  {                                                                            \
    if (err == 0) {                                                            \
      char *group = _basename(__FILE__);                                       \
      printf("ok %s\n", group);                                                \
      free(group);                                                             \
    } else {                                                                   \
      printf(_MAG "ko %d Test failed.\n" _RESET, err);                         \
    }                                                                          \
  }

#define p_success(test)                                                        \
  {                                                                            \
    char *group = _basename(__FILE__);                                         \
    printf(_CYN "\t--- PASS: %s/%s\n" _RESET, group, __func__);                \
    free(group);                                                               \
  }

#define p_failure(group)                                                       \
  {                                                                            \
    printf(_RED "\t--- FAIL: %s\n" _RESET, __func__);                          \
    err++;                                                                     \
    err_in++;                                                                  \
  }

#define p_diff_ptr(test, a, e)                                                 \
  printf(_RED _ERR_T _NOT_E _E_PTR _A_PTR _T_END _RESET, __FILE__, a, e, test)
#define p_diff_ptr_not_null(test, a)                                           \
  printf(_RED _ERR_T _NOT_E _E_PTR_NOT_NULL _A_PTR _T_END _RESET, __FILE__, a, \
         test)
#define p_diff_str(test, a, e)                                                 \
  printf(_RED _ERR_T _NOT_E _E_STR _A_STR _T_END _RESET, __FILE__, e, a, test)
#define p_diff_int64(test, a, e)                                               \
  printf(_RED _ERR_T _NOT_E _E_I64 _A_I64 _T_END _RESET, __FILE__, (int64_t)a, \
         (int64_t)e, test)
#define p_diff_int32(test, a, e)                                               \
  printf(_RED _ERR_T _NOT_E _E_I32 _A_I32 _T_END _RESET, __FILE__, a, e, test)
#define p_diff_bool(test, a, e)                                                \
  printf(_RED _ERR_T _NOT_E _E_BOOL _A_BOOL _T_END _RESET, __FILE__,           \
         _bool_tostr(a), _bool_tostr(e), test)

#define p_diff_token(test, a, e)                                               \
  {                                                                            \
    t_token *actual = (t_token *)a;                                            \
    t_token *expected = (t_token *)e;                                          \
    printf(_RED _ERR_T _NOT_E _E_TOKEN _A_TOKEN _T_END _RESET, __FILE__,       \
           actual->data, _token_type_tostr(actual->type), expected->data,      \
           _token_type_tostr(expected->type), test);                           \
  }

#define p_diff_token_list(test, a, e)                                          \
  {                                                                            \
    t_token *actual = (t_token *)a;                                            \
    t_token *expected = (t_token *)e;                                          \
    printf(_RED _ERR_T _NOT_E _RESET, __FILE__);                               \
    printf(_RED __EXP "[\n" _RESET);                                           \
    while (actual) {                                                           \
      printf(_RED _TOKEN_LIST _RESET, actual->data,                            \
             _token_type_tostr(actual->type));                                 \
      actual = actual->next;                                                   \
    }                                                                          \
    printf(_RED "\t\t\t\t]\n" _RESET);                                         \
    printf(_RED __ACT "[\n" _RESET);                                           \
    while (expected) {                                                         \
      printf(_RED _TOKEN_LIST _RESET, expected->data,                          \
             _token_type_tostr(expected->type));                               \
      expected = expected->next;                                               \
    }                                                                          \
    printf(_RED "\t\t\t\t]\n" _RESET);                                         \
  }
#define expect_null(test, actual)                                              \
  {                                                                            \
    if (equal_ptr(actual, NULL)) {                                             \
      /* pass */                                                               \
    } else {                                                                   \
      p_failure(test);                                                         \
      p_diff_ptr(test, actual, NULL);                                          \
    }                                                                          \
  }

#define expect_notnull(test, actual)                                           \
  {                                                                            \
    if (!equal_ptr(actual, NULL)) {                                            \
      /*pass*/                                                                 \
    } else {                                                                   \
      p_failure(test);                                                         \
      p_diff_ptr_not_null(test, actual);                                       \
    }                                                                          \
  }

#define expect_equal_ptr(test, actual, expected)                               \
  {                                                                            \
    if (equal_ptr(actual, expected)) {                                         \
      /* pass */                                                               \
    } else {                                                                   \
      p_failure(test);                                                         \
      p_diff_ptr(test, actual, expected);                                      \
    }                                                                          \
  }

#define expect_equal_int64(test, actual, expected)                             \
  {                                                                            \
    int64_t a = (int64_t)actual;                                               \
    int64_t e = (int64_t)expected;                                             \
    if (equal_int64(actual, expected)) {                                       \
      /*pass*/                                                                 \
    } else {                                                                   \
      p_failure(test);                                                         \
      p_diff_int64(test, a, e);                                                \
    }                                                                          \
  }

#define expect_equal_int32(test, actual, expected)                             \
  {                                                                            \
    if (equal_int32(actual, expected)) {                                       \
      /*pass*/                                                                 \
    } else {                                                                   \
      p_failure(test);                                                         \
      p_diff_int32(test, actual, expected);                                    \
    }                                                                          \
  }

#define expect_equal_bool(test, actual, expected)                              \
  {                                                                            \
    if (equal_bool(actual, expected)) {                                        \
      /*pass*/                                                                 \
    } else {                                                                   \
      p_failure(test);                                                         \
      p_diff_bool(test, actual, expected);                                     \
    }                                                                          \
  }

#define expect_equal_token(test, actual, expected)                             \
  {                                                                            \
    if (equal_token(actual, expected)) {                                       \
      /*pass*/                                                                 \
    } else {                                                                   \
      p_failure(test);                                                         \
      p_diff_token(test, actual, expected);                                    \
    }                                                                          \
  }

#define expect_equal_token_list(test, actual, expected)                        \
  {                                                                            \
    t_token *a = (t_token *)actual;                                            \
    t_token *e = (t_token *)expected;                                          \
    if (equal_token_arr(a, e)) {                                               \
      /*pass*/                                                                 \
    } else {                                                                   \
      p_failure(test);                                                         \
      p_diff_token_list(test, a, e);                                           \
    }                                                                          \
  }

#define expect_equal_str(test, actual, expected)                               \
  {                                                                            \
    if (equal_str(actual, expected)) {                                         \
      /*pass*/                                                                 \
    } else {                                                                   \
      p_failure(test);                                                         \
      p_diff_str(test, actual, expected);                                      \
    }                                                                          \
  }

#endif
