#include "minishell.h"
#include <stdlib.h>

int64_t	create_separated_node(t_token **root, char *prompt, int64_t start,
		int64_t i)
{
	char	*data;
	t_token	*new;

	data = ft_substr(prompt, start, i - start);
	if (!data)
		return (token_dispose(root), 1);
	new = token_new(data, NONE);
	if (!new)
		return (free(data), token_dispose(root), 1);
	*root = token_add_last(*root, new);
	if (!*root)
		return (free(data), free(new), 1);
	return (0);
}

int64_t	pass_data(char *prompt, int64_t *i)
{
	if (prompt[*i] && (prompt[*i] == '\'' || prompt[*i] == '"'))
		if (pass_quoted_str(prompt, i) == -42)
			return (1);
	while (prompt[*i] && prompt[*i] != ' ' && prompt[*i] != '\''
		&& prompt[*i] != '"')
		(*i)++;
	return (0);
}


// todo(apancar): handle if return NULL, (syntax error)
t_token	*separate_prompt_by_space(char *prompt)
{
	int64_t	i;
	int64_t	start;
	t_token	*root;

	if (!prompt)
		return (NULL);
	i = 0;
	start = 0;
	root = NULL;
	while (prompt[i])
	{
		while (prompt[i] && prompt[i] == ' ')
			i++;
		start = i;
		while (prompt[i] && prompt[i] != ' ')
			if (pass_data(prompt, &i) != 0)
				return (0);
		// todo(sademir): add constants to header '0'
		if (create_separated_node(&root, prompt, start, i) != 0)
			return (NULL);
	}
	return (root);
}

void	token_insert_dollar_nodes(t_token **token)
{
	t_token	*sub_nodes;
	t_token	*temp;
	t_token	*sub_last;

	if (!token)
		return ; // todo(apancar): handle error
	temp = *token;
	sub_nodes = separate_prompt_by_space(temp->data);
	if (!sub_nodes)
		return ; // todo(apancar): handle error
	if (temp->prev)
	{
		temp->prev->next = sub_nodes;
		sub_nodes->prev = temp->prev;
	}
	else
		*token = sub_nodes;
	sub_last = token_get_last(sub_nodes);
	sub_last->next = temp->next;
	if (temp->next) 
		temp->next->prev = sub_last;
	token_dispose(&temp);
}

// bool	has_syntax_errs(t_token **root)
// {
// 	t_token *tmp;

// 	if (!root || !*root)
// 		return (true);
// 	tmp = *root;
// 	int	i = 0;
// 	while (tmp->prev)
// 	{
// 		i++;
// 		tmp = tmp->prev;
// 	}
// 	if (tmp->type == PIPE)
// 		return (true);
// 	tmp = tmp->next;
// 	while (tmp)
// 	{
// 		if (tmp->type != NONE && tmp->prev->type != NONE)
// 			return (true);
// 		tmp = tmp->next;
// 	}
// 	return (false);
// }
