// #include "built_in.h"
#include <stdio.h>
#include <stddef.h>

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
}					t_built_in;

static int64_t	ft_strlen(const char *s)
{
	int64_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int64_t	handle_export(t_built_in *built)
{
	int64_t		i;
	int64_t		len;
	char		*var;
	t_built_in	*temp;

	if (!built)
		return (1);
	var = NULL;
	len = ft_strlen(built->data);
	temp = built;
	i = 0;
	while(temp->data[i] != ' ')
		i++;
	while (temp->data[i])
	{
		var = ft_strjoin(var, temp->data[i]);
		i++;
	}
	printf("export %s\n", var);
	return (0);
}

int main()
{
	t_built_in *built;
	built = (t_built_in *)malloc(sizeof(t_built_in));
	built->data = "export a=5";
	handle_export(built);
	return 0;
}

/*
	export a=5
	export a="5"
*/