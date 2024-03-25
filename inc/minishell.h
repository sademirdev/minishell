#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>


typedef enum e_token_type
{
	NONE,
	CMD,
	ARG,
	PIPE,
	RED_L,
	RED_LL,
	RED_R,
	RED_RR,
	INIT
}	t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

int64_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, int64_t len);

t_token	*token_new(char *data, t_token_type type);
void	token_add(t_token *root, t_token *new);
void	token_dispose(t_token **root);

t_token	*separate_prompt_by_space(t_token **tokens, char *prompt);

#endif
