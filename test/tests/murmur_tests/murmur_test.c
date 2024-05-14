#include "murmur_test/incs/testing.h"
#include "minishell.h"
#include <string.h>

# define UNDEFINED(res)	((res & (0xff << 24)) >> 24)
# define ZEROPIPE(res)	((res & (0xff << 16)) >> 16)
# define SIMPLEX(res)	((res & (0xff << 8)) >> 8)
# define DUPLEX(res)	((res & (0xff << 0)) >> 0)

int	ft_lstsize(t_list *lst);

// t_list	*ll_nod(t_list *node, int index)
// {
// 	if (index < 0)
// 		return (0);
// 	while (index-- > 0 && node->next)
// 		node = node->next;
// 	if (index > -1)
// 		return (0);
// 	return (node);
// }

// void	lliter(t_list *lst, void (*f)(void *, void *), void *p)
// {
// 	if (!f)
// 		return ;
// 	while (lst)
// 	{
// 		(*f)(lst->content, p);
// 		lst = lst->next;
// 	}
// }

// void	list_cmds(t_main *data)
// {
// 	for (size_t i = 0; i < (data)->cmd_ct; i++)
// 	{
// 		t_list		*arg = (data)->cmds[i].args;
// 		printf("> path: %s\n", (data)->cmds[i].cmd);
// 		for (size_t i = 0; arg; i++)
// 		{
// 			printf(">  arg[%zu]: %s\n", i, (char *)arg->content);
// 			arg = arg->next;
// 		}
// 		printf("> in: %i\n", data->cmds[i].in);
// 		printf("> out: %i\n", data->cmds[i].out);
// 	}
// }

// t_list	*ll_nod(t_list *node, int index);

int		syntax_check_test(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	((t_state *)(test->my_data))->cmd_ct = 0;
	((t_state *)(test->my_data))->promt = strdup(try->try);
	try->result = syntax_check(test->my_data);
	free(((t_state *)(test->my_data))->promt);
	try->err_bit = try->result;
	return !try->result;
}

void	syntax_check_test_ko(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	char    *result[2] = {GREEN"[OK]"RESET, RED"[KO]"RESET};
	printf("================ %s ================\n", test->current_test->name);
    printf("try		[ %s ]\n\n", (char *)try->try);

	int bits = 64;
	while(bits--)
	{
		printf("%i", ((size_t)try->result >> bits) & 1);
		if (bits % 8 == 0)
			printf(" ");
	}
	printf("\n\n");
	if (DUPLEX(try->err_bit))
		printf(YELLOW"your			[ %d ]\n"RESET, DUPLEX((size_t)try->result));
	printf("expected DUPLEX		[ %d ]\n\n", DUPLEX((size_t)try->expected));
	if (SIMPLEX(try->err_bit))
		printf(YELLOW"your			[ %d ]\n"RESET, SIMPLEX((size_t)try->result));
	printf("expected SIMPLEX	[ %d ]\n\n", SIMPLEX((size_t)try->expected));
	if (ZEROPIPE(try->err_bit))
		printf(YELLOW"your			[ %d ]\n"RESET, ZEROPIPE((size_t)try->result));
	printf("expected ZEROPIPE	[ %d ]\n\n", ZEROPIPE((size_t)try->expected));
	if (UNDEFINED(try->err_bit))
		printf(YELLOW"your			[ %d ]\n"RESET, UNDEFINED((size_t)try->result));
	printf("expected UNDEFINED	[ %d ]\n\n", UNDEFINED((size_t)try->expected));

	printf("^^^^^^^^=========TEST %zu=%s================\n\n\n", test->test_number, result[1]);
}

void	syntax_check_test_ok(t_test *test)
{
	t_try	*try;

	try = test->current_test->trys;
	char    *result[2] = {GREEN"[OK]"RESET, RED"[KO]"RESET};
	printf("=============== %s ================\n", test->current_test->name);
    printf("try         	[ %s ]\n", (char *)try->try);
	printf("expected	[ %zu ]\n", (size_t)try->expected);
	printf("=================TEST %zu=%s================\n\n\n", test->test_number, result[0]);
}

