#include <stdio.h>
#include "test.h"

uintmax_t runTests(const char *label, struct Test tests[], uintmax_t count)
{
	uintmax_t ran = 0;
	uintmax_t passed = 0;

	if (!tests)
	{
		return 0;
	}

	for (uintmax_t index = 0; index < count; index++)
	{
		bool fail = false;
		const char *file = NULL;
		uintmax_t line = 0;

		struct Test *test = tests + index;

		if (!test)
		{
			continue;
		}

		test->function(&fail, &file, &line);

		if (fail && test->shouldPass)
		{
			printf("FAIL: %s (%s:%ju)\n", test->name, file, line);
		}

		else
		{
			printf("PASS: %s\n", test->name);
			passed++;
		}

		ran++;
	}

	printf("%ju/%ju: %s\n", passed, ran, label);
	return ran - passed;
}
