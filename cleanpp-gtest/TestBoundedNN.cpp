#include <gtest/gtest.h>

#include <stdio.h>
#include <sstream>
#include <nn_impl/nn_impl.hpp>
#include <nn_impl/bounded_nn.hpp>

using namespace cleanpp;

typedef bounded_nn nn_type;

static std::string nnToString(std::unique_ptr<natural_number_impl>& o) {
    std::stringstream s;
    s << *o;
    return s.str();
}

static std::string nn_k_ToString(std::unique_ptr<natural_number_kernel_impl>& o) {
    std::stringstream s;
    s << *o;
    return s.str();
}

TEST(BoundedNN, InitializerDefTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(n_str == "0");
}

TEST(BoundedNN, Initializer_SingleDigTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(4);

    std::string n_str = nnToString(n);
    EXPECT_TRUE(n_str == "4");
}

TEST(BoundedNN, Initializer_TwoDigTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(45);

    std::string n_str = nnToString(n);
    EXPECT_TRUE(n_str == "45");
}

TEST(BoundedNN, MoveInit_ZeroTest) {
    nn_type m, m_expected;
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>();

    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(std::move(m));

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *n_expected);
    EXPECT_TRUE(m == m_expected);
}

TEST(BoundedNN, MoveInit_SingleDigTest) {
    nn_type m(5), m_expected;
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>(5);

    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(std::move(m));

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *n_expected);
    EXPECT_TRUE(m == m_expected);
}

TEST(BoundedNN, MoveInit_MultiDigTest) {
    nn_type m(76), m_expected;
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>(76);

    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(std::move(m));

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *n_expected);
    EXPECT_TRUE(m == m_expected);
}

TEST(BoundedNN, AssignZeroZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> m = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> m_expected = std::make_unique<nn_type>();

    *n = std::move(*m);

    std::string n_str = nnToString(n);
    std::string m_str = nnToString(m);
    EXPECT_TRUE(*n == *n_expected);
    EXPECT_TRUE(*m == *m_expected);
}

TEST(BoundedNN, AssignZeroNonzeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> m = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>(5);

    n = std::move(m);

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *n_expected);
}

TEST(BoundedNN, AssignNonzeroZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> m = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>(0);

    n = std::move(m);

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *n_expected);
}

TEST(BoundedNN, AssignNonzeroNonzeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(9);
    std::unique_ptr<natural_number_impl> m = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>(5);

    n = std::move(m);

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *n_expected);
}

TEST(BoundedNN, AssignMultidigMultidigTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(96);
    std::unique_ptr<natural_number_impl> m = std::make_unique<nn_type>(43);
    std::unique_ptr<natural_number_impl> n_expected = std::make_unique<nn_type>(43);

    n = std::move(m);

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *n_expected);
}

TEST(BoundedNN, NewInstanceTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    std::unique_ptr<natural_number_kernel_impl> new_n = n->new_instance();

    std::string new_n_str = nn_k_ToString(new_n);
    EXPECT_TRUE(*new_n == *expected);
}

TEST(BoundedNN, NewInstance_castedTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    std::unique_ptr<natural_number_impl> new_n(static_cast<natural_number_impl*>(n->new_instance().release()));

    std::string new_n_str = nnToString(new_n);
    EXPECT_TRUE(*new_n == *expected);
}

TEST(BoundedNN, ClearZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    n->clear();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, ClearNonZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(47);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    n->clear();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, IncrementZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(1);

    n->increment();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, IncrementNineTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(9);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(10);

    n->increment();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, IncrementFiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(6);

    n->increment();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, DecrementOneTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(1);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    n->decrement();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, DecrementTenTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(9);

    n->decrement();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, DecrementFiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(4);

    n->decrement();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, MultRadZero_ZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    n->multiply_by_radix(0);

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, MultRadZero_FiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(5);

    n->multiply_by_radix(5);

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, MultRadFive_ZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(50);

    n->multiply_by_radix(0);

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, MultRadFive_FiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(55);

    n->multiply_by_radix(5);

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(BoundedNN, DivRadZeroTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 0);
}

TEST(BoundedNN, DivRadFiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(0);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 5);
}

TEST(BoundedNN, DiveRadFiftyTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(50);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(5);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 0);
}

TEST(BoundedNN, DivRadFiftyFiveTest) {
    std::unique_ptr<natural_number_impl> n = std::make_unique<nn_type>(55);
    std::unique_ptr<natural_number_impl> expected = std::make_unique<nn_type>(5);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = nnToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 5);
}

TEST(BoundedNN, AddZeroZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();
    
    // n1 = add(std::move(n1), n2);
    std::unique_ptr<natural_number_impl> dummy = std::make_unique<nn_type>();
    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, AddZeroFiveTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(5);
    
    // n1 = add(std::move(n1), n2);
    std::unique_ptr<natural_number_impl> dummy = std::make_unique<nn_type>();
    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, AddFiveZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();
    
    // n1 = add(std::move(n1), n2);
    std::unique_ptr<natural_number_impl> dummy = std::make_unique<nn_type>();
    std::tie(n1, n2) = add(std::move(n1), std::move(n2));
  
    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, AddFourFourTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(8);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(4);
    
    // n1 = add(std::move(n1), n2);
    std::unique_ptr<natural_number_impl> dummy = std::make_unique<nn_type>();
    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, AddFiveFiveTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(5);
    
    // n1 = add(std::move(n1), n2);
    std::unique_ptr<natural_number_impl> dummy = std::make_unique<nn_type>();
    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

  std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, AddTenTenTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(20);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(10);
    
    // n1 = add(std::move(n1), n2);
    std::unique_ptr<natural_number_impl> dummy = std::make_unique<nn_type>();
    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, Add57_66Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(57);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(123);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(66);
    
    // n1 = add(std::move(n1), n2);
    std::unique_ptr<natural_number_impl> dummy = std::make_unique<nn_type>();
    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, SubtractZeroZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, SubtractFiveZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, SubtractFourFourTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(4);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, SubtractTenTenTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(10);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, Subtract77_66Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(11);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(66);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, Subtract77_6Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(6);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(71);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(6);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, Subtract71_66Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(71);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(66);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, MultiplyZeroZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, MultiplyFiveZeroTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>();

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, MultiplyFourFourTest) {
    //    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(4);
    //    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(4);
    //    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(16);
    //    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_impl> n1(new nn_type(4));
    std::unique_ptr<natural_number_impl> n2(new nn_type(4));
    std::unique_ptr<natural_number_impl> n1_exp(new nn_type(16));
    std::unique_ptr<natural_number_impl> n2_exp(new nn_type(4));

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, MultiplyTenTenTest) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(100);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(10);

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, Multiply77_66Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(5082);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(66);

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, Multiply77_6Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(6);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(462);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(6);

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(BoundedNN, Multiply71_66Test) {
    std::unique_ptr<natural_number_impl> n1 = std::make_unique<nn_type>(71);
    std::unique_ptr<natural_number_impl> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_impl> n1_exp = std::make_unique<nn_type>(4686);
    std::unique_ptr<natural_number_impl> n2_exp = std::make_unique<nn_type>(66);

    std::tie(n1, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}
