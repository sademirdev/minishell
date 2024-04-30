#ifndef EQUAL_PRIMITIVE_H
#define EQUAL_PRIMITIVE_H

#include "minishell.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool equal_ptr(void *actual, void *expected);
bool equal_int64(int64_t actual, int64_t expected);
bool equal_int32(int32_t actual, int32_t expected);
bool equal_bool(bool actual, bool expected);
bool equal_str(char *actual, char *expected);
bool equal_token_type(t_token_type actual, t_token_type expected);
bool equal_token(t_token *actual, t_token *expected);
bool equal_token_arr(t_token *actual, t_token *expected);
char *_token_type_tostr(t_token_type type);
char *_basename(char const *path);

#endif