
#include "gtest/gtest.h"
#include "Regexp.h"

TEST(RegexpTest, EmptyStr) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrQuestionMark) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("?");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrAsterisk) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrSymbol) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("a");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrDoubleQuestionMark) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("??");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrDoubleAsterisk) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("**");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrDoubleSymbol) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("aa");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrQuestionMarkAsterisk) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("?*");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrAsteriskQuestionMark) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*?");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrAsteriskSymbol) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*a");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrSymbolAsterisk) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("a*");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrQuestionMarkSymbol) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("?a");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, EmptyStrSymbolQuestionMark) {
    std::string name;
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("a?");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolSymbol) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("a");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolWrongSymbol) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("b");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolQuestionMark) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("?");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolAsterisk) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolDoubleSymbol) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("aa");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolDoubleAsterisk) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("**");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolDoubleQuestionMark) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("??");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolAsteriskQuestionMark) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*?");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolQuestionMarkAsterisk) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("?*");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolSymbolAsterisk) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("a*");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolAsteriskSymbol) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*a");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolQuestionMarkSymbol) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("?a");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, SymbolSymbolQuestionMark) {
    std::string name = "a";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("a?");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolDoubleSymbol) {
    std::string name = "aa";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("aa");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolSymbol) {
    std::string name = "aa";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("a");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolTripleSymbol) {
    std::string name = "aa";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("aaa");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolWrongDoubleSymbol) {
    std::string name = "aa";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("bb");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolAsterisk) {
    std::string name = "aa";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*");
    EXPECT_TRUE(regexp.search(nfa, name));
}
TEST(RegexpTest, DoubleSymbolDoubleAsterisk) {
    std::string name = "aa";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("**");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolTripleAsterisk) {
    std::string name = "aa";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("***");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolQuestionMark) {
    std::string name = "aa";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("?");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolDoubleQuestionMark) {
    std::string name = "aa";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("??");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolTripleQuestionMark) {
    std::string name = "aa";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("???");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolAsteriskSymbol) {
    std::string name = "ab";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*b");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolSymbolAsterisk) {
    std::string name = "ab";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("a*");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolSymbolQuestionMark) {
    std::string name = "ab";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("a?");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolQuestionMarkSymbol) {
    std::string name = "ab";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("?b");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolQuestionMarkAsterisk) {
    std::string name = "ab";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("?*");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolAsteriskQuestionMark) {
    std::string name = "ab";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*?");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, DoubleSymbolAsteriskQuestionMarkAsterisk) {
    std::string name = "ab";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*?*");
    EXPECT_FALSE(regexp.search(nfa, name));
}

TEST(RegexpTest, AsteriskWordAsterisk) {
    std::string name = "11111Some22222";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*Some*");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, AsteriskWord) {
    std::string name = "11111Some";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*Some");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, WordAsterisk) {
    std::string name = "Some22222";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("Some*");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, WordWithAsterisks) {
    std::string name = "11111Some22222";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*****Some***");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, AsteriskAnotherWordAsterisks) {
    std::string name = "11111abc22222";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("*abc*");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, AnotherWordAsterisk) {
    std::string name = "abc22222";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("abc*");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, WordQuestionMark) {
    std::string name = "abc2";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("abc?");
    EXPECT_TRUE(regexp.search(nfa, name));
}

TEST(RegexpTest, WordWord) {
    std::string name = "abc";
    Regexp regexp = Regexp();
    NFA_t nfa = regexp.toNFA("abc");
    EXPECT_TRUE(regexp.search(nfa, name));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
