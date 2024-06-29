#include "minishell.h"

static bool	validate_unset_arg(t_state *state, t_token *arg)
{
	int	i;

	if (!arg || !state)
		return (false);
	while (arg)
	{
		if (!is_al_underscore(arg->data[0]))
			return (print_exec_err(state, arg, 1, ERR_NOT_A_VALID_IDENTIFIER_J), false);
		i = 0;
		while (arg->data[i])
		{
			if (!is_alnum_underscore(arg->data[i]))
				return (print_exec_err(state, arg, 1, ERR_NOT_A_VALID_IDENTIFIER_J), false);
			i++;
		}
		arg = arg->next;
	}
	return (true);
}

int	handle_unset(t_token *token, t_state *state)
{
	if (!token || !state)
		return (FAILURE);
	if (!token->next)
		return (SUCCESS);
	token = token->next;
	while (token)
	{
		if (validate_unset_arg(state, token) == false)
			return (FAILURE);
		state->env = str_arr_remove(state->env, token->data);
		if (!state->env)
			return (FAILURE);
		token = token->next;
	}
	return (SUCCESS);
}