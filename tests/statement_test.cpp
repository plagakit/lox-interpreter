#include <gtest/gtest.h>

#include "test_utils.h"

TEST(StatementTest, BlockStmt)
{
	auto s1 = process("{{{{{ print(\"hi\"); }}}}}");
	auto s2 = process("var i = \"one\"; { var i = \"two\"; print(i); } print(i);");

	ASSERT_STREQ(s1.c_str(), "hi");
	ASSERT_STREQ(s2.c_str(), "two\none");
}

TEST(StatementTest, ExpressionStmt)
{

}

TEST(StatementTest, IfStmt)
{

}

TEST(StatementTest, PrintStmt)
{

}

TEST(StatementTest, VarStmt)
{
	auto s1 = process("var i = 0; i = 3; print i;");
	auto s2 = process("var i; print i;");

	ASSERT_STREQ(s1.c_str(), "3.000000");
	ASSERT_STREQ(s2.c_str(), "nil");
}

TEST(StatementTest, WhileStmt)
{

}