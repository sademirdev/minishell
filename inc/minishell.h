#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE -1

# define ERR_FILE_NOT_FOUND 1
# define ERR_FILE_PERMISSION_DENIED 2
# define ERR_FILE_OPEN 3

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
	RED_FILE,
	RED_HEREDOC
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

typedef struct s_token_separation_meta_data
{
	t_token	**token_arr;
	t_token	*iter;
	t_token	*tmp;
	t_token	*tmp_root;
	int64_t	i;
}			t_token_separation_meta_data;

typedef struct s_state
{
	int				status;
	char			**argv;
	char			**env;
}					t_state;

typedef struct s_cmd
{
	char	*cmd;
	char	**argv;
	int		in;
	int		out;
}				t_cmd;

typedef struct s_error
{
	int		errnum;
	char	*message;
	bool	fatal;
}				t_error;

void				handle_redl(t_token *token, t_cmd *cmd);
int64_t			ft_strlen(const char *s);
char				*ft_strdup(const char *src);
char				*ft_substr(char const *s, unsigned int start, int64_t len);
int64_t			ft_strlcpy(char *dst, const char *src, int64_t dst_size);
char				*ft_itoa(int64_t n);
int64_t			pipe_exec(t_token **token_arr, t_state *state);
t_token			*token_new(char *data, t_token_type type);
t_token			*token_add_last(t_token *token, t_token *new);
void				token_add_next(t_token *token, t_token *new);
void				token_add_prev(t_token **token, t_token *new);
void				token_dispose(t_token **token);
void				token_dispose_all(t_token **token);
t_token			**token_separate_by_pipe(t_token *token);

int64_t			create_separated_node(t_token **root, char *prompt,
						int64_t start, int64_t i);
t_token				*separate_prompt_by_space(char *prompt);
int64_t				pass_quoted_str(char *p, int64_t *oi);
t_token_type	get_meta_type(char *data, int64_t i);
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
void				extract_dollar_key_values(char **data, t_state *state, bool *has_dollar);
bool				token_separation_meta_data_init(t_token_separation_meta_data *md, t_token *token);
void	token_old_del(t_token **tmp, t_token *root);
bool	is_valid_dollar(char *data, int64_t i);
bool	is_digit(char c);
bool	is_alpha(char c);
bool	is_alnum_underscore(char c);
void	handle_dollar(t_token **root, t_state *state);
int64_t	handle_special_dollar(char **data, int64_t start, int64_t i,
		t_state *state);
void	handle_number_dollar(char **data, int64_t start, int64_t i);
int64_t	handle_regular_dollar(char **data, int64_t start, int64_t i);
char	*create_data_from_dollar(char *data, char *value, int64_t start,
		int64_t index);
void	extract_dollar_key_values(char **data, t_state *state, bool *has_dollar);
char	*get_dollar_value(char *key);

int64_t	ft_strcmp(char *s1, char *s2);
int64_t					ft_strncmp(const char *s1, const char *s2, int64_t n);
void				token_insert_dollar_nodes(t_token **token);

void				token_dispose(t_token **token);
void				token_dispose_all(t_token **token);
int64_t				token_count_pipe(t_token *token);
t_token				**token_separate_by_pipe(t_token *token);
t_token				*token_get_last(t_token *node);
void	assign_token_types(t_token *token);
void	assign_token_arr_types(t_token **token_arr);

void	error_print(t_error *err);
t_token	**lexer(char *prompt, t_state *state);

void	handle_unnecessary_quotes(t_token *root);
char	**ft_split(char const *str, char c);
int64_t	token_arr_len(t_token **token_arr);
char	*find_path(char *command, char **env);
char	*ft_strjoin(char const *s1, char const *s2, bool flag_free);
char	*token_join_arg_str(t_token *token);
int64_t	fork_init(int (*fd)[2], int64_t arr_len, t_token **token_arr, t_state *state, t_cmd *cmd);
int64_t	pipe_single_exec(t_token *token, t_state *state, t_cmd *cmd);
int64_t	pipe_init(int (*fd)[2], int64_t pipe_count);
void	set_red_file_fds(t_token *token, t_cmd *cmd);
void	set_cmd_arg_and_path(t_token *token, t_state *state, t_cmd	*cmd);
void	handle_redl(t_token	*token, t_cmd *cmd);
void	handle_redr(t_token	*token, t_cmd *cmd);
void	handle_redrr(t_token	*token, t_cmd *cmd);
void	handle_redll(t_token *token, t_cmd *cmd);

void	print_err(const char *file, int err_flag);

#endif
