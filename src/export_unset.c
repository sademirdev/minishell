#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

static void	export_var(t_state *state, t_token *token, t_cmd *cmd);
static int	env_add(char *var, char *temp, t_state *state);

int has_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

static int has_alnum_underscore_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!is_alnum_underscore(str[i]))
			return (1);
		i++;
	}
	return (0);
}
static int has_only_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] <= '0' || str[i] >= '9')
			return (1);
		i++;
	}
	return (0);

}
int	handle_export(t_token *token, t_state *state, t_cmd *cmd)
{
	char	**var;
	t_token	*temp;

	if (!token)
		return (1);
	if (!token->next | (token && token->next && (token->next->type == PIPE
		|| token->next->type == RED_R || token->next->type == RED_RR)))
		return (export_var(state, token, cmd), 0);
	var = NULL;
	temp = token->next;
	if (temp->data[0] == '=' && temp->data[1] == '\0')
	{
		state->status = 1;
		return(1);
	}
	var = ft_split(temp->data, '=');
	if (!var)
		return (1);
	if (has_equal(var[0]) != 0 && has_only_num(var[0]) == 0)
	{
		print_err(var[0], ERR_FILE_NOT_VALID);
		state->status = 1;
		return (free(var), 1);
	}
		if (has_alnum_underscore_str(var[0]) != 0)
	{
		print_err(var[0], ERR_FILE_NOT_VALID);
		state->status = 1;
		return (free(var), 1);
	}
	if (env_add(var[0], temp->data, state) == 1)
	{
		state->status = 1;
		return (free(var), 1);
	}
	return (0);
}

static void	export_var(t_state *state, t_token *token, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (state->env[i])
	{
		if (!token->next)
		{
			write (2, "declare -x ", 12);
			write (2, state->env[i], ft_strlen(state->env[i]));
			write (2, "\n", 2);
		}
		else
		{
			write (cmd->out, "declare -x ", 12);
			write (cmd->out, state->env[i], ft_strlen(state->env[i]));
			write (cmd->out, "\n", 2);
		}
		i++;
	}
}

static int	env_add(char *var, char *temp, t_state *state)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (!state->env[i])
	{
		if (ft_strncmp(state->env[i], var, len) == 0
			&& state->env[i][ft_strlen(var)] == '=')
			free(state->env[i]);
		i++;
	}
	state->env[i] = ft_strdup(temp);
	if (!state->env[i])
		return (1);
	return (0);
}

int	handle_unset(t_token *token, t_state *state)
{
	int		i;
	int		len;
	char	**var;

	if (!token || !state || !token->next)
		return (1);
	var = NULL;
	var = ft_split(token->next->data, '=');
	if (!var)
		return (1);
	len = ft_strlen(var[0]);
	i = 0;
	while (state->env[i])
	{
		if (strncmp(state->env[i], var[0], len) == 0
			&& state->env[i][len] == '=')
		{
			while (state->env[i])
			{
				state->env[i] = state->env[i + 1];
				i++;
			}
			free (state->env[i]);
			break ;
		}
		i++;
	}
	state->env[i] = NULL;
	return (free(var), 0);
}
