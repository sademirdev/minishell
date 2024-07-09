#include "minishell.h"
#include <stdio.h>
#include "readline/history.h"
#include "readline/readline.h"
#include <stdlib.h>
#include <unistd.h>

int	g_sig = 0;

#define MESSAGE_COLOR "\033[1;33m"
void print_close(const char *func, char *cmd, int i, int j)
{
	(void)cmd;
	dprintf(2, COLOR_GREEN "[DEBUG]: [%s]: cmd: %s, closed=(%d:%d)\n" COLOR_RESET, func, cmd, i, j);
	usleep(200);
}
void print_cmd(t_cmd *cmd, int cmd_count)
{
	dprintf(2, MESSAGE_COLOR "%s, in=%s, out=%s, " COLOR_RESET, cmd->cmd, cmd->in == NAFD ? "NAFD" : ft_itoa(cmd->in), cmd->out == NAFD ? "NAFD" : ft_itoa(cmd->out));
	dprintf(2, MESSAGE_COLOR "heredoc{" COLOR_RESET);
	if (cmd_count > 0)
	{
		for (int i = 0; i < cmd_count; i++)
		{
			if (i != cmd_count - 1)
				dprintf(2, MESSAGE_COLOR "'%d'=%s, " COLOR_RESET, i, cmd->heredoc[i] == NAFD ? "NAFD" : ft_itoa(cmd->heredoc[i]));
			else
				dprintf(2, MESSAGE_COLOR "'%d'=%s" COLOR_RESET, i, cmd->heredoc[i] == NAFD ? "NAFD" : ft_itoa(cmd->heredoc[i]));
		}
	}
	dprintf(2, MESSAGE_COLOR "}\n" COLOR_RESET);
}
void print_fd(int **fd, int pipe_count)
{
	dprintf(2, MESSAGE_COLOR "[DEBUG]: pipe_fds{" COLOR_RESET);
	if (fd)
	{
		for (int i = 0; i < pipe_count; i++)
		{
			if (i == pipe_count - 1)
				dprintf(2, MESSAGE_COLOR "'%d'=(%d:%d)" COLOR_RESET, i, fd[i][0], fd[i][1]);
			else
				dprintf(2, MESSAGE_COLOR "'%d'=(%d:%d), " COLOR_RESET, i, fd[i][0], fd[i][1]);
		}
	}
	dprintf(2, MESSAGE_COLOR "}\n" COLOR_RESET);
}
void print_debug(const char *tag, const char *message, t_cmd *cmd, int cmd_count, int **fd)
{
  // todo: delete this on release
	dprintf(2, MESSAGE_COLOR "[DEBUG]: [%s]: %s\n" COLOR_RESET, tag, message);
	dprintf(2, MESSAGE_COLOR "[DEBUG]: cmd = " COLOR_RESET);
	print_cmd(cmd, cmd_count);
	print_fd(fd, cmd_count - 1);
	dprintf(2, COLOR_RED "---\n" COLOR_RESET);
	usleep(200);
}

static void	dispose_env_idx(char **copy_env, int i)
{
	if (!copy_env)
		return ;
	if (i > 0)
		while (i--)
			free(copy_env[i]);
	free(copy_env);
}

char	**copy_env(char **env)
{
	char	**env_copy;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
		i++;
	env_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		if (!env_copy[i])
			return (dispose_env_idx(env_copy, i), NULL);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

static t_state	*state_init(char **argv, char **env)
{
	t_state	*state;

	state = malloc(sizeof(t_state));
	if (!state)
		return (NULL);
	state->env = copy_env(env);
	if (!state->env)
		return (state_dispose(&state), NULL);
	state->argv = argv;
	state->token_arr = NULL;
	state->prompt = NULL;
	state->status = 0;
	state->cmd_ct = 0;
	state->err = 0;
	return (state);
}

int	main(int argc, char **argv, char **env)
{
	t_state	*state;

	handle_signals();
	state = state_init(argv, env);
	if (!state)
		return (argc);
	while (true)
	{
		state->prompt = readline(COLOR_GREEN PROMPT COLOR_RESET);
		if (!state->prompt)
			break ;
		add_history(state->prompt);
		state->err = syntax_check(state);
		if (state->err)
		{
			print_syntax_err(state->err);
			dispose_prompt(state);
			continue ;
		}
		state->err = SUCCESS;
		state->token_arr = run_lexer(state);
		if (!state->token_arr)
		{
			free(state->prompt);
			continue ;
		}
		run_executor(state);
	}
	return (state_dispose(&state), state->status);
}
