#include "minishell.h"
#include <stdlib.h>
#include <string.h>

t_token	*separate_prompt_by_space(char *prompt)
{
	t_token	*root;
	int		start;
	int		i;

	if (!prompt)
		return (NULL);
	i = 0;
	start = 0;
	root = NULL;
	while (prompt[i])
	{
		while (prompt[i] && (prompt[i] == ' ' || prompt[i] == '\t'))
			i++;
		start = i;
		while (prompt[i] && (prompt[i] != ' ' && prompt[i] != '\t'))
			if (pass_data(prompt, &i) != SUCCESS)
				return (0);
		if (create_separated_node(&root, prompt, start, i) != SUCCESS)
			return (NULL);
		while (prompt[i] && prompt[i] == ' ')
			i++;
	}
	return (root);
}

int	create_separated_node(t_token **root, char *prompt, int start, int i)
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

int	pass_data(char *prompt, int *i)
{
	if (prompt[*i] && (prompt[*i] == '\'' || prompt[*i] == '"'))
		if (pass_quoted_str(prompt, i) == -42)
			return (1);
	while (prompt[*i] && prompt[*i] != ' ' && prompt[*i] != '\t'
		&& prompt[*i] != '\'' && prompt[*i] != '"')
		(*i)++;
	return (0);
}

void	token_insert_dollar_nodes(t_token **token)
{
	t_token	*sub_nodes;
	t_token	*temp;

	if (!token || !*token)
		return ;
	temp = *token;
	sub_nodes = separate_prompt_by_space(temp->data);
	if (!sub_nodes)
	{
		if (temp->prev)
		{
			temp->prev->next = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
		}
		else
			*token = temp->next;
		token_dispose(&temp);
		return ;
	}
	token_insertion(token, temp, sub_nodes);
}

void	token_insertion(t_token **token, t_token *temp, \
	t_token *sub_nodes)
{
	t_token	*sub_last;

	if (temp->prev)
	{
		temp->prev->next = sub_nodes;
		sub_nodes->prev = temp->prev;
	}
	else
		*token = sub_nodes;
	sub_last = token_get_last(sub_nodes);
	if (!sub_last)
		return ;
	if (temp->next)
		sub_last->next = temp->next;
	if (temp->next)
		temp->next->prev = sub_last;
	token_dispose(&temp);
}
