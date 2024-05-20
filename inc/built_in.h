# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "minishell.h"

enum e_token_type;
typedef struct s_built_in
{
	char				*data;
	enum e_token_type	type;
	char				*path;
	struct s_built_in	*next;
	struct s_built_in	*previous;
}						t_built_in;

int64_t var_exist(char *var);
char	**get_env(char *new_var, char *temp, int64_t i);
int64_t	handle_export(t_built_in *built);
int64_t	handle_echo(t_built_in *built);
int64_t	handle_cd(t_built_in *built);
int64_t	handle_pwd(void);
int64_t	handle_unset(t_built_in *built);
int64_t	handle_env(t_built_in *built);
int64_t	handle_exit(t_built_in *built);
bool	is_built_in(t_built_in *built);
int64_t	handle_built_in(t_built_in *built);

