#include "minishell.h"
#include <stdlib.h>

void	state_dispose(t_state **state)
{
	if (!state || !*state)
		return ;
	free((*state)->env);
	(*state)->env = NULL;
	free((*state)->prompt);
	(*state)->prompt = NULL;
	token_arr_dispose(&(*state)->token_arr);
}

void	dispose_prompt(t_state *state)
{
	if (!state || !state->token_arr)
		return ;
	token_arr_dispose(&state->token_arr);
	free(state->prompt);
	state->prompt = NULL;
}

void	state_dispose_single(t_state **state)
{
	int	i;

	if (!state || !*state)
		return ;
	i = 0;
	while ((*state)->env && (*state)->env[i])
		free((*state)->env[i++]);
	free((*state)->env);
	(*state)->env = NULL;
	free((*state)->prompt);
	(*state)->prompt = NULL;
}
