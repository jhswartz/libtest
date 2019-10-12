# libtest
This is a minimal unit testing library for C. It consists of a test suite runner, named **runTests**, and two macros, named **EXPECT** and **REJECT**, which signal test failure if evaluation of a passed expression does not yield a satisfactory result.


### How do I define and run a suite of tests?
```
#include <test.h>

TEST(TrueIsNotFalse)
{
        REJECT(true == false);
}

TEST(50Minus3Is47)
{
        EXPECT(50 - 3 == 47);
}

TEST(47Minus3Is50)
{
        EXPECT(47 - 3 == 50);
}

int main()
{
        struct Test tests[] =
        {
                VERIFY(TrueIsNotFalse, PASSES),
                VERIFY(50Minus3Is47, PASSES),
                VERIFY(47Minus3Is50, FAILS)
        };

        return runTests("My Tests", tests, sizeof tests / sizeof *tests);
}
```
See **test/test.c** for more.


### How do I compile and link against the library?
```
$ cc -o my-tests my-tests.c -ltest
```


### What is *TEST*?
```
#define TEST(name) \
        static void test_##name(bool *fail, const char **file, uintmax_t *line)
```


### What is *REJECT*?
```
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
```


### What about *EXPECT*?
```
#define EXPECT(expression, ...) REJECT(!(expression), __VA_ARGS__)
```


### What does a Test structure contain?
```
struct Test
{
        const char *name;
        void (*function)(bool *fail, const char **file, uintmax_t *line);
        bool shouldPass;
};
```


### What are *VERIFY*, *PASSES* and *FAILS*?
```
#define FAILS false
#define PASSES true

#define VERIFY(name, shouldPass) { #name, test_##name, shouldPass }
```


### What is *runTests()* and what does it do?
```
uintmax_t runTests(const char *label, struct Test tests[], uintmax_t count);
```

For each of the first **count** elements in the **tests** array: the element's test function is executed and a report, which includes the test result and the name of the test, is written to the standard output stream. After the tests have been performed, a final report is written to the standard output stream that specifies: the number of tests that passed; the number of tests that were ran; and the test suite **label**. Finally, the number of tests that failed is returned to the caller.


### What do the reports look like?
```
PASS: REJECTwhenExpressionIsFalse
PASS: REJECTwhenExpressionIsTrue
PASS: EXPECTwhenExpressionIsTrue
PASS: EXPECTwhenExpressionIsFalse
PASS: REJECTcanExecuteExtraCodeIfTestFails
PASS: EXPECTcanExecuteExtraCodeIfTestFails
PASS: REJECTwillNotExecuteExtraCodeIfTestPasses
PASS: EXPECTwillNotExecuteExtraCodeIfTestPasses
8/8: libtest
```


### How do I prepare a distribution of libtest?
```
$ autoreconf -i
$ ./configure
$ make distcheck
```


### How do I install libtest?
```
$ tar xvf libtest-0.0.tar.gz
$ cd libtest-0.0
$ ./configure
$ make
$ make check
# make install
```
