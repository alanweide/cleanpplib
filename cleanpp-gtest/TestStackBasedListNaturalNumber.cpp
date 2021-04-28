#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <list_impls/stack_based_list.hpp>
#include <natural_number_impls/bounded_nn.hpp>
#include <natural_number_impls/stack_nn.hpp>

using namespace cleanpp;

typedef stack_nn nn_type;
typedef stack_based_list<nn_type> list_nn_type;

TEST(StackBasedListNaturalNumber, InitializerDefTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(StackBasedListNaturalNumber, ClearFromEmptyTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    list->clear();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(StackBasedListNaturalNumber, ClearFromEmptyRemTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    nn_type a(5);
    list->insert(std::move(a));
    
    list->clear();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(StackBasedListNaturalNumber, ClearFromEmptyPrecTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    nn_type a(5);
    list->insert(std::move(a));
    list->retreat();
    
    list->clear();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(StackBasedListNaturalNumber, ClearFromNonEmptyTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    nn_type a(5), b(3);
    list->insert(std::move(a));
    list->insert(std::move(b));
    list->retreat();
    
    list->clear();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(StackBasedListNaturalNumber, IsAtFrontEmptyTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();

    EXPECT_TRUE(list->is_at_front());
}

TEST(StackBasedListNaturalNumber, IsAtEndEmptyTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();

    EXPECT_TRUE(list->is_at_end());
}

TEST(StackBasedListNaturalNumber, IsAtFrontNonemptyTrueTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();

    nn_type a(1);
    list->insert(std::move(a));
    list->retreat();
    
    EXPECT_TRUE(list->is_at_front());
}

TEST(StackBasedListNaturalNumber, IsAtFrontNonemptyFalseTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();

    nn_type a(1);
    list->insert(std::move(a));
    
    EXPECT_TRUE(!list->is_at_front());
}

TEST(StackBasedListNaturalNumber, IsAtEndNonemptyTrueTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();

    nn_type a(1);
    list->insert(std::move(a));
    list->retreat();
    
    EXPECT_TRUE(!list->is_at_end());
}

TEST(StackBasedListNaturalNumber, IsAtEndNonemptyFalseTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();

    nn_type a(1);
    list->insert(std::move(a));
    
    EXPECT_TRUE(list->is_at_end());
}

TEST(StackBasedListNaturalNumber, InsertFromEmptyTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <>)";
    nn_type a_exp;
    
    nn_type a(1);
    
    list->insert(std::move(a));
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(StackBasedListNaturalNumber, InsertFromNonemptyAtEndTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1, 2>, <>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    
    list->insert(std::move(b));
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(StackBasedListNaturalNumber, InsertFromNonemptyAtFrontTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<2>, <1>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    list->retreat();
    
    list->insert(std::move(b));
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(StackBasedListNaturalNumber, InsertNonemptyInMiddleTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1, 3>, <2>)";
    nn_type a_exp, b_exp, c_exp;
    
    nn_type a(1), b(2), c(3);
    list->insert(std::move(a));
    list->insert(std::move(b));
    list->retreat();
    
    list->insert(std::move(c));
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
    EXPECT_TRUE(c == c_exp);
}

TEST(StackBasedListNaturalNumber, RetreatFromEndToFrontTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <1>)";
    nn_type a_exp;
    
    nn_type a(1);
    list->insert(std::move(a));
    
    list->retreat();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(StackBasedListNaturalNumber, RetreatFromMiddleToFrontTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <2, 1>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    list->retreat();
    list->insert(std::move(b));
    
    list->retreat();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(StackBasedListNaturalNumber, RetreatFromEndToMiddleTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <2>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    list->insert(std::move(b));
    
    list->retreat();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(StackBasedListNaturalNumber, RetreatMiddleTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <3, 2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list->insert(std::move(a));
    list->insert(std::move(b));
    list->retreat();
    list->insert(std::move(c));
    
    list->retreat();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
    EXPECT_TRUE(c == c_exp);
}

TEST(StackBasedListNaturalNumber, AdvanceFrontToEndTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <>)";
    nn_type a_exp;
    
    nn_type a(1);
    list->insert(std::move(a));
    list->retreat();
    
    list->advance();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(StackBasedListNaturalNumber, AdvanceFromMiddleToEndTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<2, 1>, <>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    list->retreat();
    list->insert(std::move(b));

    list->advance();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(StackBasedListNaturalNumber, AdvanceFromFrontToMiddleTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <2>)";
    
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    list->insert(std::move(b));
    list->retreat();
    list->retreat();
    
    list->advance();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
}

TEST(StackBasedListNaturalNumber, AdvanceMiddleTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1, 3>, <2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list->insert(std::move(a));
    list->insert(std::move(b));
    list->retreat();
    list->insert(std::move(c));
    list->retreat();
    
    list->advance();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
    EXPECT_TRUE(b == b_exp);
    EXPECT_TRUE(c == c_exp);
}

TEST(StackBasedListNaturalNumber, RemoveToEmptyTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    nn_type a_exp(5);
    
    nn_type a, b(5);
    list->insert(std::move(b));
    list->retreat();
    
    a = list->remove();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(StackBasedListNaturalNumber, RemoveToNonEmptyRemTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <1>)";
    nn_type a_exp(5);
    
    nn_type a, b(5), c(1);
    list->insert(std::move(b));
    list->insert(std::move(c));
    list->retreat();
    list->retreat();
    
    a = list->remove();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(StackBasedListNaturalNumber, RemoveToNonEmptyPrecRemTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <3>)";
    nn_type a_exp(5);
    
    nn_type a, b(5), c(1), d(3);
    list->insert(std::move(c));
    list->insert(std::move(b));
    list->insert(std::move(d));
    list->retreat();
    list->retreat();
    
    a = list->remove();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
    EXPECT_TRUE(a == a_exp);
}

TEST(StackBasedListNaturalNumber, ResetFromEmptyTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    list->reset();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(StackBasedListNaturalNumber, ResetFromEmptyRemTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <4>)";
    
    nn_type a(4);
    list->insert(std::move(a));
    
    list->reset();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(StackBasedListNaturalNumber, ResetFromEmptyPrecTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <4>)";
    
    nn_type a(4);
    list->insert(std::move(a));
    list->retreat();
    
    list->reset();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
}

TEST(StackBasedListNaturalNumber, ResetFromNonEmptyTest) {
    std::unique_ptr<list_impl<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <5, 4>)";
    
    nn_type a(4), b(5);
    list->insert(std::move(a));
    list->retreat();
    list->insert(std::move(b));
    
    list->reset();
    
    std::string list_str = list->to_str();
    EXPECT_TRUE(list_str == expected);
}
