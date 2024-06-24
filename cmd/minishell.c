#include "minishell.h"
#include <stdlib.h>

char	*_token_type_tostr(t_token_type type)
{
	switch (type)
	{
	case CMD:
		return ("CMD");
	case ARG:
		return ("ARG");
	case PIPE:
		return ("PIPE");
	case RED_L:
		return ("RED_L");
	case RED_LL:
		return ("RED_LL");
	case RED_R:
		return ("RED_R");
	case RED_RR:
		return ("RED_RR");
	case RED_FILE:
		return ("RED_FILE");
	case RED_HEREDOC:
		return ("RED_HEREDOC");
	default:
		return ("NONE");
	}
}

// static void	_token_print(t_token *token)
// {
// 	while (token)
// 	{
// 		printf("(data: %s, type: %s) ", token->data,
// 			_token_type_tostr(token->type));
// 		token = token->next;
// 	}
// }

// static void	token_print(t_token **token_arr)
// {
// 	int	i;

// 	i = 0;
// 	if (token_arr[i])
// 		printf("[  ");
// 	while (token_arr[i])
// 	{
// 		printf("[ ");
// 		_token_print(token_arr[i]);
// 		printf(" ] : ");
// 		i++;
// 	}
// 	if (token_arr[0])
// 		printf("  ]\n");
// }

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
	env_copy = (char **) malloc(sizeof(char *) * (i + 1));
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

int	main(int argc, char ** argv, char **env)
{
	t_state	*state;

	// handle_signals();
	state = state_init(argv, env);
	if (!state)
		return (argc);
	while (true)
	{
		state->prompt = readline(PROMPT);
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
		state->token_arr = run_lexer(state);
		// token_print(state->token_arr);
		if (state->token_arr && execute_prompt(state) != SUCCESS)
			continue ;
		// return (state_dispose(&state), 1); // todo(sademir): i remove this, because it quits the shell
		dispose_prompt(state);
	}
	return (state_dispose(&state), 0);
}
