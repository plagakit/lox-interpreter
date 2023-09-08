#include <gtest/gtest.h>

#include "test_utils.h"

TEST(StatementTest, BlockStmt)
{
	auto s1 = process("{{{{{ print(\"hi\"); }}}}}");
	//auto s2 = process("var i = \"one\"; { var i = \"two\"; print i; } print i;");
	auto s3 = process("var i = 0; { i = 2; } print i;");

	ASSERT_STREQ(s1.c_str(), "hi");
	//ASSERT_STREQ(s2.c_str(), "two\none");
	ASSERT_STREQ(s3.c_str(), "2.000000");
}

TEST(StatementTest, ExpressionStmt)
{
	auto s1 = process("3 + 4;");
	ASSERT_STREQ(s1.c_str(), "");
}

TEST(StatementTest, IfStmt)
{
	auto s1 = process("if (true) print \"yes\";");
	auto s2 = process("if (false) print \"yes\";");
	auto s3 = process("if (3 < 5) print true; else print false;");
	auto s4 = process("if (3 > 5) print true; else print false;");

	ASSERT_STREQ(s1.c_str(), "yes");
	ASSERT_STREQ(s2.c_str(), "");
	ASSERT_STREQ(s3.c_str(), "true");
	ASSERT_STREQ(s4.c_str(), "false");
}

TEST(StatementTest, PrintStmt)
{
	auto s1 = process("print true;");
	ASSERT_STREQ(s1.c_str(), "true");
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
	auto s1 = process("var i = 0; while (i < 3) { print i; i = i + 1; }");
	auto s2 = process("while (false) { print nil; }");

	ASSERT_STREQ(s1.c_str(), "0.000000\n1.000000\n2.000000");
	ASSERT_STREQ(s2.c_str(), "");
}