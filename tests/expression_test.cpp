#include <gtest/gtest.h>

#include "test_utils.h"

TEST(ExpressionTest, AssignExpr) 
{
	auto s1 = process("var i = \"test\"; print i;");
	auto s2 = process("var i; print i = 3;");

	ASSERT_STREQ(s1.c_str(), "test");
	ASSERT_STREQ(s2.c_str(), "3.000000");
}

TEST(ExpressionTest, BinaryExpr) 
{
	auto s1 = process("print 3 + 4;");
	auto s2 = process("print 3 - 4;");
	auto s3 = process("print 3 * 4;");
	auto s4 = process("print 3 / 4;");

	ASSERT_STREQ(s1.c_str(), "7.000000");
	ASSERT_STREQ(s2.c_str(), "-1.000000");
	ASSERT_STREQ(s3.c_str(), "12.000000");
	ASSERT_STREQ(s4.c_str(), "0.750000");
}

TEST(ExpressionTest, GroupingExpr) 
{
	auto s1 = process("print (3 * (4 + 1));");
	ASSERT_STREQ(s1.c_str(), "15.000000");
}


TEST(ExpressionTest, LiteralExpr) 
{
	auto s1 = process("print 3; print \"hi\"; print nil; print true;");
	ASSERT_STREQ(s1.c_str(), "3.000000\nhi\nnil\ntrue");
}

TEST(ExpressionTest, LogicalExpr) 
{
	auto s1 = process("print 3 < 5;");
	auto s2 = process("print 3 > 5;");
	auto s3 = process("print 1 == 1;");
	auto s4 = process("print \"hi\" == \"hi\";");
	auto s5 = process("print 1 + 1 != 2;");
	auto s6 = process("print 4 >= 5;");
	auto s7 = process("print 4 <= 5;");

	ASSERT_STREQ(s1.c_str(), "true");
	ASSERT_STREQ(s2.c_str(), "false");
	ASSERT_STREQ(s3.c_str(), "true");
	ASSERT_STREQ(s4.c_str(), "true");
	ASSERT_STREQ(s5.c_str(), "false");
	ASSERT_STREQ(s6.c_str(), "false");
	ASSERT_STREQ(s7.c_str(), "true");
}

TEST(ExpressionTest, UnaryExpr) 
{
	auto s1 = process("var i = 5; print -i;");
	auto s2 = process("var i = false; print !i;");

	ASSERT_STREQ(s1.c_str(), "-5.000000");
	ASSERT_STREQ(s2.c_str(), "true");
}

TEST(ExpressionTest, VariableExpr) 
{
	auto s1 = process("var i = nil; print i;");
	auto s2 = process("var i = true; var j = i; i = false; print j;");

	ASSERT_STREQ(s1.c_str(), "nil");
	ASSERT_STREQ(s2.c_str(), "true");
}