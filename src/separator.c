#include <stdlib.h>
#include "minishell.h"

int64_t	pass_quoted_str(char *p, int64_t *oi);

t_token	*separate_prompt_by_space(char *prompt)
{
	int64_t	i;
	int64_t	start;
	char	*data;
	t_token	*new;
	t_token	*tokens;

	if (!prompt)
		return (NULL);
	i = 0;
	start = 0;
	while (prompt[i])
	{
		while (prompt[i] && prompt[i] == ' ')
			i++;
		start = i;
		while (prompt[i] && prompt[i] != ' ')
		{
			if (prompt[i] && (prompt[i] == '\'' || prompt[i] == '"'))
				if (pass_quoted_str(prompt, &i) == -42)
					return (NULL);
			while (prompt[i] && prompt[i] != ' ' && prompt[i] != '\'' && prompt[i] != '"')
				i++;
		}
		data = ft_substr(prompt, start, i - start);
		if (!data)
			return (token_dispose(&tokens), NULL);
		new = token_new(data, NONE);
		if (!new)
			return (free(data), token_dispose(&tokens), NULL);
		tokens = token_add_last(tokens, new);
		if (!tokens)
			return (free(data), free(new), NULL);
	}
	return (tokens);
}

int64_t	pass_quoted_str(char *p, int64_t *oi)
{
	int64_t	i;

	i = *oi;
	if (p[i] == '"')
	{
		i++;
		while (p[i] && p[i] != '"')
			i++;
		*oi = i;
		if (!p[i])
			return (-42);
		(*oi)++;
	}
	else if (p[i] == '\'')
	{
		i++;
		while (p[i] && p[i] != '\'')
			i++;
		*oi = i;
		if (!p[i])
			return (-42);
		(*oi)++;
	}
	return (0);
}

t_token_type	get_meta_type(char *data, int64_t i)
{
	if (data[i] == '|')
		return (PIPE);
	if (data[i] == '<' && data[i + 1] == '<')
		return (RED_LL);
	if (data[i] == '<')
		return (RED_L);
	if (data[i] == '>' && data[i + 1] == '>')
		return (RED_RR);
	if (data[i] == '>')
		return (RED_R);
	return (NONE);
}

void	token_append_meta_pipe(t_token **token)
{
	t_token_type	type;
	t_token			*new;
	char			*data;

	if (type == PIPE)
	{
		data = ft_strdup("|");
		if (!data)
			return ; // todo(sademir): handle error
		new = token_new(data, PIPE);
		if (!new)
			return ; // todo(sademir): handle error
		token_add_prev(token, new);
	}
}

void	token_append_meta_redl(t_token **token)
{
	t_token_type	type;
	t_token			*new;
	char			*data;

	if (type == RED_L)
	{
		data = ft_strdup("<");
		if (!data)
			return ; // todo(sademir): handle error
		new = token_new(data, RED_L);
		if (!new)
			return ; // todo(sademir): handle error
		token_add_prev(token, new);
	}
}

void	token_append_meta_redll(t_token **token)
{
	t_token_type	type;
	t_token			*new;
	char			*data;

	if (type == RED_LL)
	{
		data = ft_strdup("<<");
		if (!data)
			return ; // todo(sademir): handle error
		new = token_new(data, RED_LL);
		if (!new)
			return ; // todo(sademir): handle error
		token_add_prev(token, new);
	}
}

void	token_append_meta_redr(t_token **token)
{
	t_token_type	type;
	t_token			*new;
	char			*data;

	if (type == RED_R)
	{
		data = ft_strdup(">");
		if (!data)
			return ; // todo(sademir): handle error
		new = token_new(data, RED_R);
		if (!new)
			return ; // todo(sademir): handle error
		token_add_prev(token, new);
	}
}

void	token_append_meta_redrr(t_token **token)
{
	t_token_type	type;
	t_token			*new;
	char			*data;

	if (type == RED_RR)
	{
		data = ft_strdup(">>");
		if (!data)
			return ; // todo(sademir): handle error
		new = token_new(data, RED_RR);
		if (!new)
			return ; // todo(sademir): handle error
		token_add_prev(token, new);
	}
}

void	token_append_meta(t_token **token)
{
	t_token_type	type;
	t_token			*new;
	int64_t			i;

	i = 0;
	while ((*token)->data[i])
	{
		type = get_meta_type((*token)->data, i);
		if (type == PIPE)
			token_append_meta_pipe(token);
		if (type == RED_L)
			token_append_meta_redl(token);
		if (type == RED_LL)
			token_append_meta_redll(token);
		if (type == RED_R)
			token_append_meta_redr(token);
		if (type == RED_RR)
			token_append_meta_redrr(token);
		if (type == RED_LL || type == RED_RR)
			i++;
		i++;
	}
}

t_token	*extract_meta_chars(t_token	**token)
{
	t_token			*tmp;
	t_token			*old_node;

	tmp = *token;
	while (tmp)
	{
		token_append_meta(token);
		old_node = tmp;
		tmp->prev->next = tmp->next->prev;
		tmp->next->prev = tmp->prev->next;
		tmp = tmp->next;
		token_dispose(&old_node);
	}
	return (NULL);
}

// int main()
// {
// 	t_token *root = separate_prompt_by_space("ls -l | cat");
// 	extract_meta_chars(&root);
// 	while (root)
// 	{
// 		printf("%s\n", root->data);
// 		root = root->next;
// 	}
// }
