#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static int	env_set_value_new(t_state *state, char *key_value);

int	exec_env(t_state *state, t_cmd *cmd)
{
	int	i;

	if (!state || !state->env || !cmd)
		return (FAILURE);
	i = 0;
	while (state->env[i])
		dprintln(cmd->out, state->env[i++]);
	return (SUCCESS);
}

int	env_set_pwd(t_state *state)
{
	char	buffer[4096];

	if (!state)
		return (FAILURE);
	buffer[0] = 'P';
	buffer[1] = 'W';
	buffer[2] = 'D';
	buffer[3] = '=';
	getcwd(buffer + 4, 4096);
	if (!buffer[4])
		return (FAILURE);
	if (env_set_value(state, buffer) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	env_set_value(t_state *state, char *key_value)
{
	int		i;
	int		len;
	bool	new;

	if (!state || !state->env || !key_value)
		return (FAILURE);
	new = true;
	i = 0;
	while (state->env[i])
	{
		len = ft_strlen(key_value) - ft_strlen(ft_strchr(key_value, '='));
		if (ft_strncmp(state->env[i], key_value, len) == 0
			&& state->env[i][len] == '=')
		{
			free(state->env[i]);
			state->env[i] = ft_strdup(key_value);
			new = false;
		}
		i++;
	}
	if (new)
		return (env_set_value_new(state, key_value));
	return (SUCCESS);
}

static int	env_set_value_new(t_state *state, char *key_value)
{
	char	*data;

	if (!state || !state->env || !key_value)
		return (FAILURE);
	data = ft_strdup(key_value);
	if (!data)
		return (FAILURE);
	state->env = str_arr_append(state->env, data);
	if (!state->env)
		return (free(data), FAILURE);
	return (SUCCESS);
}

char	*env_get_value(t_state *state, const char *key)
{
	int			i;
	size_t		len;

	if (!state || !state->env || !key)
		return (NULL);
	i = 0;
	while (state->env[i])
	{
		len = ft_strlen(key);
		if (ft_strncmp(state->env[i], key, len) == 0
			&& state->env[i][len] == '=')
			return (state->env[i] + 5);
		i++;
	}
	return (NULL);
}
