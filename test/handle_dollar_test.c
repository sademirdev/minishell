#include "murmur_eval.h"
// #include "minishell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	test_main();

int main(void)
{
	MURMURTEST
}


#include "libs/tin/testing.h"

static int		ft_lstsize(struct s_link_list *lst);

void	*get_my_data(void)
{
	t_state *state = calloc(1, sizeof(t_state));
	return (state);
}

int		test_handle_dollar(t_test *test);
void	test_handle_dollar_ko(t_test *test);
void	test_handle_dollar_ok(t_test *test);

int		test_native_handle_dollar(t_test *test);
void	test_native_handle_dollar_ko(t_test *test);
void	test_native_handle_dollar_ok(t_test *test);

void	test_main()
{
  NEW_TEST_RUNNER(1)
	GET_TEST_RUNNER(1).my_data = get_my_data();

	NEW_TEST(1)
		NEW_GROUP("handle_dollar_test", test_handle_dollar, test_handle_dollar_ko, test_handle_dollar_ok)
			{
				CASE = &(t_token *[]){
					&(t_token){.data = strdup("$a"), .type = NONE},
					&(t_token){.data = strdup("$b"), .type = NONE},
					NULL
				},
				EXPECTED = (char *[]){"000", "AAAA"}
			},
		END_GROUP
		NEW_GROUP("native_handle_dollar_test", test_native_handle_dollar, test_native_handle_dollar_ko, test_native_handle_dollar_ok)
			{
				CASE = "$a $b",
				EXPECTED = &(t_token *[]){
					&(t_token){.data = strdup("000"), .type = NONE},
					&(t_token){.data = strdup("AAAA"), .type = NONE},
					NULL
				},
			},
			{
				CASE = "$a $b$c$b",
				EXPECTED = &(t_token *[]){
					&(t_token){.data = strdup("000"), .type = NONE},
					&(t_token){.data = strdup("AAAA"), .type = NONE},
					NULL
				},
			},
		END_GROUP
  END_TEST

	EVAL_INIT(GET_TEST_RUNNER(1), GET_TEST(1))

	EVAL_ALL(GET_TEST_RUNNER(1), GET_TEST(1))

	// EVAL_GROUP(GET_TEST_RUNNER(1), GET_TEST(1), 0)

	// EVAL_TEST(GET_TEST_RUNNER(1), 0, 0)

	EVAL_FAILS(GET_TEST_RUNNER(1))

}

int		test_native_handle_dollar(t_test *test)
{
	extern char **environ;
	setenv("a", "0000", 1);
	setenv("b", "AAAA", 1);
	setenv("c", "xx xx", 1);
	((t_state *)(test->my_data))->env = environ;
	t_token *root = NULL;
	t_token *exp = NULL;

	root = separate_prompt_by_space(CURR_TEST(test)->try);
	root = extract_meta_chars(&root);
	handle_dollar(&root, test->my_data);
	for (size_t i = 0; ((t_token **)CURR_TEST(test)->expected)[i] ; i++)
		exp = token_add_last(exp, token_new(strdup(((t_token **)CURR_TEST(test)->expected)[i]->data), ((t_token **)CURR_TEST(test)->expected)[i]->type));
	CURR_TEST(test)->expected = exp;
	CURR_TEST(test)->result = root;
	if (!equal_token_arr(root, CURR_TEST(test)->expected))
		return (0);
	return (1);
}
void	test_native_handle_dollar_ko(t_test *test)
{
	printf("=============== %s ============\n", test->current_test->name);
	printf("try		[ `%s` ]\n", (CURR_TEST(test)->try));
	p_diff_token_list(test->current_test->name, CURR_TEST(test)->result, CURR_TEST(test)->expected);
	// printf(YELLOW"your		[ %s ]\n"RESET, ((t_token *)(CURR_TEST(test)->result))->data );
	// printf("expected	[ %s ]\n", ((char **)(CURR_TEST(test)->expected))[CURR_TEST(test)->err_bit]);
	printf("^^^^^^^^=========TEST %zu=%s================\n\n\n", test->test_number, __result_eval[1]);
}

void	test_native_handle_dollar_ok(t_test *test)
{
	printf("=============== %s ================\n", test->current_test->name);
    printf("try         	[ %s ]\n", ((t_token **)CURR_TEST(test)->try)[CURR_TEST(test)->err_bit]->data);
    // printf(GREEN"expected	[ %s ]\n"RESET, ((char **)(CURR_TEST(test)->expected))[CURR_TEST(test)->err_bit]);
	printf("=================TEST %zu=%s================\n\n\n", test->test_number, __result_eval[0]);
}







int		test_handle_dollar(t_test *test)
{
	extern char **environ;
	setenv("a", "0000", 1);
	setenv("b", "AAAA", 1);
	((t_state *)(test->my_data))->env = environ;
	t_token *root = NULL;
	for (size_t i = 0; ((t_token **)CURR_TEST(test)->try)[i] ; i++)
		root = token_add_last(root, token_new(strdup(((t_token **)CURR_TEST(test)->try)[i]->data), ((t_token **)CURR_TEST(test)->try)[i]->type));
	handle_dollar(&root, test->my_data);
	CURR_TEST(test)->result = root;
	int at = 0;
	for (t_token *iter = root; iter; iter = iter->next)
	{
		if (strcmp(iter->data, ((char **)CURR_TEST(test)->expected)[at]))
		{
			CURR_TEST(test)->err_bit = at;
			return (0);
		}
		at++;
	}
	return (1);
}
void	test_handle_dollar_ko(t_test *test)
{
	printf("=============== %s ============\n", test->current_test->name);
	printf("node %zu\n\n", CURR_TEST(test)->err_bit);
	printf("try		[ %s ]\n", ((t_token **)CURR_TEST(test)->try)[CURR_TEST(test)->err_bit]->data);

	// go_node()
	for (size_t i = 0; i < CURR_TEST(test)->err_bit; i++)
	{
		CURR_TEST(test)->result = ((t_token *)(CURR_TEST(test)->result))->next;
	}

	printf(YELLOW"your		[ %s ]\n"RESET, ((t_token *)(CURR_TEST(test)->result))->data );
	printf("expected	[ %s ]\n", ((char **)(CURR_TEST(test)->expected))[CURR_TEST(test)->err_bit]);
	printf("^^^^^^^^=========TEST %zu=%s================\n\n\n", test->test_number, __result_eval[1]);
}

void	test_handle_dollar_ok(t_test *test)
{
	printf("=============== %s ================\n", test->current_test->name);
    printf("try         	[ %s ]\n", ((t_token **)CURR_TEST(test)->try)[CURR_TEST(test)->err_bit]->data);
    printf(GREEN"expected	[ %s ]\n"RESET, ((char **)(CURR_TEST(test)->expected))[CURR_TEST(test)->err_bit]);
	printf("=================TEST %zu=%s================\n\n\n", test->test_number, __result_eval[0]);
}



static int	ft_lstsize(struct s_link_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
