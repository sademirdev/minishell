#ifndef INNER_H
#define INNER_H

#include <stdbool.h>
#include <stdint.h>
#include "minishell.h"

/* separator.c */
int64_t	pass_quoted_str(char *p, int64_t *oi);

/* token.c */
t_token	*token_new(char *data, t_token_type type);
void	token_add(t_token *root, t_token *new);

#endif
