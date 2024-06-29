#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

static int	print_env(t_state *state)
{
	int	i;

	if (!state || !state->env)
		return (FAILURE);
	i = 0;
	while (state->env[i])
	{
		dprint(STDOUT_FILENO, "declare -x ");
		dprintln(STDOUT_FILENO, state->env[i]);
		i++;
	}
	return (SUCCESS);
}

static bool	validate_export_value(t_state *state, t_token *arg)
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
			if (arg->data[i] == '=')
				break ;
			if (!is_alnum_underscore(arg->data[i]))
				return (print_exec_err(state, arg, 1, ERR_NOT_A_VALID_IDENTIFIER_J), false);
			i++;
		}
		arg = arg->next;
	}
	return (true);
}

static int	set_env_value(t_state *state, char *key)
{
	char	*data;
	int		i;
	int		len;
	bool	new;

	if (!state || !state->env || !key)
		return (FAILURE);
	new = true;
	i = 0;
	while (state->env[i])
	{
		len = ft_strlen(key) - ft_strlen(ft_strchr(key, '='));
		if (ft_strncmp(state->env[i], key, len) == 0 && state->env[i][len] == '=')
		{
			free(state->env[i]);
			state->env[i] = ft_strdup(key);
			new = false;
		}
		i++;
	}
	if (new)
	{
		data = ft_strdup(key);
		if (!data)
			return (FAILURE);
		state->env = str_arr_append(state->env, data);
		if (!state->env)
			return (free(data), FAILURE);
	}
	return (SUCCESS);
}

static int	export_env(t_token *arg, t_state *state)
{
	if (!arg || !state)
		return (FAILURE);
	while (arg)
	{
		if (!ft_strchr(arg->data, '='))
		{
			arg = arg->next;
			continue ;
		}
		if (set_env_value(state, arg->data) != SUCCESS)
			return (FAILURE);
		arg = arg->next;
	}
	return (SUCCESS);
}

int	handle_export(t_token *token, t_state *state, t_cmd *cmd)
{
	if (!token || !state || !cmd)
		return (FAILURE);
	if (!token->next)
		return (print_env(state));
	if (validate_export_value(state, token->next) == false)
		return (FAILURE);
	if (export_env(token->next, state) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
