#include <gtest/gtest.h>

#include "scanner.h"

void compareTokens(const std::vector<Token>& v1, const std::vector<Token>& v2)
{
	ASSERT_EQ(v1.size(), v2.size()) << "Amount of tokens unequal.";
	for (int i = 0; i < v1.size(); i++)
	{
		const Token& a = v1[i];
		const Token& b = v2[i];

		ASSERT_EQ(a.getType(), b.getType());
		ASSERT_EQ(a.getLexeme(), b.getLexeme());

		if (a.getType() == NUMBER)
			ASSERT_DOUBLE_EQ(std::get<double>(a.getLiteral()), std::get<double>(b.getLiteral()));
		else
			ASSERT_EQ(a.getLiteral(), b.getLiteral());

		ASSERT_EQ(a.getLine(), b.getLine());
	}
}


TEST(ScannerTest, GeneralTest) {
	Scanner s = Scanner("var a = \"balls\";");
	auto tks = s.scanTokens();
	auto cmp = {
		Token(VAR, "var", std::monostate(), 1),
		Token(IDENTIFIER, "a", std::monostate(), 1),
		Token(EQUAL, "=", std::monostate(), 1),
		Token(STRING, "\"balls\"", "balls", 1),
		Token(SEMICOLON, ";", std::monostate(), 1),
		Token(END_OF_FILE, "", std::monostate(), 1)
	};
	compareTokens(tks, cmp);
}

TEST(ScannerTest, LineNoTest) {
	Scanner s = Scanner("a\n\n\n\na\na");
	auto tks = s.scanTokens();
	auto cmp = {
		Token(IDENTIFIER, "a", std::monostate(), 1),
		Token(IDENTIFIER, "a", std::monostate(), 5),
		Token(IDENTIFIER, "a", std::monostate(), 6),
		Token(END_OF_FILE, "", std::monostate(), 6)
	};
	compareTokens(tks, cmp);
}

TEST(ScannerTest, ValueTest) {
	Scanner s = Scanner("\"string\" 1.0 true false nil");
	auto tks = s.scanTokens();
	auto cmp = {
		Token(STRING, "\"string\"", "string", 1),
		Token(NUMBER, "1.0", 1.0, 1),
		Token(TRUE, "true", true, 1),
		Token(FALSE, "false", false, 1),
		Token(NIL, "nil", std::monostate(), 1),
		Token(END_OF_FILE, "", std::monostate(), 1)
	};
	compareTokens(tks, cmp);
}