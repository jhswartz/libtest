#include <stdbool.h>
#include <test.h>

TEST(REJECTwhenExpressionIsFalse)
{
        REJECT(false);
}

TEST(REJECTwhenExpressionIsTrue)
{
        REJECT(true);
}

TEST(EXPECTwhenExpressionIsTrue)
{
        EXPECT(true);
}

TEST(EXPECTwhenExpressionIsFalse)
{
        EXPECT(false);
}

TEST(REJECTcanExecuteExtraCodeIfTestFails)
{
	bool execution = false;
	REJECT(false != true, *fail = false, execution = true);
	EXPECT(execution);
}

TEST(EXPECTcanExecuteExtraCodeIfTestFails)
{
	bool execution = false;
	EXPECT(false == true, *fail = false, execution = true);
	EXPECT(execution);
}

TEST(REJECTwillNotExecuteExtraCodeIfTestPasses)
{
	bool execution = false;
	EXPECT(true == true, *fail = false, execution = true);
	REJECT(execution);
}

TEST(EXPECTwillNotExecuteExtraCodeIfTestPasses)
{
	bool execution = false;
	EXPECT(false == false, *fail = false, execution = true);
	REJECT(execution);
}

int main()
{
        struct Test tests[] =
        {
                VERIFY(REJECTwhenExpressionIsFalse, PASSES),
		VERIFY(REJECTwhenExpressionIsTrue, FAILS),

                VERIFY(EXPECTwhenExpressionIsTrue, PASSES),
		VERIFY(EXPECTwhenExpressionIsFalse, FAILS),

		VERIFY(REJECTcanExecuteExtraCodeIfTestFails, PASSES),
		VERIFY(EXPECTcanExecuteExtraCodeIfTestFails, PASSES),

		VERIFY(REJECTwillNotExecuteExtraCodeIfTestPasses, PASSES),
		VERIFY(EXPECTwillNotExecuteExtraCodeIfTestPasses, PASSES)
        };

        return runTests("libtest", tests, sizeof tests / sizeof *tests);
}
