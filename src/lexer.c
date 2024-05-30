#include "minishell.h"
#include <stdlib.h>

t_token	**run_lexer(char *prompt, t_state *state)
{
	t_token	*root;
	t_token	**token_arr;

	if (!prompt || !state)
		return (NULL);
	root = separate_prompt_by_space(prompt);
	if (!root)
		return (NULL);
	root = extract_meta_chars(&root);
	handle_dollar(&root, state);
	handle_unnecessary_quotes(root);
	token_arr = token_separate_by_pipe(root);
	if (!token_arr)
		return (NULL);
	assign_token_arr_types(token_arr);
	return (token_arr);
}
