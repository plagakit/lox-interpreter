#include <gtest/gtest.h>

#include "scanner.h"

void compareTokens(const std::vector<Token>& v1, const std::vector<Token>& v2)
{
	ASSERT_EQ(v1.size(), v2.size()) << "Amount of tokens unequal.";
	for (int i = 0; i < v1.size(); i++)
	{
		const Token& a = v1[i];
		const Token& b = v2[i];
		ASSERT_EQ(a.getType(), b.getType()) << "Token A: " << a.toString() << " Token B: " << b.toString();
		ASSERT_EQ(a.getLexeme(), b.getLexeme()) << "Token A: " << a.toString() << " Token B: " << b.toString();
		ASSERT_EQ(a.getLiteral(), b.getLiteral()) << "Token A: " << a.toString() << " Token B: " << b.toString();
		ASSERT_EQ(a.getLine(), b.getLine()) << "Token A: " << a.toString() << " Token B: " << b.toString();
	}
}


TEST(ScannerTest, ScanTokens) {

	Scanner s1 = Scanner("var a = \"balls\";");
	auto tk1 = s1.scanTokens();
	auto cmp1 = {
		Token(VAR, "var", std::monostate(), 1),
		Token(IDENTIFIER, "a", std::monostate(), 1),
		Token(EQUAL, "=", std::monostate(), 1),
		Token(STRING, "\"balls\"", "balls", 1),
		Token(SEMICOLON, ";", std::monostate(), 1),
		Token(END_OF_FILE, "", std::monostate(), 1)
	};
	compareTokens(tk1, cmp1);
}