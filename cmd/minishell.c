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

static void	state_init(t_state *state, char **argv, char **env)
{
	state->status = 0;
	state->argv = argv;
	state->env = env;
	state->prompt = 0;
	state->cmd_ct = 0;
}

static t_token	*prepare_lexer(t_state *state, char *line,t_token *root)
{
	root = separate_prompt_by_space(line);
	root = extract_meta_chars(&root);
	handle_dollar(&root, state);
	handle_unnecessary_quotes(root);
	return (root);
}

int	main(int argc, char **argv, char **env)
{
	t_state		*state;
	char		*line;
	t_token		**arr;
	t_token		*root;
	int			i;

	root = 0;
	(void)argc;
	state = malloc(sizeof(t_state));
	if (!state)
		return (1);
	state_init(state, argv, env);
	while (1)
	{
		line = readline("Minishell: ");
		state->prompt = line;
		if (!line)
			break ;
		int32_t err = syntax_check(state);
		if (err)
		{
			print_syntax_err(err);
			continue;
		}
		add_history(line);
		root = prepare_lexer(state, line, root);
		arr = token_separate_by_pipe(root);
		assign_token_arr_types(arr);
		pipe_exec(arr, state);
		i = 0;
		while (arr[i])
			token_dispose_all(&arr[i++]);
		free(line);
		line = 0;
		free(arr);
		arr = 0;
	}
	free(state);
	return (0);
}
