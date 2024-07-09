#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	**pipe_fds_dispose_idx(int **pipe_fds, int i)
{
	if (!pipe_fds)
		return (NULL);
	if (i < 1)
		return (free(pipe_fds), NULL);
	i--;
	while (i >= 0)
	{
		free(pipe_fds[i]);
		i--;
	}
	free(pipe_fds);
	return (NULL);
}

int	**pipe_fds_init(int pipe_count)
{
	int	**pipe_fds;
	int	i;

	pipe_fds = (int **) malloc(sizeof(int *) * pipe_count);
	if (!pipe_fds)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipe_fds[i] = (int *) malloc(sizeof(int) * 2);
		if (!pipe_fds[i])
			return (pipe_fds_dispose_idx(pipe_fds, i));
		i++;
	}
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipe_fds[i]) == -1)
			return (pipe_fds_dispose_idx(pipe_fds, pipe_count - 1), NULL);
		i++;
	}
	return (pipe_fds);
}
