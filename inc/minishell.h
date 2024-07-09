#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
#include <stdio.h>

# define PATH_MAX 4096

# define SUCCESS 0
# define FAILURE -1
# define HANDLED -2

# define NAFD -2

# define IN_HEREDOC 2
# define AFTER_HEREDOC 3
# define IN_CMD 4
# define AFTER_CMD 5

# define ENO_OTHER 40000

# define ERR_NO_SUCH_FILE_OR_DIR 30002
# define ERR_NUMERIC_ARG_REQUIRED 30003
# define ERR_TOO_MANY_ARG 30004
# define ERR_NOT_A_VALID_IDENTIFIER 30005
# define ERR_PERMISSION_DENIED 30006
# define ERR_PERMISSION_DENIED_BROKEN_PIPE 30007
# define ERR_IS_DIR 30008

# define ERR_HOME_NOT_SET 10001
# define ERR_CMD_NOT_FOUND 10002
# define ERR_CANT_CHANGE_DIR 10003
# define ERRP_NOT_A_VALID_IDENTIFIER 10004
# define ERR_NOT_VALID_IN_THIS_CTX 10005

# define ENDL "\n"
# define ESTR_UNKNOWN "unknown error"
# define ESTR_UNEXPECTED "unexpected error"
# define ESTR_CMD_NOT_FOUND "command not found"
# define ESTR_HOME_NOT_SET "HOME not set"
# define ESTR_CANT_CHANGE_DIR "cannot change directory"
# define ESTR_INVALID_ARG "invalid argument"
# define ESTR_NOT_A_VALID_IDENTIFIER "not a valid identifier"
# define ESTR_NO_SUCH_FILE_OR_DIR "no such file or directory"
# define ESTR_NUMERIC_ARG_REQUIRED "numeric argument required"
# define ESTR_TOO_MANY_ARG "too many arguments"
# define ESTR_PERMISSION_DENIED "permission denied"
# define ESTR_PERMISSION_DENIED_BROKEN_PIPE "permission denied"
# define ESTR_IS_DIR "is a directory"
# define ESTR_NOT_VALID_IN_THIS_CTX "not valid in this context"
# define ESTR_SYN_UNKNOWN_ERR "unknown syntax error"
# define ESTR_SYN_ZERO_PIPE "syntax error near unexpected token `newline'"
# define ESTR_SYN_EMPTY_AFTER "syntax error near unexpected token `newline'"
# define ESTR_SYN_MISS_QUOTE "unexpected quote `'', `\"'"

# define COLOR_RED "\e[0;31m"
# define COLOR_GREEN "\e[0;32m"
# define COLOR_RESET "\e[0m"

# define PROMPT "minishell: "

extern int			g_sig;

typedef struct s_syntax
{
	unsigned char	duplex;
	unsigned char	simplex;
	unsigned char	zero_pipe;
	unsigned char	undefined;
}					t_syntax;

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

typedef struct s_token_sep_md
{
	t_token			**token_arr;
	t_token			*iter;
	t_token			*temp;
	t_token			*temp_root;
	int				i;
}					t_token_sep_md;

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
	int				idx;
	int				count;
	int				bin;
	int				bout;
}					t_cmd;

typedef struct s_handle_cp_arg
{
	int				i;
	int				**fd;
	int				arr_len;
}					t_handle_cp_arg;

void				print_unknown_err(t_state *state);
int					print_exec_err(t_state *state, const t_token *token,
						int status, int err);
void				print_fatal_err(const char *msg, const int err);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *src);
char				*ft_substr(char const *s, int start, int len);
char				*ft_itoa(int n);
char				**ft_split(char const *str, char c);
char				*ft_strjoin(char const *s1, char const *s2, bool flag_free);
int					ft_strlen(const char *s);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, int n);
int					ft_atoi(const char *str);
bool				is_al_underscore(char c);
bool				is_digit(char c);
bool				is_alpha(char c);
bool				is_alnum_underscore(char c);
void				dprint(int fd, const char *s);
void				dprintln(int fd, const char *s);
void				eprint(const char *str);
void				eprintln(const char *str);
char				**str_arr_append(char **str_arr, char *data);
char				**str_arr_remove(char **str_arr, char *key);
t_token				*token_new(char *data, t_token_type type);
t_token				*token_add_last(t_token *token, t_token *new);
void				token_add_prev(t_token **token, t_token *new);
void				token_dispose(t_token **token);
void				token_dispose_all(t_token **token);
t_token				**token_separate_by_pipe(t_token *token);
int					token_append_meta_redr(t_token **token);
int					token_append_meta_redrr(t_token **token);
int					token_append_str(t_token **token, int start, int i);
void				token_append_all(t_token **token, int start, int i,
						t_token_type type);
void				token_append_meta_data_init(t_token_append_meta_data *md,
						t_token **token);
bool				token_append_meta(t_token **token);
t_token				*token_get_root(t_token *node);
bool				token_is_just_meta(t_token **token);
bool				token_sep_md_init(t_token_sep_md *md, t_token *token);
void				token_old_del(t_token **temp, t_token *root);
void				token_insert_dollar_nodes(t_token **token);
int					token_append_meta_pipe(t_token **token);
int					token_append_meta_redl(t_token **token);
int					token_append_meta_redll(t_token **token);
int					token_count_pipe(t_token *token);
void				token_insertion(t_token **token, t_token *temp,
						t_token *sub_nodes);
