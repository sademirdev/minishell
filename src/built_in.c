#include "minishell.h"
#include <unistd.h>

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

int	exec_built_in(t_state *state, t_token *token, t_cmd *cmd)
{
	if (cmd->in == NAFD)
		cmd->in = STDIN_FILENO;
	if (cmd->out == NAFD)
		cmd->out = STDOUT_FILENO;
	if (ft_strncmp(token->data, "echo", 5) == 0)
		return (exec_echo(state, token, cmd));
	if (ft_strncmp(token->data, "cd", 3) == 0)
		return (exec_cd(state, token));
	if (ft_strncmp(token->data, "pwd", 4) == 0)
		return (exec_pwd(cmd));
	if (ft_strncmp(token->data, "export", 7) == 0)
		return (exec_export(state, token, cmd));
	if (ft_strncmp(token->data, "unset", 6) == 0)
		return (exec_unset(state, token));
	if (ft_strncmp(token->data, "env", 4) == 0)
		return (exec_env(state, cmd));
	if (ft_strncmp(token->data, "exit", 5) == 0)
		return (exec_exit(state, token));
	return (SUCCESS);
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
