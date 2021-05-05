#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <list_impl/stack_based_list.hpp>
#include <nn_impl/bounded_nn.hpp>
#include <nn_impl/stack_nn.hpp>
#include <list.hpp>

using namespace cleanpp;

typedef stack_nn nn_type;
typedef stack_based_list<nn_type> list_nn_type;

TEST(FlexListNaturalNumber, InitializerDefTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";

    std::string list_str = my_list.to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(FlexListNaturalNumber, ClearFromEmptyTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";

    my_list.clear();

    std::string list_str = my_list.to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(FlexListNaturalNumber, ClearFromEmptyRemTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";

    nn_type a(5);
    my_list.insert(std::move(a));

    my_list.clear();

    std::string list_str = my_list.to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(FlexListNaturalNumber, ClearFromEmptyPrecTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";

    nn_type a(5);
    my_list.insert(std::move(a));
    my_list.retreat();

    my_list.clear();

    std::string list_str = my_list.to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(FlexListNaturalNumber, ClearFromNonEmptyTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";

    nn_type a(5), b(3);
    my_list.insert(std::move(a));
    my_list.insert(std::move(b));
    my_list.retreat();

    my_list.clear();

    std::string list_str = my_list.to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(FlexListNaturalNumber, AssignEmptyEmptyTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    list<nn_type> my_list2(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";

    my_list = std::move(my_list2);

    std::string list_str = my_list.to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(FlexListNaturalNumber, IsAtFrontEmptyTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    EXPECT_TRUE(my_list.is_at_front());
}

TEST(FlexListNaturalNumber, IsAtEndEmptyTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    EXPECT_TRUE(my_list.is_at_end());
}

TEST(FlexListNaturalNumber, IsAtFrontNonemptyTrueTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    nn_type a(1);
    my_list.insert(std::move(a));
    my_list.retreat();

    EXPECT_TRUE(my_list.is_at_front());
}

TEST(FlexListNaturalNumber, IsAtFrontNonemptyFalseTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    nn_type a(1);
    my_list.insert(std::move(a));

    EXPECT_TRUE(!my_list.is_at_front());
}

TEST(FlexListNaturalNumber, IsAtEndNonemptyTrueTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    nn_type a(1);
    my_list.insert(std::move(a));
    my_list.retreat();

    EXPECT_TRUE(!my_list.is_at_end());
}

TEST(FlexListNaturalNumber, IsAtEndNonemptyFalseTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    nn_type a(1);
    my_list.insert(std::move(a));

    EXPECT_TRUE(my_list.is_at_end());
}

TEST(FlexListNaturalNumber, InsertFromEmptyTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<1>, <>)";
    nn_type a_exp;

    nn_type a(1);

    my_list.insert(std::move(a));

    std::string list_str = my_list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(FlexListNaturalNumber, InsertFromNonemptyAtEndTest) {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<1, 2>, <>)";
    nn_type a_exp, b_exp;

    nn_type a(1), b(2);
    my_list.insert(std::move(a));

    my_list.insert(std::move(b));

    std::string list_str = my_list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(FlexListNaturalNumber, InsertFromNonemptyAtFrontTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<2>, <1>)";
    nn_type a_exp, b_exp;

    nn_type a(1), b(2);
    list.insert(std::move(a));
    list.retreat();

    list.insert(std::move(b));

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(FlexListNaturalNumber, InsertNonemptyInMiddleTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<1, 3>, <2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list.insert(std::move(a));
    list.insert(std::move(b));
    list.retreat();

    list.insert(std::move(c));

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
    EXPECT_TRUE(c == c_exp);
}

TEST(FlexListNaturalNumber, RetreatFromEndToFrontTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <1>)";
    nn_type a_exp;

    nn_type a(1);
    list.insert(std::move(a));

    list.retreat();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(FlexListNaturalNumber, RetreatFromMiddleToFrontTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <2, 1>)";
    nn_type a_exp, b_exp;

    nn_type a(1), b(2);
    list.insert(std::move(a));
    list.retreat();
    list.insert(std::move(b));

    list.retreat();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(FlexListNaturalNumber, RetreatFromEndToMiddleTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<1>, <2>)";
    nn_type a_exp, b_exp;

    nn_type a(1), b(2);
    list.insert(std::move(a));
    list.insert(std::move(b));

    list.retreat();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(FlexListNaturalNumber, RetreatMiddleTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<1>, <3, 2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list.insert(std::move(a));
    list.insert(std::move(b));
    list.retreat();
    list.insert(std::move(c));

    list.retreat();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
    EXPECT_TRUE(c == c_exp);
}

TEST(FlexListNaturalNumber, AdvanceFrontToEndTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<1>, <>)";
    nn_type a_exp;

    nn_type a(1);
    list.insert(std::move(a));
    list.retreat();

    list.advance();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(FlexListNaturalNumber, AdvanceFromMiddleToEndTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<2, 1>, <>)";
    nn_type a_exp, b_exp;

    nn_type a(1), b(2);
    list.insert(std::move(a));
    list.retreat();
    list.insert(std::move(b));

    list.advance();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(FlexListNaturalNumber, AdvanceFromFrontToMiddleTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<1>, <2>)";
    nn_type a_exp, b_exp;

    nn_type a(1), b(2);
    list.insert(std::move(a));
    list.insert(std::move(b));
    list.retreat();
    list.retreat();

    list.advance();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(FlexListNaturalNumber, AdvanceMiddleTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<1, 3>, <2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list.insert(std::move(a));
    list.insert(std::move(b));
    list.retreat();
    list.insert(std::move(c));
    list.retreat();

    list.advance();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
    EXPECT_TRUE(c == c_exp);
}

TEST(FlexListNaturalNumber, RemoveToEmptyTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    nn_type a_exp(5);

    nn_type a, b(5);
    list.insert(std::move(b));
    list.retreat();

    a = list.remove();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(FlexListNaturalNumber, RemoveToNonEmptyRemTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <1>)";
    nn_type a_exp(5);

    nn_type a, b(5), c(1);
    list.insert(std::move(b));
    list.insert(std::move(c));
    list.retreat();
    list.retreat();

    a = list.remove();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(FlexListNaturalNumber, RemoveToNonEmptyPrecRemTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<1>, <3>)";
    nn_type a_exp(5);

    nn_type a, b(5), c(1), d(3);
    list.insert(std::move(c));
    list.insert(std::move(b));
    list.insert(std::move(d));
    list.retreat();
    list.retreat();

    a = list.remove();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(FlexListNaturalNumber, ResetFromEmptyTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";

    list.reset();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(FlexListNaturalNumber, ResetFromEmptyRemTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <4>)";

    nn_type a(4);
    list.insert(std::move(a));

    list.reset();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(FlexListNaturalNumber, ResetFromEmptyPrecTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <4>)";

    nn_type a(4);
    list.insert(std::move(a));
    list.retreat();

    list.reset();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(FlexListNaturalNumber, ResetFromNonEmptyTest) {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <5, 4>)";

    nn_type a(4), b(5);
    list.insert(std::move(a));
    list.retreat();
    list.insert(std::move(b));

    list.reset();

    std::string list_str = list.to_str();
    EXPECT_TRUE(list_str == expected);
}
