#include "testing.h"
#include "inner.h"

void test_token_new()
{
	typedef struct {
		char			*name;
		char			*desc;
		char			*data;
		t_token_type	type;
		t_token			expected;
	} c;

	c test_cases[] = {
		{
			.name = __FILE__,
			.desc = "return token when success 1",
			.data = "hulya",
			.type = NONE,
			.expected = {
				.data = "hulya",
				.type = NONE,
				.next = NULL,
			},
		},
		{
			.name = __FILE__,
			.desc = "return token when success 2",
			.data = "kizrak 'yigit' $fatih",
			.type = CMD,
			.expected = {
				.data = "kizrak 'yigit' $fatih",
				.type = CMD,
				.next = NULL,
			},
		},
		{
			.name = __FILE__,
			.desc = "return null when data is null",
			.data = NULL,
			.type = CMD,
		},
	};

	int64_t i = 0;
	int64_t size = sizeof test_cases / sizeof(c);
	while (i < size)
	{
		c tc = test_cases[i];
		t_token *actual = token_new(tc.data, tc.type);
		if (!tc.data)
		{
			expect_null(tc.name, tc.desc, actual);
		}
		else
		{
			equal_token(tc.name, tc.desc, actual, &tc.expected);
			free(actual);
		}
		i++;
	}
}

int main(void)
{
	test_token_new();
}
