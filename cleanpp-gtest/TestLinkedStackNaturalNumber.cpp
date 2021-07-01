#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <stack_impl/linked_stack.hpp>
#include <nn_impl/bounded_nn.hpp>
#include <nn_impl/stack_nn.hpp>

using namespace cleanpp;

typedef stack_nn nn_type;
typedef linked_stack<nn_type> stack_nn_type;

static std::string stackNNToString(std::unique_ptr<stack_impl<nn_type>>& s) {
    std::stringstream s_stm;
    s_stm << *s;
    std::string s_str = s_stm.str();
    return s_str;
}

TEST(LinkedStackNaturalNumber, InitializerDefTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string empty_stack = "<>";
    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == empty_stack);
}

TEST(LinkedStackNaturalNumber, IsEmpty_EmptyTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    EXPECT_TRUE(s->is_empty());
}

TEST(LinkedStackNaturalNumber, IsEmpty_NonEmptyTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    nn_type a(1);
    s->push(std::move(a));
    EXPECT_TRUE(!s->is_empty());
}

TEST(LinkedStackNaturalNumber, IsEmpty_Empty_PushPopTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    nn_type a(1), b(2);
    s->push(std::move(a));
    b = s->pop();
    EXPECT_TRUE(s->is_empty());
}

TEST(LinkedStackNaturalNumber, PushToEmptyTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<1>";

    nn_type a(1);
    s->push(std::move(a));

    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == expected_stack);
}

TEST(LinkedStackNaturalNumber, PushToNonEmptyTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<2, 1>";

    nn_type a(1), b(2);
    s->push(std::move(a));
    s->push(std::move(b));

    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == expected_stack);
}

TEST(LinkedStackNaturalNumber, PopEmptyToEmptyTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<>";
    nn_type expected_a(0);

    nn_type a(1), b(2);
    s->push(std::move(a));
    b = s->pop();

    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == expected_stack);
    EXPECT_TRUE(a == expected_a);
}

TEST(LinkedStackNaturalNumber, PopNonEmptyToEmptyTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<>";
    nn_type expected_b(1);

    nn_type a(1), b(2);
    s->push(std::move(a));
    b = s->pop();

    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == expected_stack);
    EXPECT_TRUE(b == expected_b);
}

TEST(LinkedStackNaturalNumber, FlipNonEmptyTest) {
    GTEST_SKIP();
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<0, 1, 2, 3, 4>";
    int numElem = 5;
    for(int i = 0; i < numElem; i++){
        s->push(std::move(i));
    }

    s->flip();

    std::string s_str = stackNNToString(s);
    EXPECT_EQ(s_str, expected_stack);
}