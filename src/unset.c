#include "minishell.h"
#include <stdlib.h>

static bool	validate_unset_arg(t_state *state, t_token *arg);

int	exec_unset(t_state *state, t_token *token)
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

static bool	validate_unset_arg(t_state *state, t_token *arg)
{
	int	i;

	if (!arg || !state)
		return (false);
	while (arg)
	{
		if (!is_al_underscore(arg->data[0]))
			return (print_exec_err(state, arg, 1, \
			ERRP_NOT_A_VALID_IDENTIFIER), false);
		i = 0;
		while (arg->data[i])
		{
			if (!is_alnum_underscore(arg->data[i]))
				return (print_exec_err(state, arg, 1, \
				ERRP_NOT_A_VALID_IDENTIFIER), false);
			i++;
		}
		arg = arg->next;
	}
	return (true);
}

char	**str_arr_remove(char **str_arr, char *key)
{
	char	**new_str_arr;
	int		i;
	int		len;

	if (!str_arr || !key)
		return (NULL);
	i = 0;
	while (str_arr[i])
		i++;
	len = i;
	new_str_arr = (char **) malloc(sizeof(char *) * len);
	if (!new_str_arr)
		return (NULL);
	i = 0;
	while (str_arr[i])
	{
		if (ft_strncmp(str_arr[i], key, ft_strlen(key)) == 0
			&& str_arr[i][ft_strlen(key)] == '=')
			free(str_arr[i]);
		else
			new_str_arr[i] = str_arr[i];
		i++;
	}
	new_str_arr[i] = NULL;
	return (free(str_arr), new_str_arr);
}
