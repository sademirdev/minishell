#include "minishell.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool equal_ptr(void *actual, void *expected) { return (actual == expected); }

bool equal_int64(int64_t actual, int64_t expected) {
  return (actual == expected);
}

bool equal_int32(int32_t actual, int32_t expected) {
  return (actual == expected);
}

bool equal_bool(bool actual, bool expected) { return (actual == expected); }

bool equal_str(char *actual, char *expected) {
  if (!actual && !expected)
    return (true);
  if (!actual || !expected)
    return (false);
  return (strcmp(actual, expected) == 0);
}

bool equal_token_type(t_token_type actual, t_token_type expected) {
  return (actual == expected);
}

bool equal_token(t_token *actual, t_token *expected) {
  if (!actual && !expected)
    return (true);
  if (!actual || !expected)
    return (false);
  return (equal_str(actual->data, expected->data) &&
          equal_token_type(actual->type, expected->type));
}

bool equal_token_arr(t_token *actual, t_token *expected) {
  if (!actual && !expected)
    return (true);
  if (!actual || !expected)
    return (false);
  while (actual) {
    if (equal_token(actual, expected) == false)
      return (false);
    expected = expected->next;
    actual = actual->next;
  }
  return (true);
}

char *_token_type_tostr(t_token_type type) {
  switch (type) {
  case CMD:
    return "CMD";
  case ARG:
    return "ARG";
  case PIPE:
    return "PIPE";
  case RED_L:
    return "RED_L";
  case RED_LL:
    return "RED_LL";
  case RED_R:
    return "RED_R";
  case RED_RR:
    return "RED_RR";
  default:
    return "NONE";
  }
}

char *_basename(char const *path) {
  char *s = strrchr(path, '/');
  char *buffer = NULL;
  if (!s)
    buffer = strdup(path);
  else
    buffer = strdup(s + 1);
  char *rsp = ft_substr(buffer, 0, ft_strlen(buffer) - 2);
  free(buffer);
  return (rsp);
}
