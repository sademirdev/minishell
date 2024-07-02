#include "minishell.h"
#include <stdlib.h>

bool	str_is_all_space(const char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	token_is_all_space(t_token *root)
{
	if (!root)
		return (true);
	while (root)
	{
		if (!str_is_all_space(root->data))
			return (false);
		root = root->next;
	}
	return (true);
}

t_token	**run_lexer(t_state *state)
{
	t_token	*root;
	t_token	**token_arr;

	if (!state || !state->prompt)
		return (NULL);
	root = separate_prompt_by_space(state->prompt);
	if (!root)
		return (NULL);
	if (token_is_all_space(root))
		return (token_dispose_all(&root), state_dispose_single(&state), NULL);
	root = extract_meta_chars(&root);
	handle_dollar(&root, state);
	handle_unnecessary_quotes(root);
	token_arr = token_separate_by_pipe(root);
	if (!token_arr)
		return (NULL);
	assign_token_arr_types(token_arr);
	return (token_arr);
}
