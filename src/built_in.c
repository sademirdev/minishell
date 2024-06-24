#include "minishell.h"

int	handle_built_in(t_token *token, t_state *state, t_cmd *cmd)
{
	int	result;

	result = 0;
	if (ft_strncmp(token->data, "echo", 5) == 0)
		result = handle_echo(token, state, cmd);
	else if (ft_strncmp(token->data, "cd", 3) == 0)
		result = handle_cd(token, state);
	else if (ft_strncmp(token->data, "pwd", 4) == 0)
		result = handle_pwd();
	else if (ft_strncmp(token->data, "export", 7) == 0)
		result = handle_export(token, state, cmd);
	else if (ft_strncmp(token->data, "unset", 6) == 0)
		result = handle_unset(token, state);
	else if (ft_strncmp(token->data, "env", 4) == 0)
		result = handle_env(token, state, cmd);
	else if (ft_strncmp(token->data, "exit", 5) == 0)
		result = handle_exit(token, state);
	return (result);
}

static bool	str_is_build_in(const char *str)
{
	if (!str)
		return (false);
	if (ft_strncmp(str, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (true);
	return (false);
}

bool	cmd_is_str_built_in(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd)
		return (false);
	return (str_is_build_in(cmd->cmd));
}

bool	token_is_built_in(t_token *token)
{
	if (!token || token->type != CMD)
		return (false);
	return (str_is_build_in(token->data));
}
