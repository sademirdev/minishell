#include "built_in.h"

void	handle_cd(t_built_in *built)
{
	if (!built)
		return ;
}

/*
The chdir function returns an integer value to indicate success or failure.
It returns 0 if the operation is successful, and it returns -1 if it fails, 
with errno set to indicate the error.

cd /home/user/Documents
cd Documents
cd ..
cd .
cd 

*/