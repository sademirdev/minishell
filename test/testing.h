#ifndef TESTING_H

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>

# define RED	"\x1B[31m"
# define GREEN	"\x1B[32m"
# define RESET	"\x1B[0m"

#define equal_int64(name, desc, actual, expected) { \
	__typeof__(actual)		a = (int64_t) actual; \
	__typeof__(expected)	e = (int64_t) expected; \
	if (a == e) \
	{ \
		printf(GREEN "✔ %s - %s\n" RESET, name, desc); \
	} \
	else \
	{ \
		printf(RED "☓ %s - %s\n\tactual:   %lld\n\texpected: %lld\n" RESET, name, desc, a, e); \
	} \
}

#endif