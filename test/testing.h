#ifndef TESTING_H
#define TESTING_H

#include "equal_primitive.h"
#include "minishell.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int err;
extern int err_in;

typedef enum { UNKNOWN, NOT_EQUAL } t_err_type;

typedef struct {
  int fails_group;
  int fails_test;
  int fails_internal_test;
  bool ended;
} t_test_suite;

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
#define _E_PTR_NOT_NULL __EXP "(not nil)\n"
#define _A_STR __ACT "%s\n"
#define _E_STR __EXP "%s\n"

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
#define p_diff_str(a, e)                                                       \
  printf(_RED _ERR_T _NOT_E _A_STR _E_STR _T_END _RESET, a, e)
#define p_diff_int64(a, e)                                                     \
  printf(_RED "  actual: %lld\nexpected: %lld\n" _RESET, a, e)
#define p_diff_int32(a, e)                                                     \
  printf(_RED "  actual: %ld\nexpected: %ld\n" _RESET, a, e)
#define p_diff_bool(a, e)                                                      \
  printf(_RED "  actual: %d\nexpected: %d\n" RESET, a, e)
#define p_diff_token(a, e)                                                     \
  {                                                                            \
    t_token *actual = (t_token *)a;                                            \
    t_token *expected = (t_token *)e;                                          \
    printf(_RED "expected: {\n  data: %s,\n  type: %s\n}" _RESET, a->data,     \
           _token_type_tostr(a->type));                                        \
    printf(_RED "  actual: {\n  data: %s,\n  type: %s\n}" _RESET, e->data,     \
           _token_type_tostr(e->type));                                        \
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

#endif
