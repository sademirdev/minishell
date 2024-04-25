#include "minishell.h"
#include <stdlib.h>

t_token	**lexer(char *prompt, t_state *state)
{
	t_token	*root;

	(void)state;
	t_error err = {
		5,
		"a",
		true
	};
	error_print(&err);
	exit(1);
	root = separate_prompt_by_space(prompt);
	return NULL;
}
