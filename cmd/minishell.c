#include "minishell.h"

int	main(void)
{
	t_token	*root;
	t_token	*tmp;

	root = separate_prompt_by_space("a| '' b");
	tmp = root;
	root = extract_meta_chars(&root);
	while (root)
	{
		printf("ARG: %s\nTYPE: %u\n\n", root->data, root->type);
		root = root->next;
	}

	// if (has_syntax_errs(&tmp))
	// {
	// 	printf("\n***\nsyntax error\n***\n");
	// }
	return (0);
}