t_token				**token_separate_by_pipe(t_token *token);
t_token				*token_get_last(t_token *node);
int					token_arr_len(t_token **token_arr);
bool				token_is_built_in(t_token *token);
void				token_arr_dispose(t_token ***token_arr);
void				assign_token_types(t_token *token);
void				assign_token_arr_types(t_token **token_arr);
void				syntax_squote(t_syntax *syntax);
void				syntax_dquote(t_syntax *syntax);
int					syntax_check(t_state *shell);
int					syntax_darrow(t_syntax *syntax, int *i);
int					syntax_sarrow(t_syntax *syntax, int *i);
int					syntax_pipe(t_state *shell, t_syntax *syntax, int *i);
int					env_set_value(t_state *state, char *key_value);
int					env_set_pwd(t_state *state);
char				*env_get_value(t_state *state, const char *key);
int					exec_built_in(t_state *state, t_token *token, t_cmd *cmd, int **pipe_fds);
int					exec_echo(t_state *state, t_token *token, t_cmd *cmd);
int					exec_env(t_state *state, t_cmd *cmd);
int					exec_cd(t_state *state, t_token *token);
int					exec_pwd(t_cmd *cmd, t_state *state);
int					exec_export(t_state *state, t_token *token, t_cmd *cmd);
int					exec_unset(t_state *state, t_token *token);
int					exec_exit(t_state *state, t_token *token);
bool				is_empty_arg(t_token *arg);
int					execute_prompt(t_state *state);
t_token				**run_lexer(t_state *state);
int					create_separated_node(t_token **root, char *prompt,
						int start, int i);
t_token				*separate_prompt_by_space(char *prompt);
int					pass_quoted_str(char *p, int *oi);
t_token_type		get_meta_type(char *data, int i);
bool				is_meta(t_token_type type);
bool				is_meta_char(char *data, int i);
char				get_in_quote(char old, char data);
t_token				*extract_meta_chars(t_token **root);
bool				is_valid_dollar(char *data, int i);
void				handle_dollar(t_token **root, t_state *state);
int					handle_special_dollar(char **data, int start, int i,
						t_state *state);
void				handle_number_dollar(char **data, int start, int i);
int					handle_regular_dollar(char **data, int start, int i,
						t_state *state);
void				handle_unnecessary_quotes(t_token *root);
char				*create_data_from_dollar(char *data, char *value, int start,
						int index);
void				extract_dollar_key_values(char **data, t_state *state,
						bool *has_dollar);
char				*get_dollar_value(char *key, t_state *state);
int					**pipe_fds_init(int pipe_count);
int					set_red_file_fds(t_token *token, t_cmd *cmd,
						t_state *state);
int					set_cmd_arg_and_path(t_token *token, t_state *state,
						t_cmd *cmd, int **pipe_fds);
int					handle_redl(t_token *token, t_cmd *cmd,
						bool has_last_heredoc, t_state *state);
int					handle_redr(t_token *token, t_cmd *cmd, t_state *state);
int					handle_redrr(t_token *token, t_cmd *cmd, t_state *state);
int					handle_redll(t_token *token, t_cmd *cmd, int i);
void				handle_signals(void);
int					set_heredoc_fds(t_token *token, t_cmd *cmd, int i);
bool				cmd_is_str_built_in(t_cmd *cmd);
void				print_syntax_err(int errs, t_state *state);
void				state_dispose(t_state **state);
void				dispose_prompt(t_state *state);
int					pass_data(char *prompt, int *i);
char				**copy_env(char **env);
char				*get_cmd_path(t_token *token, t_state *state);
int					token_count_args(t_token *token);
int					handle_fds(t_token *token, t_cmd *cmd, t_state *state,
						bool has_last_heredoc);
char				**token_to_arg(t_token *token, char *cmd_path);
int					count_unnecessary_quotes(char *data);
bool				is_unnecessary_quote(int *quote, char data);
bool				has_unnecessary_quotes(char *data);
void				t_handle_cp_arg_init(t_handle_cp_arg *arg, int **fd,
						int i);
void				handle_child_process(int **fd, t_state *state,
						t_cmd *cmd, int i);
int					fork_init(t_state *state, t_cmd *cmd, int **fd,
						int arr_len);
int					w_exit_status(int status);
int					exec_single_cmd(t_token *token, t_state *state, t_cmd *cmd);
bool				token_has_cmd(t_token *token);
void				run_executor(t_state *state);
int					cmd_init(t_cmd *cmd, int arr_len);
void				state_dispose_single(t_state **state);
void				cmd_dispose(t_cmd *cmd);
int					**pipe_fds_dispose_idx(int **pipe_fds, int i);
void				built_in_handle_fds(t_cmd *cmd, int **pipe_fds);
void				dispose_paths(char **paths);


void print_debug(const char *tag, const char *message, t_cmd *cmd, int cmd_count, int **fd); // todo: delete this on release
void print_close(const char *func, char *cmd, int i, int j);
#endif
