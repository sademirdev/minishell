#include "built_in.h"
#include <unistd.h>

void	handle_cd(t_built_in *built)
{
	const char	*home_path;
	
	if (!built)
		return ;
	home_path = getenv("HOME"); // maybe define macro for home_path
	while (built)
	{
		if (!built->next)
			if (chdir(home_path) != 0)
				return ;
		if (built->type == ARG)
		{
			if (access(built->data, F_OK) != 0)
				return ;
			if (chdir(built->data) != 0)
				return ;
		}
		if (is_meta(built->type))
		{
			// todo(apancar): handle meta
		}
		built = built->next;
	}
}

/*
The chdir function returns an integer value to indicate success or failure.
It returns 0 if the operation is successful, and it returns -1 if it fails, 
with errno set to indicate the error.

****** cd projects/ aaaa : "change directory but i do not understand where is aaaa" *****
****** cd projects aaa : "bash: cd: projects: No such file or directory"            *****
****** cd /projects/ aaaa : "bash: cd: /projects/: No such file or directory"       *****
cd /home/user/Documents
cd Documents
cd "Documents"
cd ..
cd .
cd 
cd |
cd > >> < <<

*/