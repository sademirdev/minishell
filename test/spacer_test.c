#include "testing.h"
#include "inner.h"

void test_pass_quoted_str()
{
	typedef struct {
		char	*name;
		char	*desc;
		char	*prompt;
		int64_t	oi;
		int64_t	expected_rsp;
		char	expected_index;
	} c;

	c testCases[] = {
		{
			.name = __FILE__,
			.desc = "return 0 when success",
			.prompt = "at adam'a 'bbb",
			.oi = 7,
			.expected_rsp = 0,
			.expected_index = 11,
		},
		{
			.name = __FILE__,
			.desc = "do nothing and return 0",
			.prompt = "a",
			.oi = 0,
			.expected_rsp = 0,
			.expected_index = 0,
		},
		{
			.name = __FILE__,
			.desc = "return -42 when the (') quote not closed",
			.prompt = "'",
			.oi = 0,
			.expected_rsp = -42,
			.expected_index = 1,
		},
		{
			.name = __FILE__,
			.desc = "return -42 when the (\") quote not closed",
			.prompt = "\"",
			.oi = 0,
			.expected_rsp = -42,
			.expected_index = 1,
		},
	};

	int64_t i = 0;
	int64_t size = sizeof testCases / sizeof(c);
	while (i < size)
	{
		c tc = testCases[i];
		int64_t actual = pass_quoted_str(tc.prompt, &tc.oi);
		equal_int64(tc.name, tc.desc, actual, tc.expected_rsp);
		equal_int64(tc.name, tc.desc, tc.oi, (int64_t) tc.expected_index);
		i++;
	}
}

void test_separated_list_len()
{
	typedef struct {
		char	*name;
		char	*desc;
		char	*prompt;
		int64_t	expected;
	} c;

	c testCases[] = {
		{
			.name = __FILE__,
			.desc = "return len when success 1",
			.prompt = "at adam'a 'bbb",
			.expected = 2,
		},
		{
			.name = __FILE__,
			.desc = "return len when success 2",
			.prompt = " 'a 'b 'aa ''bb'a'b' a ''",
			.expected = 4,
		},
		{
			.name = __FILE__,
			.desc = "return len when success 3",
			.prompt = "''''''''''a'' ''a '' aa'' a's' ",
			.expected = 5,
		},
		{
			.name = __FILE__,
			.desc = "return len when success 4",
			.prompt = "' a\"'\"\" \" bc\" \"'''\"",
			.expected = 3,
		},
		{
			.name = __FILE__,
			.desc = "return len when quote not closed",
			.prompt = "' a\"'\"\" \" bc\" \"'''",
			.expected = -42,
		},
	};

	int64_t i = 0;
	int64_t size = sizeof testCases / sizeof(c);
	while (i < size)
	{
		c tc = testCases[i];
		int64_t actual = separated_list_len(tc.prompt);
		equal_int64(tc.name, tc.desc, actual, tc.expected);
		i++;
	}
}

int main(void)
{
	test_pass_quoted_str();
	test_separated_list_len();
}
