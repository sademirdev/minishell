#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

static void	export_var(t_state *state);
static int	env_add(char *var, char *temp, t_state *state);

int	handle_export(t_token *token, t_state *state)
{
	int		i;
	char	**var;
	t_token	*temp;

	if (!token)
		return (1);
	if (!token->next)
		return (export_var(state), 0);
	var = NULL;
	temp = token->next;
	if (temp->data[0] == '=' && temp->data[1] == '\0')
	{
		printf("minishell: export: `%s': not a valid identifier\n", temp->data);
		exit (1);
	}
	var = ft_split(temp->data, '=');
	if (!var)
		return (1);
	i = 0;
	if (env_add(var[0], temp->data, state) == 1)
		return (free(var), 1);
	return (0);
}

static void	export_var(t_state *state)
{
	int		i;

	i = 0;
	while (state->env[i])
		printf("declare -x %s\n", state->env[i++]);
}

static int	env_add(char *var, char *temp, t_state *state)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (!state->env[i])
	{
		if (strncmp(state->env[i], var, len) == 0
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
