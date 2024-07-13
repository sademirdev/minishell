#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

static int	print_export(t_state *state, t_cmd *cmd);
static bool	validate_export_value(t_state *state, t_token *arg);
static int	export_env(t_token *arg, t_state *state);

static void	export_sort(t_state *state, int len)
{
	int		i;
	int		j;
	int		sorted;
	char	*temp;

	i = 0;
	sorted = 0;
	while (i < len - 1 && !sorted)
	{
		j = 0;
		sorted = 1;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(state->env[j], state->env[j + 1]) > 0)
			{
				temp = state->env[j];
				state->env[j] = state->env[j + 1];
				state->env[j + 1] = temp;
				sorted = 0;
			}
			j++;
		}
		i++;
	}
}

int	exec_export(t_state *state, t_token *token, t_cmd *cmd)
{
	if (!token || !state || !cmd)
		return (FAILURE);
	if (is_empty_arg(token->next))
	{
		export_sort(state, env_len(state));
		return (print_export(state, cmd));
	}
	if (validate_export_value(state, token->next) == false)
		return (FAILURE);
	if (export_env(token->next, state) != SUCCESS)
		return (FAILURE);
	state->status = 0;
	return (SUCCESS);
}

static int	print_export(t_state *state, t_cmd *cmd)
{
	int	i;

	if (!state || !state->env)
		return (FAILURE);
	i = 0;
	while (state->env[i])
	{
		dprint(cmd->bout, "declare -x ");
		dprintln(cmd->bout, state->env[i]);
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
		if (arg->type == ARG && !is_al_underscore(arg->data[0]))
			return (print_exec_err(state, arg, 1, \
				ERRP_NOT_A_VALID_IDENTIFIER), false);
		i = 0;
		while (arg->data[i])
		{
			if (arg->data[i] == '=')
				break ;
			if (arg->type == ARG && !is_alnum_underscore(arg->data[i]))
				return (print_exec_err(state, arg, 1, \
					ERRP_NOT_A_VALID_IDENTIFIER), false);
			i++;
		}
		arg = arg->next;
	}
	return (true);
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
		if (env_set_value(state, arg->data) != SUCCESS)
			return (FAILURE);
		arg = arg->next;
	}
	return (SUCCESS);
}
