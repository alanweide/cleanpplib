#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <nn_impl/stack_nn.hpp>

using namespace cleanpp;

typedef stack_nn nn_type;

static std::string nnPtrToString(std::unique_ptr<natural_number_impl>& o) {
    std::stringstream s;
    s << *o;
    return s.str();
}

static std::string nn_k_ToString(std::unique_ptr<natural_number_kernel_impl>& o) {
    std::stringstream s;
    s << *o;
    return s.str();
}

static std::string nnToString(nn_type& o) {
    std::stringstream s;
    s << o;
    return s.str();
}

TEST(StackNN, InitializerDefTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(n_str == "0");
}

TEST(StackNN, Initializer_SingleDigTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(4);

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(n_str == "4");
}

TEST(StackNN, Initializer_TwoDigTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(45);

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(n_str == "45");
}

TEST(StackNN, MoveInit_ZeroTest) {
    nn_type m, m_expected;
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>();

    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(std::move(m));

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *n_expected);
    EXPECT_TRUE(m == m_expected);
}

TEST(StackNN, MoveInit_SingleDigTest) {
    nn_type m(5), m_expected;
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>(5);

    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(std::move(m));

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *n_expected);
    EXPECT_TRUE(m == m_expected);
}

TEST(StackNN, MoveInit_MultiDigTest) {
    nn_type m(76), m_expected;
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>(76);

    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(std::move(m));

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *n_expected);
    EXPECT_TRUE(m == m_expected);
}

TEST(StackNN, Assign_ZeroToZeroTest) {
    nn_type n, m, n_exp, m_exp;

    n = std::move(m);

    std::string n_str = nnToString(n);
    std::string m_str = nnToString(m);
    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(m == m_exp);
}

TEST(StackNN, Assign_ZeroToNonZeroTest) {
    nn_type n(5), m, n_exp, m_exp;

    n = std::move(m);

    std::string n_str = nnToString(n);
    std::string m_str = nnToString(m);
    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(m == m_exp);
}

TEST(StackNN, Assign_NonzeroToZeroTest) {
    nn_type n, m(5), n_exp(5), m_exp;

    n = std::move(m);

    std::string n_str = nnToString(n);
    std::string m_str = nnToString(m);
    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(m == m_exp);
}

TEST(StackNN, Assign_NonzeroToNonzeroTest) {
    nn_type n(3), m(5), n_exp(5), m_exp(0);

    n = std::move(m);

    std::string n_str = nnToString(n);
    std::string m_str = nnToString(m);
    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(m == m_exp);
}

TEST(StackNN, Assign_MultidigToZeroTest) {
    nn_type n, m(76), n_exp(76), m_exp;

    n = std::move(m);

    std::string n_str = nnToString(n);
    std::string m_str = nnToString(m);
    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(m == m_exp);
}


TEST(StackNN, Assign_MultidigToMultidigTest) {
    nn_type n(89), m(76), n_exp(76), m_exp;

    n = std::move(m);

    std::string n_str = nnToString(n);
    std::string m_str = nnToString(m);
    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(m == m_exp);
}

TEST(StackNN, NewInstanceTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    std::unique_ptr<natural_number_kernel_impl> new_n = n->new_instance();

    std::string new_n_str = nn_k_ToString(new_n);
    EXPECT_TRUE(*new_n == *expected);
}

TEST(StackNN, NewInstance_castedTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    std::unique_ptr<natural_number_impl> new_n(static_cast<natural_number_impl*>(n->new_instance().release()));

    std::string new_n_str = nnPtrToString(new_n);
    EXPECT_TRUE(*new_n == *expected);
}

TEST(StackNN, ClearZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    n->clear();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, ClearNonZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(47);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    n->clear();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, IncrementZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(1);

    n->increment();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, IncrementNineTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(9);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(10);

    n->increment();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, IncrementFiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(6);

    n->increment();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, DecrementOneTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(1);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    n->decrement();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, DecrementTenTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(9);

    n->decrement();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, DecrementFiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(4);

    n->decrement();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, MultRadZero_ZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    n->multiply_by_radix(0);

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, MultRadZero_FiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(5);

    n->multiply_by_radix(5);

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, MultRadFive_ZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(50);

    n->multiply_by_radix(0);

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, MultRadFive_FiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(55);

    n->multiply_by_radix(5);

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(StackNN, DivRadZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 0);
}

TEST(StackNN, DivRadFiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 5);
}

TEST(StackNN, DiveRadFiftyTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(50);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(5);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 0);
}

TEST(StackNN, DivRadFiftyFiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(55);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(5);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = nnPtrToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 5);
}

TEST(StackNN, AddZeroZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, AddZeroFiveTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(5);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, AddFiveZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, AddFourFourTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(8);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(4);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, AddFiveFiveTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(5);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, AddTenTenTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(20);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(10);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, Add57_66Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(57);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(123);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(66);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, SubtractZeroZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, SubtractFiveZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, SubtractFourFourTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(4);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, SubtractTenTenTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(10);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, Subtract77_66Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(11);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(66);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, Subtract77_6Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(6);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(71);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(6);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, Subtract71_66Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(71);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(66);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, MultiplyZeroZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, MultiplyFiveZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, MultiplyFourFourTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(16);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(4);

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, MultiplyTenTenTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(100);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(10);

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, Multiply77_66Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(5082);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(66);

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, Multiply77_6Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(6);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(462);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(6);

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(StackNN, Multiply71_66Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(71);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(4686);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(66);

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}
