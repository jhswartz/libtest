#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <stdint.h>

#define TEST(name) \
	static void test_##name(bool *fail, const char **file, uintmax_t *line)

#define REJECT(expression, ...) \
        if (expression) \
        { \
		*fail = true; \
                *file = __FILE__; \
                *line = __LINE__; \
		{ __VA_ARGS__ ; } \
		if (*fail) \
		{ \
			return; \
		} \
        }

#define EXPECT(expression, ...) REJECT(!(expression), __VA_ARGS__)

#define FAILS false
#define PASSES true

#define VERIFY(name, shouldPass) { #name, test_##name, shouldPass }

struct Test
{
        const char *name;
        void (*function)(bool *fail, const char **file, uintmax_t *line);
	bool shouldPass;
};

uintmax_t runTests(const char *label, struct Test tests[], uintmax_t count);

#endif
