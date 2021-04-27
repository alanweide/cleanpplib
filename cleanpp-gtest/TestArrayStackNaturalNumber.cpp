#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <stack_impls/linked_stack.hpp>
#include <stack_impls/array_stack.hpp>
#include <natural_number_impls/bounded_nn.hpp>
#include <natural_number_impls/stack_nn.hpp>

using namespace cleanpp;

typedef stack_nn nn_type;
typedef array_stack<nn_type> stack_nn_type;

static std::string stackNNToString(std::unique_ptr<stack_impl<nn_type>> &s) {
    std::stringstream s_stm;
    s_stm << *s;
    std::string s_str = s_stm.str();
    return s_str;
}

TEST(ArrayStackNaturalNumber, InitializerDefTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string empty_stack = "<>";
    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == empty_stack);
}

TEST(ArrayStackNaturalNumber, IsEmpty_EmptyTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    EXPECT_TRUE(s->is_empty());
}

TEST(ArrayStackNaturalNumber, IsEmpty_NonEmptyTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    nn_type a(1);
    s->push(std::move(a));
    EXPECT_TRUE(!s->is_empty());
}

TEST(ArrayStackNaturalNumber, IsEmpty_Empty_PushPopTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    nn_type a(1), b(2);
    s->push(std::move(a));
    b = s->pop();
    EXPECT_TRUE(s->is_empty());
}

TEST(ArrayStackNaturalNumber, PushToEmptyTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<1>";
    
    nn_type a(1);
    s->push(std::move(a));
    
    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == expected_stack);
}

TEST(ArrayStackNaturalNumber, PushToNonEmptyTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<2, 1>";
    
    nn_type a(1), b(2);
    s->push(std::move(a));
    s->push(std::move(b));
    
    std::string s_str = stackNNToString(s);
    EXPECT_TRUE(s_str == expected_stack);
}

TEST(ArrayStackNaturalNumber, PopEmptyToEmptyTest) {
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

TEST(ArrayStackNaturalNumber, PopNonEmptyToEmptyTest) {
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

TEST(ArrayStackNaturalNumber, NonMonotonicResizingTest) {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    nn_type expected_b(1);
    
    const int cap = 100;
    for (int i = 0; i < cap; i++) {
        nn_type n(i);
        s->push(std::move(n));
    }
    while (!s->is_empty()) {
        nn_type n;
        n = s->pop();
    }
    
    EXPECT_TRUE(s->is_empty());
}