void	*get_my_data(void)
{
	t_state *shell = malloc(sizeof(t_state[1]));
	return (shell);
}

// void	print_tlist(t_list *head)
// {
// 	printf(">  [\n");
// 	a:
// 	printf(">  node: %s\n", (char *)head->content);
// 	head = head->next;
// 	if (head)
// 		goto a;
// 	printf(">  ]\n");
// }

void	test_main()
{
	// printf("%s: %s\n", __func__, turn.buffer);

	// test for syntax_check(): duplex and simplex must be 0 when it should be.
	// test for parser(): must give correct out.

    // create test struct
	t_test	test;
	test.my_data = get_my_data();


    // ============================= EXECUTER =============================
	// ((t_main *)test.my_data)->cmds = (t_cmd []){
	// 	{
	// 		.cmd = ft_strdup("/usr/bin/ls"),
	// 		.args = (char *[]){"", "-la", "-s", "/home/mehmetap/sources/repos/projects/main/murmursh-copyxd", NULL},
	// 		.in = 0, .out = 1,
	// 		// .path = NULL
	// 	},
	// 	{
	// 		.cmd = ft_strdup("grep"),
	// 		.args = (char *[]){"", "\\-rw-r--r--", NULL},
	// 		.in = 0, .out = 1,
	// 		// .path = NULL
	// 	},
	// 	{
	// 		.cmd = ft_strdup("cut"),
	// 		.args = (char *[]){"", "-b", "57-", NULL},
	// 		.in = 0, .out = 1,
	// 		// .path = NULL
	// 	},
	// 	{
	// 		.cmd = ft_strdup("/usr/bin/cat"),
	// 		.args = (char *[]){"", NULL},
	// 		.in = 0, .out = 1,
	// 		// .path = NULL
	// 	},
	// 	{
	// 		.cmd = ft_strdup("wc"),
	// 		.args = (char *[]){"", "-l", NULL},
	// 		.in = 0, .out = 1,
	// 		// .path = NULL
	// 	},
	// };
	// set_path(test.my_data);
	// for (size_t i = 0; i < ((t_main *)test.my_data)->cmd_ct; i++)
	// {
	// 	printf("path: %s\n", ((t_main *)test.my_data)->cmds[i].cmd);
	// }
	// exe_cute_cat(test.my_data);


    // ============================= STRING =============================
	t_try	*trys[] =
	{
        (t_try [])
        {
            {
				.try = &(t_fun){syntax_check_test, syntax_check_test_ko, syntax_check_test_ok},
				.expected = "syntax check test",
			},
			{
				.try = ">ls<ls ls|cat|cat>>cat<<cat$?",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = "ls -l|cat|cat|ls",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = ">cat|cat|ls",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = "><echo>a|ls",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = ">ls>ls>ls ls|cat|cat>>cat$?",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = ">ls<ls<ls|cat|ls|cat",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = "ls -l|wc -l|ls<<ls|cat",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = "<<ls<<ls>>ls>>ls<<ls|cat|cat",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = "ls<ls>ls>ls<ls<ls<ls>ls|ls|ls",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = "$?|cat|cat|ls|ls|",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = ">echo ls|ls|ls<<ls",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
			{
				.try = ">>echo<<ls<<ls<<ls|cat|cat<<cat<cat>>ls>>ls>ls",
				.expected = 0b0000000000000000000000000000000000000000000000000000000000000000l,
			},
            {
				.try = NULL,
				.expected = NULL,
			}
        },

		NULL,
	};

    // initialize test
    init_test(&test, trys);

    // call each tests in test groups
    for (size_t j = 0; (size_t)trys[j]; j++)
    {
        for (size_t i = 0; (size_t)trys[j][i + 1].try; i++)
            tester(j, i, &test);
    }
	printf("fails: %i\n", ft_lstsize(test.fails));

	// index kayiyo 1 tane aradan cikardinmi. index kayarsa kodun degismesi
	// gerekir. test caselerinin sayisina bagli olmamalidir kod.
    exit(0);
}