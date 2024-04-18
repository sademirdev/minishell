#include "../inc/minishell.h"
#include <stdlib.h>

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
  setenv("atat", "fa", 1);
  root = separate_prompt_by_space("a$atat");
  tmp = root;
  root = extract_meta_chars(&root);
  extract_dollar_key_values(&root->data, state);
  while (root) {
    printf("DATA: %s\nTYPE: %u\n\n", root->data, root->type);
    root = root->next;
  }

  // if (has_syntax_errs(&tmp))
  // {
  // 	printf("\n***\nsyntax error\n***\n");
  // }
  return (0);
}
