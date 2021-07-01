#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <stack_impl/linked_stack.hpp>
#include <stack_impl/array_stack.hpp>
#include <stack.hpp>

using namespace cleanpp;

typedef int item_type;
typedef linked_stack<item_type> impl_type;
typedef array_stack<item_type> impl_type2;
typedef stack<item_type> stack_type;

template<class Item>
static std::string stackToString(stack<Item>& s) {
    std::stringstream s_stm;
    s_stm << s;
    std::string s_str = s_stm.str();
    return s_str;
}

TEST(FlexStackInt, InitializerDefTest) {
    stack<item_type> s(impl_type{});
    std::string empty_stack = "<>";
    std::string s_str = stackToString(s);
    EXPECT_TRUE(s_str == empty_stack);
}

TEST(FlexStackInt, IsEmpty_EmptyTest) {
    stack<item_type> s(impl_type{});
    EXPECT_TRUE(s.is_empty());
}

TEST(FlexStackInt, IsEmpty_NonEmptyTest) {
    stack<item_type> s(impl_type{});
    int a(1);
    s.push(std::move(a));
    EXPECT_TRUE(!s.is_empty());
}

TEST(FlexStackInt, IsEmpty_Empty_PushPopTest) {
    stack<item_type> s(impl_type{});
    int a(1), b(2);
    s.push(std::move(a));
    b = s.pop();
    EXPECT_TRUE(s.is_empty());
}

TEST(FlexStackInt, PushToEmptyTest) {
    stack<item_type> s(impl_type{});
    std::string expected_stack = "<1>";

    int a(1);
    s.push(std::move(a));

    std::string s_str = stackToString(s);
    EXPECT_TRUE(s_str == expected_stack);
}

TEST(FlexStackInt, PushToNonEmptyTest) {
    stack<item_type> s(impl_type{});
    std::string expected_stack = "<2, 1>";

    int a(1), b(2);
    s.push(std::move(a));
    s.push(std::move(b));

    std::string s_str = stackToString(s);
    EXPECT_TRUE(s_str == expected_stack);
}

TEST(FlexStackInt, PopEmptyToEmptyTest) {
    stack<item_type> s(impl_type{});
    std::string expected_stack = "<>";
    int expected_a(1);

    int a(1), b(2);
    s.push(std::move(a));
    b = s.pop();

    std::string s_str = stackToString(s);
    EXPECT_TRUE(s_str == expected_stack);
    EXPECT_TRUE(a == expected_a);
}

TEST(FlexStackInt, PopNonEmptyToEmptyTest) {
    stack<item_type> s(impl_type{});
    std::string expected_stack = "<>";
    int expected_b(1);

    int a(1), b(2);
    s.push(std::move(a));
    b = s.pop();

    std::string s_str = stackToString(s);
    EXPECT_TRUE(s_str == expected_stack);
    EXPECT_TRUE(b == expected_b);
}

TEST(FlexStackInt, ClearEmptyTest) {
    stack<item_type> s(impl_type{});
    std::string expected_stack = "<>";

    s.clear();

    std::string s_str = stackToString(s);
    EXPECT_TRUE(s_str == expected_stack);
}

TEST(FlexStackInt, ClearNonemptyTest) {
    stack<item_type> s(impl_type{});
    std::string expected_stack = "<>";
    s.push(1);

    s.clear();

    std::string s_str = stackToString(s);
    EXPECT_TRUE(s_str == expected_stack);
}

TEST(FlexStackInt, AssignEmptyEmptyTest) {
    stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<>", t_exp = "<>";

    s = std::move(t);

    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    EXPECT_TRUE(s_str == s_exp);
    EXPECT_TRUE(t_str == t_exp);
}

TEST(FlexStackInt, AssignEmptyNonemptyTest) {
    stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<>", t_exp = "<>";
    s.push(1);

    s = std::move(t);

    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    EXPECT_TRUE(s_str == s_exp);
    EXPECT_TRUE(t_str == t_exp);
}

TEST(FlexStackInt, AssignNonemptyEmptyTest) {
    stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<1>", t_exp = "<>";
    t.push(1);

    s = std::move(t);

    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    EXPECT_TRUE(s_str == s_exp);
    EXPECT_TRUE(t_str == t_exp);
}

TEST(FlexStackInt, AssignNonemptyNonemptyTest) {
    stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<1>", t_exp = "<>";
    s.push(2);
    t.push(1);

    s = std::move(t);

    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    EXPECT_TRUE(s_str == s_exp);
    EXPECT_TRUE(t_str == t_exp);
}

TEST(FlexStackInt, AssignEmptyEmptyMultiImplTest) {
    stack<item_type> s(impl_type{}), t(impl_type2{});
    std::string s_exp = "<>", t_exp = "<>";

    s = std::move(t);

    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    EXPECT_TRUE(s_str == s_exp);
    EXPECT_TRUE(t_str == t_exp);
}

TEST(FlexStackInt, AssignEmptyNonemptyMultiImplTest) {
    stack<item_type> s(impl_type{}), t(impl_type2{});
    std::string s_exp = "<>", t_exp = "<>";
    s.push(1);

    s = std::move(t);

    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    EXPECT_TRUE(s_str == s_exp);
    EXPECT_TRUE(t_str == t_exp);
}

TEST(FlexStackInt, AssignNonemptyEmptyMultiImplTest) {
    stack<item_type> s(impl_type{}), t(impl_type2{});
    std::string s_exp = "<1>", t_exp = "<>";
    t.push(1);

    s = std::move(t);

    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    EXPECT_TRUE(s_str == s_exp);
    EXPECT_TRUE(t_str == t_exp);
}

TEST(FlexStackInt, AssignNonemptyNonemptyMultiImplTest) {
    stack<item_type> s(impl_type{}), t(impl_type2{});
    std::string s_exp = "<1>", t_exp = "<>";
    s.push(2);
    t.push(1);

    s = std::move(t);

    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    EXPECT_TRUE(s_str == s_exp);
    EXPECT_TRUE(t_str == t_exp);
}

TEST(FlexStackInt, FlipNonEmpty){
    GTEST_SKIP();
    stack<item_type> s(impl_type{});
    std::string s_exp = "<0, 1, 2, 3, 4>";
    int numElem = 5;
    for(int i = 0; i < numElem; i++){
        s.push(std::move(i));
    }

    s.flip();

    std::string s_str = stackToString(s);
    EXPECT_TRUE(s_str == s_exp);
}

TEST(FlexStackInt, FlipEmpty){
    GTEST_SKIP();
    stack<item_type> s(impl_type{});
    std::string s_exp = "<>";

    s.flip();

    std::string s_str = stackToString(s);
    EXPECT_TRUE(s_str == s_exp);
}

TEST(FlexStackInt, FlipBig){
    GTEST_SKIP();
    stack<item_type> s(impl_type{});
    std::string s_exp = "<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>";
    int numElem = 10;
    for(int i = 0; i < numElem; i++){
        s.push(std::move(i));
    }

    s.flip();

    std::string s_str = stackToString(s);
    EXPECT_TRUE(s_str == s_exp);
}
