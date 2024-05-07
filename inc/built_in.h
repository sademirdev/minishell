# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_built_in_type
{
	NONE,
	CMD,
	ARG,
	PIPE,
	RED_L,
	RED_LL,
	RED_R,
	RED_RR
}					t_built_in_type;

typedef struct s_built_in
{
	char				*data;
	t_built_in_type		type;
	char				*path;
	struct s_built_in	*next;
	struct s_built_in	*previous;
}						t_built_in;
