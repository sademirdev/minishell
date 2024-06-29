#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

int	print_env(t_state *state)
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

// a
// a=

static bool	is_al_underscore(char c)
{
	return (is_alpha(c) || c == '_');
}

bool	validate_export_value(t_state *state, t_token *arg)
{
	if (!arg)
		return (false);
	if (!is_al_underscore(arg->data[0]))
		return (print_exec_err(state, arg, 1, ERR_NOT_A_VALID_IDENTIFIER_J), false);
	return (false);
}

int	handle_export(t_token *token, t_state *state, t_cmd *cmd)
{
	if (!token || !state || !cmd)
		return (FAILURE);
	if (!token->next)
		return (print_env(state));
	if (validate_export_value(state, token->next) == false)
		return (FAILURE);
	return (SUCCESS);
}

int	handle_unset(t_token *token, t_state *state)
{
	int		i;
	int		len;
	char	**var;

	if (!token || !state || !token->next)
		return (FAILURE);
	var = NULL;
	var = ft_split(token->next->data, '=');
	if (!var)
		return (FAILURE);
	len = ft_strlen(var[0]);
	i = 0;
	while (state->env[i])
	{
		if (ft_strncmp(state->env[i], var[0], len) == 0
			&& state->env[i][len] == '=')
		{
			if (var[0] && ft_strncmp(var[0], "PATH", 4) == 0)
				return (free(var), FAILURE);
			free(state->env[i]);
			while (state->env[i])
			{
				state->env[i] = state->env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	if (state->env[i] != NULL)
		state->env[i] = NULL;
	return (free(var), SUCCESS);
}
