#ifndef TESTING_H
# define TESTING_H
# if defined(__linux__)
	/* Linux. --------------------------------------------------- */
// #  include "./linux.h"
	/* WSL keycodes */
/* #  define W 119
#  define A 97
#  define S 115
#  define D 100 */

# elif defined(__APPLE__)
	/* OSX. --------------------------------------------------- */
/* #  include "./apple.h"
#  define W 13
#  define A 0
#  define S 1
#  define D 2 */

# endif

# ifndef TEST
#  define TEST 0
# endif

#include <stdlib.h>

void	test_main();
# define MURMURTEST if(TEST){test_main();}

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define RESET "\x1B[0m"

# ifndef TEST
#  define TEST 0
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

struct s_tests;

typedef struct s_test
{
	size_t			test_number;
	size_t			test_group_num;

	struct s_tests	*current_test;
	t_list			*fails;
	t_list			*success;
	void			(*ko_msg)(struct s_test *test);
	void			(*ok_msg)(struct s_test *test);

	struct s_tests	**tests;
	void			*my_data;
}				t_test;

struct s_try;

typedef struct s_tests
{
	char			*name;
	int				(*test_fun)(struct s_test *test);

	void			(*ko_msg)(struct s_test *test);
	void			(*ok_msg)(struct s_test *test);

	struct s_try	*trys;
}				t_tests;

typedef struct s_try
{
	void	*try;
	void	*expected;
	void	*result;
	size_t	err_bit;
}				t_try;

typedef struct s_fun
{
	void	*test_fun;
	void	*ko_msg;
	void	*ok_msg;
}				t_fun;

void    init_test(t_test *test, t_try *trys[]);
void	tester(int test_group_num, int test_num, t_test *test);

#endif
