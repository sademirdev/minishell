#include "../inc/minishell.h"
#include <stdlib.h>

char *_token_type_tostr(t_token_type type) {
  switch (type) {
  case CMD:
    return "CMD";
  case ARG:
    return "ARG";
  case PIPE:
    return "PIPE";
  case RED_L:
    return "RED_L";
  case RED_LL:
    return "RED_LL";
  case RED_R:
    return "RED_R";
  case RED_RR:
    return "RED_RR";
  default:
    return "NONE";
  }
}

int main(int argc, char **argv) {
	extern char **environ;
	t_token *root;
	t_token *tmp;
	t_state *state;

	(void)argc;
	state = malloc(sizeof(t_state));
	if (!state)
	return (1);
	state->argv = argv;
	state->env = environ;
	state->status = 12;
	setenv("l", " l_0 l_1 l_2", 1);
	setenv("nl", "nl_0 nl_1 nl_2", 1);
	setenv("r", "r_0 r_1 r_2 ", 1);
	setenv("nr", "nr_0 nr_1 nr_2", 1);
	setenv("b", " b_0 b_1 b_2 ", 1);
	setenv("nb", "nb_0 nb_1 nb_2", 1);
	root = separate_prompt_by_space("cat '$a' 'pre'$l $r'suf' <'pre'$b'suf' >>'pre'$nl $nr'suf'> | 'pre'$nb'suf'");
	// root = separate_prompt_by_space("$r'a'");
	tmp = root;
	root = extract_meta_chars(&root);
	handle_dollar(&root, state);
	while (root) {
		printf("ptr: %p, DATA: %s\nTYPE: %s\n\n", root, root->data, _token_type_tostr(root->type));
		root = root->next;
	}
	token_dispose_all(&root);

	// if (has_syntax_errs(&tmp))
	// {
	// 	printf("\n***\nsyntax error\n***\n");
	// }
	return (0);
}
