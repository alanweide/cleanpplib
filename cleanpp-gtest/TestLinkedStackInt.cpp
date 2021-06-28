#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <stack_impl/linked_stack.hpp>

using namespace cleanpp;

typedef linked_stack<int> stack_type;

static std::string stackNNToString(std::unique_ptr<stack_impl<int>>& s) {
    std::stringstream s_stm;
    s_stm << *s;
    std::string s_str = s_stm.str();
    return s_str;
}

TEST(LinkedStackInt, InitializerDefTest) {
    std::unique_ptr<stack_impl<int>> s = std::make_unique<stack_type>();
    std::string empty_stack = "<>";
    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == empty_stack);
}

TEST(LinkedStackInt, IsEmpty_EmptyTest) {
    std::unique_ptr<stack_impl<int>> s = std::make_unique<stack_type>();
    EXPECT_TRUE(s->is_empty());
}

TEST(LinkedStackInt, IsEmpty_NonEmptyTest) {
    std::unique_ptr<stack_impl<int>> s = std::make_unique<stack_type>();
    int a(1);
    s->push(std::move(a));
    EXPECT_TRUE(!s->is_empty());
}

TEST(LinkedStackInt, IsEmpty_Empty_PushPopTest) {
    std::unique_ptr<stack_impl<int>> s = std::make_unique<stack_type>();
    int a(1), b(2);
    s->push(std::move(a));
    b = s->pop();
    EXPECT_TRUE(s->is_empty());
}

TEST(LinkedStackInt, PushToEmptyTest) {
    std::unique_ptr<stack_impl<int>> s = std::make_unique<stack_type>();
    std::string expected_stack = "<1>";

    int a(1);
    s->push(std::move(a));

    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == expected_stack);
}

TEST(LinkedStackInt, PushToNonEmptyTest) {
    std::unique_ptr<stack_impl<int>> s = std::make_unique<stack_type>();
    std::string expected_stack = "<2, 1>";

    int a(1), b(2);
    s->push(std::move(a));
    s->push(std::move(b));

    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == expected_stack);
}

TEST(LinkedStackInt, PopEmptyToEmptyTest) {
    std::unique_ptr<stack_impl<int>> s = std::make_unique<stack_type>();
    std::string expected_stack = "<>";
    int expected_a(1);

    int a(1), b(2);
    s->push(std::move(a));
    b = s->pop();

    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == expected_stack);
    EXPECT_TRUE(a == expected_a);
}

TEST(LinkedStackInt, PopNonEmptyToEmptyTest) {
    std::unique_ptr<stack_impl<int>> s = std::make_unique<stack_type>();
    std::string expected_stack = "<>";
    int expected_b(1);

    int a(1), b(2);
    s->push(std::move(a));
    b = s->pop();

    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == expected_stack);
    EXPECT_TRUE(b == expected_b);
}

TEST(LinkedStackInt, FlipNonEmptyTest) {
    std::unique_ptr<stack_impl<int>> s = std::make_unique<stack_type>();
    std::string expected_stack = "<0, 1, 2, 3, 4>";
    int numElem = 5;
    for(int i = 0; i < numElem; i++){
        s->push(std::move(i));
    }

    s->flip();

    std::string s_str = stackNNToString(s);
    EXPECT_EQ(s_str, expected_stack);
}