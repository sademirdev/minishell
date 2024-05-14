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
	default:
		return ("NONE");
	}
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	t_token		*root;
	t_token		*tmp;
	t_state		*state;
	char		*line;
	t_token		**arr;
	int			i;

	(void)argc;
	state = malloc(sizeof(t_state));
	if (!state)
		return (1);
	state->argv = argv;
	state->env = environ;
	state->status = 12;
	while ("false")
	{
		line = readline("at: ");
		// line = ft_strdup("ls -l | grep a | wc -l");
		add_history(line);
		root = separate_prompt_by_space(line);
		tmp = root;
		root = extract_meta_chars(&root);
		handle_dollar(&root, state);
		handle_unnecessary_quotes(root);
		arr = token_separate_by_pipe(root);
		assign_token_arr_types(arr);
		i = 0;
		printf("\n");
		printf("===\n\n");
		while (arr[i])
		{
			root = arr[i];
			while (root)
			{
				printf("ptr: %p, DATA: %s\nTYPE: %s\n\n", root, root->data,
					_token_type_tostr(root->type));
				root = root->next;
			}
			printf("===\n\n");
			i++;
		}
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
