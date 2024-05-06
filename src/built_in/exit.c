#include "built_in.h"

int64_t	handle_exit(t_built_in *built)
{
	t_built_in	*temp;

	if (!built)
		return (1);
	temp = built;
	if (!is_numeric(temp->next))
	{
		write (1, "exit", 5);
		//free
		//"exit at" bash: exit: at: numeric argument required
		exit(255);
	}
	if (temp->next->next)
	{
		write (1, "exit", 5);
		//free
		//"exit 1 at" bash: exit: too many arguments
		exit(1);
	}
	return (0);
}
/*
- process termination and 
- the least significant byte of status (i.e., status & 0xFF) is
       returned to the parent (see wait(2))
#include <stdlib.h>
*/