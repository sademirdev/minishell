#include "minishell.h"
#include <stdlib.h>

int64_t			pass_quoted_str(char *p, int64_t *oi);

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
			while (prompt[i] && prompt[i] != ' ' && prompt[i] != '\''
				&& prompt[i] != '"')
				i++;
		}
		// todo(sademir): add constants to header '0'
		if (create_separated_node(&root, prompt, start, i) != 0)
			return (NULL);
	}
	return (root);
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
	else
		return (NONE);
}

void	token_append_meta_pipe(t_token **token)
{
	t_token	*new;
	char	*data;

	data = ft_strdup("|");
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, PIPE);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}

void	token_append_meta_redl(t_token **token)
{
	t_token	*new;
	char	*data;

	data = ft_strdup("<");
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, RED_L);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}

void	token_append_meta_redll(t_token **token)
{
	t_token	*new;
	char	*data;

	data = ft_strdup("<<");
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, RED_LL);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}

void	token_append_meta_redr(t_token **token)
{
	t_token	*new;
	char	*data;

	data = ft_strdup(">");
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, RED_R);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}

void	token_append_meta_redrr(t_token **token)
{
	t_token	*new;
	char	*data;

	data = ft_strdup(">>");
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, RED_RR);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}

bool	is_meta(t_token_type type)
{
	return (type == PIPE || type == RED_L || type == RED_LL || type == RED_R
		|| type == RED_RR);
}

bool	is_meta_char(char *data, int64_t i)
{
	if (!data)
		return (false);
	if (data[i] == '>' && data[i + 1] == '>')
		return (true);
	if (data[i] == '<' && data[i + 1] == '<')
		return (true);
	return (data[i] == '|' || data[i] == '>' || data[i] == '<');
}

bool	has_meta_char(char *data, int64_t i)
{
	while (data[i])
	{
		if (is_meta_char(data, i))
			return (true);
		i++;
	}
	return (false);
}

void	token_append_str(t_token **token, int64_t start, int64_t i)
{
	t_token	*new;
	char	*data;

	data = ft_substr((*token)->data, start, i - start);
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, NONE);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}

char	get_in_quote(char old, char data)
{
	if (old == '"' && data == '"')
		old = 0;
	else if (old == '\'' && data == '\'')
		old = 0;
	else if (data == '\'' || data == '"')
		old = data;
	return (old);
}

void	token_append_all(t_token **token, int64_t start, int64_t i,
		t_token_type type)
{
	// todo(hkizrak-): check if there are two PIPE side by side after this func
	// (throw syntax error)
	if (type == PIPE)
		token_append_meta_pipe(token);
	if (type == RED_L)
		token_append_meta_redl(token);
	// todo(hkizrak-): check if there are > or >> after this created node (throw
	// syntax error)
	if (type == RED_LL)
		token_append_meta_redll(token);
	if (type == RED_R)
		token_append_meta_redr(token);
	// todo(hkizrak-): check if there are < or << after this created node (throw
	// syntax error)
	if (type == RED_RR)
		token_append_meta_redrr(token);
}

void	token_append_meta_data_init(t_token_append_meta_data *md,
		t_token **token)
{
	md->i = 0;
	if (!is_meta_char((*token)->data, md->i))
		md->start = 0;
	else
		md->start = -1;
	md->has_meta = false;
	md->in_quote = 0;
}

// todo(hkizrak-): check possible errors for side by side metas (throw syntax
// error)  a<b
bool	token_append_meta(t_token **token)
{
	t_token_append_meta_data	md;
	bool						a;

	token_append_meta_data_init(&md, token);
	while ((*token)->data[md.i])
	{
		md.in_quote = get_in_quote(md.in_quote, (*token)->data[md.i]);
		md.type = get_meta_type((*token)->data, md.i);
		if (is_meta(md.type) && !md.in_quote)
		{
			md.has_meta = true;
			if (md.start != -1)
				token_append_str(token, md.start, md.i);
			token_append_all(token, md.start, md.i, md.type);
			if (md.type == RED_LL || md.type == RED_RR)
				md.i++;
			if ((*token)->data[md.i + 1] && !is_meta_char((*token)->data, md.i
					+ 1))
				md.start = md.i + 1;
			else
				md.start = -1;
		}
		if (!(*token)->data[md.i + 1] && md.has_meta && md.start != -1)
			token_append_str(token, md.start, md.i + 1);
		md.i++;
	}
	return (md.has_meta);
}

t_token	*token_get_root(t_token *node)
{
	if (!node)
		return (NULL);
	while (node->prev)
		node = node->prev;
	return (node);
}

bool	token_is_just_meta(t_token **token)
{
	if (!token && !*token && !(*token)->data)
		return (false);
	if ((*token)->data[0] == '>' && (*token)->data[1] == '>'
		&& (*token)->data[2] == '\0')
		(*token)->type = RED_RR;
	else if ((*token)->data[0] == '<' && (*token)->data[1] == '<'
		&& (*token)->data[2] == '\0')
		(*token)->type = RED_LL;
	else if ((*token)->data[0] == '|' && (*token)->data[1] == '\0')
		(*token)->type = PIPE;
	else if ((*token)->data[0] == '<' && (*token)->data[1] == '\0')
		(*token)->type = RED_L;
	else if ((*token)->data[0] == '>' && (*token)->data[1] == '\0')
		(*token)->type = RED_R;
	else
		return (false);
	return (true);
}

t_token	*extract_meta_chars(t_token **root)
{
	t_token	*tmp;
	t_token	*old_node;
	t_token	*last;

	tmp = *root;
	last = tmp;
	while (tmp)
	{
		if (!tmp->next)
			last = tmp;
		if (token_is_just_meta(&tmp))
			tmp = tmp->next;
		else if (token_append_meta(&tmp))
		{
			old_node = tmp;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			if (*root == tmp)
				tmp = tmp->next;
			else
				tmp = tmp->next;
			token_dispose(&old_node);
		}
		else
			tmp = tmp->next;
	}
	return (token_get_root(last));
}

bool	has_syntax_errs(t_token **root)
{
	t_token *tmp;

	tmp = *root;
	int	i = 0;
	while (tmp->prev)
	{
		i++;
		tmp = tmp->prev;
	}
	printf("%d\n",i);
	if (tmp->type == PIPE)
		return (true);
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type != NONE && tmp->prev->type != NONE)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int	main(void)
{
	t_token	*root;
	t_token	*tmp;

	root = separate_prompt_by_space("|'s''a|b'  >>s'' ''\">>c>d\" <<e|f|");
	tmp = root;
	root = extract_meta_chars(&root);
	while (root)
	{
		printf("ARG: %s\nTYPE: %u\n\n", root->data, root->type);
		root = root->next;
	}

	if (has_syntax_errs(&tmp))
	{
		printf("\n***\nsyntax error\n***\n");
	}
	return (0);
}
