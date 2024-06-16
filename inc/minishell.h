#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>

# define SUCCESS 0
# define FAILURE -1

# define ERR_FILE_NOT_FOUND 1
# define ERR_FILE_PERMISSION_DENIED 2
# define ERR_FILE_OPEN 3
# define ERR_FILE_NOT_VALID 4
# define ERR_CMD_NOT_FOUND 5


# define PROMPT "minishell: "

typedef struct s_syntax
{
	unsigned char	duplex;
	unsigned char	simplex;
	unsigned char	zero_pipe;
	unsigned char	undefined;
}					t_syntax;

# define UNKNOWN_ERR "shell says: I don't know what you're trying to do\n"
# define ZERO_PIPE \
	"shell says: syntax error near expected non-exist \
token before `|'\n"
# define EMPTY_AFTER \
	"shell says: syntax error near unexpected token after \
`|', `>', `<', `>>', `<<'\n"
# define MISS_QUOTE \
	"shell says: unexpected EOF while looking for matching \
`'', `\"'\n"

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
	int				in_quote;
	bool			has_meta;
	int				i;
	int				start;
}					t_token_append_meta_data;

typedef struct s_token_separation_meta_data
{
	t_token			**token_arr;
	t_token			*iter;
	t_token			*temp;
	t_token			*temp_root;
	int				i;
}					t_token_separation_meta_data;

typedef struct s_state
{
	int				status;
	char			**argv;
	char			**env;
	char			*prompt;
	t_token			**token_arr;
	int				cmd_ct;
	int				err;
}					t_state;

typedef struct s_cmd
{
	char			*cmd;
	char			**argv;
	int				in;
	int				out;
	int				*heredoc;
}					t_cmd;

typedef struct s_error
{
	int				errnum;
	char			*message;
	bool			fatal;
}					t_error;

int					ft_strlen(const char *s);
char				*ft_strdup(const char *src);
char				*ft_substr(char const *s, int start, int len);
int					ft_strlcpy(char *dst, const char *src, int dst_size);
char				*ft_itoa(int n);
int					execute_prompt(t_state *state);
t_token				*token_new(char *data, t_token_type type);
t_token				*token_add_last(t_token *token, t_token *new);
void				token_add_next(t_token *token, t_token *new);
void				token_add_prev(t_token **token, t_token *new);
void				token_dispose(t_token **token);
void				token_dispose_all(t_token **token);
t_token				**token_separate_by_pipe(t_token *token);

int					create_separated_node(t_token **root, char *prompt,
						int start, int i);
t_token				*separate_prompt_by_space(char *prompt);
int					pass_quoted_str(char *p, int *oi);
t_token_type		get_meta_type(char *data, int i);
int					token_append_meta_redr(t_token **token);
int					token_append_meta_redrr(t_token **token);
bool				is_meta(t_token_type type);
bool				is_meta_char(char *data, int i);
int					token_append_str(t_token **token, int start, int i);
char				get_in_quote(char old, char data);
void				token_append_all(t_token **token, int start, int i,
						t_token_type type);
void				token_append_meta_data_init(t_token_append_meta_data *md,
						t_token **token);
bool				token_append_meta(t_token **token);
t_token				*token_get_root(t_token *node);
bool				token_is_just_meta(t_token **token);
t_token				*extract_meta_chars(t_token **root);
bool				has_syntax_errs(t_token **root);
void				extract_dollar_key_values(char **data, t_state *state,
						bool *has_dollar);
bool				token_separation_meta_data_init(t_token_separation_meta_data *md,
						t_token *token);
void				token_old_del(t_token **temp, t_token *root);
bool				is_valid_dollar(char *data, int i);
bool				is_digit(char c);
bool				is_alpha(char c);
bool				is_alnum_underscore(char c);
void				handle_dollar(t_token **root, t_state *state);
int					handle_special_dollar(char **data, int start, int i,
						t_state *state);
void				handle_number_dollar(char **data, int start, int i);
int	handle_regular_dollar(char **data, int start, int i, t_state *state);
char				*create_data_from_dollar(char *data, char *value, int start,
						int index);
void				extract_dollar_key_values(char **data, t_state *state,
						bool *has_dollar);
char				*get_dollar_value(char *key, t_state *state);


int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, int n);
void				token_insert_dollar_nodes(t_token **token);
int					token_append_meta_pipe(t_token **token);
int					token_append_meta_redl(t_token **token);
int					token_append_meta_redll(t_token **token);
void				token_dispose(t_token **token);
void				token_dispose_all(t_token **token);
int					token_count_pipe(t_token *token);
t_token				**token_separate_by_pipe(t_token *token);
t_token				*token_get_last(t_token *node);
void				assign_token_types(t_token *token);
void				assign_token_arr_types(t_token **token_arr);

void				error_print(t_error *err);
t_token				**run_lexer(t_state *state);

void				handle_unnecessary_quotes(t_token *root);
char				**ft_split(char const *str, char c);
int					token_arr_len(t_token **token_arr);
char				*find_path(char *command, char **env);
char				*ft_strjoin(char const *s1, char const *s2, bool flag_free);
char				*token_join_arg_str(t_token *token);
int					fork_init(int (*fd)[2], int arr_len, t_token **token_arr,
						t_state *state, t_cmd *cmd);
int					pipe_single_exec(t_token *token, t_state *state,
						t_cmd *cmd);
int					pipe_init(int (*fd)[2], int pipe_count);
int					set_red_file_fds(t_token *token, t_cmd *cmd, t_state *state);
void				set_cmd_arg_and_path(t_token *token, t_state *state,
						t_cmd *cmd);
int					handle_redl(t_token *token, t_cmd *cmd,
						bool has_last_heredoc, t_state *state);
int					handle_redr(t_token *token, t_cmd *cmd, t_state *state);
int					handle_redrr(t_token *token, t_cmd *cmd, t_state *state);
int					handle_redll(t_token *token, t_cmd *cmd, int i);

void				print_err(const char *file, int err_flag);
void				set_heredoc_fds(t_token *token, t_cmd *cmd, int i);
void				handle_signals(void);

int					handle_built_in(t_token *token, t_state *state, t_cmd *cmd);
bool				is_built_in(t_token *token);
int					handle_unset(t_token *token, t_state *state);
int					handle_pwd(void);
int					handle_export(t_token *token, t_state *state, t_cmd *cmd);
char				**get_env(char *new_var, char *temp, int i, t_state *state);
int					handle_exit(t_token *token, t_state *state);
int					handle_env(t_token *token, t_state *state, t_cmd *cmd);
int					handle_echo(t_token *token, t_state *state, t_cmd *cmd);
int					handle_cd(t_token *token, t_state *state);
int					syntax_check(t_state *shell);
void				syntax_squote(t_syntax *syntax);
int					syntax_darrow(t_syntax *syntax, int *i);
void				syntax_dquote(t_syntax *syntax);
int					syntax_sarrow(t_syntax *syntax, int *i);
int					syntax_pipe(t_state *shell, t_syntax *syntax, int *i);
void				print_syntax_err(int errs);
void				token_arr_dispose(t_token ***token_arr);
void				state_dispose(t_state **state);
void				dispose_prompt(t_state *state);
int					pass_data(char *prompt, int *i);
char				**copy_env(char **env);
int					has_equal(char *str);

#endif
