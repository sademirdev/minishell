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
