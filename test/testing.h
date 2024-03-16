#ifndef TESTING_H
#define TESTING_H

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

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

#define expect_null(name, desc, actual) { \
	__typeof__(actual)		a = (t_token *) actual; \
	if (a == NULL) \
	{ \
		printf(GREEN "✔ %s - %s\n" RESET, name, desc); \
	} \
	else \
	{ \
		printf(RED "☓ %s - %s\n\tactual:   %p\n\texpected: %p\n" RESET, name, desc, a, NULL); \
	} \
}

#define equal_token(name, desc, actual, expected) { \
	__typeof__(actual)		a = (t_token *) actual; \
	__typeof__(expected)	e = (t_token *) expected; \
	if (strcmp(a->data, e->data) == 0 && a->type == e-> type) \
	{ \
		printf(GREEN "✔ %s - %s\n" RESET, name, desc); \
	} \
	else \
	{ \
		printf(RED "☓ %s - %s\n" RESET, name, desc); \
		printf(RED "\t actual: {\n\tdata: %s,\n\ttype: %d\n\tnext: %p\n}" RESET, a->data, a->type, a->next); \
		printf(RED "\texpected: {\n\tdata: %s,\n\ttype: %d\n\tnext: %p\n}" RESET, e->data, e->type, e->next); \
	} \
}

#define equal_token_list(name, desc, actual, expected) { \
	__typeof__(actual)		a = (t_token *) actual; \
	__typeof__(expected)	e = (t_token *) expected; \
	t_token	*iter; \
	bool	ok = true; \
	iter = a; \
	while (a->next) \
	{ \
		if (!(strcmp(a->data, e->data) == 0 && a->type == e-> type)) \
		{ \
			printf(RED "☓ %s - %s\n" RESET, name, desc); \
			printf(RED "\t actual:{ ..., {\n\tdata: %s,\n\ttype: %d\n\tnext: %p\n}, ... }" RESET, a->data, a->type, a->next); \
			printf(RED "\texpected:{ ..., {\n\tdata: %s,\n\ttype: %d\n\tnext: %p\n}, ... }" RESET, e->data, e->type, e->next); \
			ok = false; \
		} \
		a = a->next; \
		e = e->next; \
	} \
	if (ok) \
	{ \
		printf(GREEN "✔ %s - %s\n" RESET, name, desc); \
	} \
}

#endif
