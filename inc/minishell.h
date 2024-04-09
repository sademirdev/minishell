#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>

typedef enum e_token_type
{
	NONE,
	CMD,
	ARG,
	PIPE,
	RED_L,
	RED_LL,
	RED_R,
	RED_RR
}					t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_token_append_meta_data
{
	t_token_type	type;
	int64_t			in_quote;
	bool			has_meta;
	int64_t			i;
	int64_t			start;
}					t_token_append_meta_data;

int64_t				ft_strlen(const char *s);
char				*ft_strdup(const char *src);
char				*ft_substr(char const *s, unsigned int start, int64_t len);

t_token				*token_new(char *data, t_token_type type);
t_token				*token_add_last(t_token *token, t_token *new);
void				token_add_next(t_token *token, t_token *new);
void				token_add_prev(t_token **token, t_token *new);
void				token_dispose(t_token **token);
void				token_dispose_all(t_token **token);
t_token				**token_separate_by_pipe(t_token *token);

int64_t				create_separated_node(t_token **root, char *prompt,
						int64_t start, int64_t i);
t_token				*separate_prompt_by_space(char *prompt);
int64_t				pass_quoted_str(char *p, int64_t *oi);
t_token_type		get_meta_type(char *data, int64_t i);
void				token_append_meta_pipe(t_token **token);
void				token_append_meta_redl(t_token **token);
void				token_append_meta_redll(t_token **token);
void				token_append_meta_redr(t_token **token);
void				token_append_meta_redrr(t_token **token);
bool				is_meta(t_token_type type);
bool				is_meta_char(char *data, int64_t i);
void				token_append_str(t_token **token, int64_t start, int64_t i);
char				get_in_quote(char old, char data);
void				token_append_all(t_token **token, int64_t start, int64_t i,
						t_token_type type);
void				token_append_meta_data_init(t_token_append_meta_data *md,
						t_token **token);
bool				token_append_meta(t_token **token);
t_token				*token_get_root(t_token *node);
bool				token_is_just_meta(t_token **token);
t_token				*extract_meta_chars(t_token **root);
bool				has_syntax_errs(t_token **root);

int	ft_strncmp(const char *s1, const char *s2, size_t n);

void	token_dispose(t_token **token);
void	token_dispose_all(t_token **token);
int64_t	token_count_pipe(t_token *token);
t_token	**token_separate_by_pipe(t_token *token);

#endif
