#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <integer_impl/nn_integer.hpp>
#include <integer_impl/vector_integer.hpp>
#include <integer.hpp>
#include "../src/clean_integer/integer_impl.cpp"

using namespace cleanpp;

typedef nn_integer bigint_kernel_impl;

static std::string bigintToString(integer& o) {
    std::stringstream s;
    s << o;
    return s.str();
}

TEST(FlexInteger, InitializerDefTest) {
    integer n(bigint_kernel_impl{});

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "0");
    EXPECT_TRUE(n.sign() == ZERO);
}

TEST(FlexInteger, Initializer_SingleDigTest) {
    integer n(bigint_kernel_impl{}, 4);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "4");
    EXPECT_TRUE(n.sign() == POSITIVE);
}

TEST(FlexInteger, Initializer_TwoDigTest) {
    integer n(bigint_kernel_impl{}, 45);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "45");
    EXPECT_TRUE(n.sign() == POSITIVE);
}


TEST(FlexInteger, Initializer_SingleDigNegTest) {
    integer n(bigint_kernel_impl{}, -4);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "-4");
    EXPECT_TRUE(n.sign() == NEGATIVE);
}

TEST(FlexInteger, Initializer_TwoDigNegTest) {
    integer n(bigint_kernel_impl{}, -45);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "-45");
    EXPECT_TRUE(n.sign() == NEGATIVE);
}

TEST(FlexInteger, ClearZeroTest) {
    integer n(bigint_kernel_impl{});
    integer expected(bigint_kernel_impl{});

    n.clear();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, ClearPositiveTest) {
    integer n(bigint_kernel_impl{}, 47);
    integer expected(bigint_kernel_impl{}, 0);

    n.clear();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, ClearNegativeTest) {
    integer n(bigint_kernel_impl{}, -47);
    integer expected(bigint_kernel_impl{}, 0);

    n.clear();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, IncrementZeroTest) {
    integer n(bigint_kernel_impl{}, 0);
    integer expected(bigint_kernel_impl{}, 1);

    n.increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, IncrementNineTest) {
    integer n(bigint_kernel_impl{}, 9);
    integer expected(bigint_kernel_impl{}, 10);

    n.increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, IncrementFiveTest) {
    integer n(bigint_kernel_impl{}, 5);
    integer expected(bigint_kernel_impl{}, 6);

    n.increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, IncrementNegTenTest) {
    integer n(nn_integer{}, -10);
    integer expected(nn_integer{}, -9);

    n.increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, IncrementNegFiveTest) {
    integer n(bigint_kernel_impl{}, -5);
    integer expected(bigint_kernel_impl{}, -4);

    n.increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, IncrementNegOneTest) {
    integer n(bigint_kernel_impl{}, -1);
    integer expected(bigint_kernel_impl{}, 0);

    n.increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, DecrementOneTest) {
    integer n(bigint_kernel_impl{}, 1);
    integer expected(bigint_kernel_impl{}, 0);

    n.decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, DecrementTenTest) {
    integer n(bigint_kernel_impl{}, 10);
    integer expected(bigint_kernel_impl{}, 9);

    n.decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, DecrementFiveTest) {
    integer n(bigint_kernel_impl{}, 5);
    integer expected(bigint_kernel_impl{}, 4);

    n.decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, DecrementZeroTest) {
    integer n(bigint_kernel_impl{}, 0);
    integer expected(bigint_kernel_impl{}, -1);

    n.decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, DecrementNegNineTest) {
    integer n(bigint_kernel_impl{}, -9);
    integer expected(bigint_kernel_impl{}, -10);

    n.decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, DecrementNegFiveTest) {
    integer n(bigint_kernel_impl{}, -5);
    integer expected(bigint_kernel_impl{}, -6);

    n.decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, MultRadZero_ZeroTest) {
    integer n(bigint_kernel_impl{}, 0);
    integer expected(bigint_kernel_impl{}, 0);

    n.multiply_by_radix(0);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, MultRadZero_FiveTest) {
    integer n(bigint_kernel_impl{}, 0);
    integer expected(bigint_kernel_impl{}, 5);

    n.multiply_by_radix(5);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, MultRadFive_ZeroTest) {
    integer n(bigint_kernel_impl{}, 5);
    integer expected(bigint_kernel_impl{}, 50);

    n.multiply_by_radix(0);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, MultRadFive_FiveTest) {
    integer n(bigint_kernel_impl{}, 5);
    integer expected(bigint_kernel_impl{}, 55);

    n.multiply_by_radix(5);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, MultRadNegFive_ZeroTest) {
    integer n(bigint_kernel_impl{}, -5);
    integer expected(bigint_kernel_impl{}, -50);

    n.multiply_by_radix(0);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, MultRadNegFive_FiveTest) {
    integer n(bigint_kernel_impl{}, -5);
    integer expected(bigint_kernel_impl{}, -55);

    n.multiply_by_radix(5);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
}

TEST(FlexInteger, DivRadZeroTest) {
    integer n(bigint_kernel_impl{}, 0);
    integer expected(bigint_kernel_impl{}, 0);

    int d = n.divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
    EXPECT_TRUE(d == 0);
}

TEST(FlexInteger, DivRadFiveTest) {
    integer n(bigint_kernel_impl{}, 5);
    integer expected(bigint_kernel_impl{}, 0);

    int d = n.divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
    EXPECT_TRUE(d == 5);
}

TEST(FlexInteger, DiveRadFiftyTest) {
    integer n(bigint_kernel_impl{}, 50);
    integer expected(bigint_kernel_impl{}, 5);

    int d = n.divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
    EXPECT_TRUE(d == 0);
}

TEST(FlexInteger, DivRadFiftyFiveTest) {
    integer n(bigint_kernel_impl{}, 55);
    integer expected(bigint_kernel_impl{}, 5);

    int d = n.divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
    EXPECT_TRUE(d == 5);
}

TEST(FlexInteger, DivRadNegFiveTest) {
    integer n(bigint_kernel_impl{}, -5);
    integer expected(bigint_kernel_impl{}, 0);

    int d = n.divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
    EXPECT_TRUE(d == 5);
}

TEST(FlexInteger, DiveRadNegFiftyTest) {
    integer n(bigint_kernel_impl{}, -50);
    integer expected(bigint_kernel_impl{}, -5);

    int d = n.divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
    EXPECT_TRUE(d == 0);
}

TEST(FlexInteger, DivRadNegFiftyFiveTest) {
    integer n(bigint_kernel_impl{}, -55);
    integer expected(bigint_kernel_impl{}, -5);

    int d = n.divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n == expected);
    EXPECT_TRUE(d == 5);
}

TEST(FlexInteger, CloneFromZeroTest) {
    integer n(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{});
    integer n_exp(bigint_kernel_impl{});
    integer n2_exp(bigint_kernel_impl{});

    n = n2.clone();

    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, CloneFromOneTest) {
    integer n(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, 1);
    integer n_exp(bigint_kernel_impl{}, 1);
    integer n2_exp(bigint_kernel_impl{}, 1);

    n = n2.clone();

    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, CloneFromThreeTest) {
    integer n(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, 3);
    integer n_exp(bigint_kernel_impl{}, 3);
    integer n2_exp(bigint_kernel_impl{}, 3);

    n = n2.clone();

    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, CloneFromFiveTest) {
    integer n(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, 5);
    integer n_exp(bigint_kernel_impl{}, 5);
    integer n2_exp(bigint_kernel_impl{}, 5);

    n = n2.clone();

    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, CloneFrom25Test) {
    integer n(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, 25);
    integer n_exp(bigint_kernel_impl{}, 25);
    integer n2_exp(bigint_kernel_impl{}, 25);

    n = n2.clone();

    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, CloneFromNegOneTest) {
    integer n(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, -1);
    integer n_exp(bigint_kernel_impl{}, -1);
    integer n2_exp(bigint_kernel_impl{}, -1);

    n = n2.clone();

    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, CloneFromNegThreeTest) {
    integer n(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, -3);
    integer n_exp(bigint_kernel_impl{}, -3);
    integer n2_exp(bigint_kernel_impl{}, -3);

    n = n2.clone();

    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, CloneFromNegFiveTest) {
    integer n(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, -5);
    integer n_exp(bigint_kernel_impl{}, -5);
    integer n2_exp(bigint_kernel_impl{}, -5);

    n = n2.clone();

    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, CloneFromNeg25Test) {
    integer n(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, -25);
    integer n_exp(bigint_kernel_impl{}, -25);
    integer n2_exp(bigint_kernel_impl{}, -25);

    n = n2.clone();

    EXPECT_TRUE(n == n_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

/* ----------------------------
 * friend functions
 * ---------------------------- */

TEST(FlexInteger, CompareZeroZeroTest) {
    integer n1(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{});
    integer n2_exp(bigint_kernel_impl{});

    int comp;
    std::tie(comp, n1, n2) = compare(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
    EXPECT_TRUE(comp == 0);
}

TEST(FlexInteger, CompareZeroOneTest) {
    integer n1(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, 1);
    integer n1_exp(bigint_kernel_impl{});
    integer n2_exp(bigint_kernel_impl{}, 1);

    int comp;
    std::tie(comp, n1, n2) = compare(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
    EXPECT_TRUE(comp < 0);
}

TEST(FlexInteger, CompareOneZeroTest) {
    integer n1(bigint_kernel_impl{}, 1);
    integer n2(bigint_kernel_impl{}, 0);
    integer n1_exp(bigint_kernel_impl{}, 1);
    integer n2_exp(bigint_kernel_impl{}, 0);

    int comp;
    std::tie(comp, n1, n2) = compare(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
    EXPECT_TRUE(comp > 0);
}

TEST(FlexInteger, CompareFiveTwoTest) {
    integer n1(bigint_kernel_impl{}, 5);
    integer n2(bigint_kernel_impl{}, 2);
    integer n1_exp(bigint_kernel_impl{}, 5);
    integer n2_exp(bigint_kernel_impl{}, 2);

    int comp;
    std::tie(comp, n1, n2) = compare(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
    EXPECT_TRUE(comp > 0);
}

TEST(FlexInteger, CompareFiveNeg4Test) {
    integer n1(bigint_kernel_impl{}, 5);
    integer n2(bigint_kernel_impl{}, -4);
    integer n1_exp(bigint_kernel_impl{}, 5);
    integer n2_exp(bigint_kernel_impl{}, -4);

    int comp;
    std::tie(comp, n1, n2) = compare(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
    EXPECT_TRUE(comp > 0);
}

TEST(FlexInteger, CompareNegFourFiveTest) {
    integer n1(bigint_kernel_impl{}, -4);
    integer n2(bigint_kernel_impl{}, 5);
    integer n1_exp(bigint_kernel_impl{}, -4);
    integer n2_exp(bigint_kernel_impl{}, 5);

    int comp;
    std::tie(comp, n1, n2) = compare(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
    EXPECT_TRUE(comp < 0);
}

TEST(FlexInteger, CompareTenSixTest) {
    integer n1(bigint_kernel_impl{}, 10);
    integer n2(bigint_kernel_impl{}, 6);
    integer n1_exp(bigint_kernel_impl{}, 10);
    integer n2_exp(bigint_kernel_impl{}, 6);

    int comp;
    std::tie(comp, n1, n2) = compare(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
    EXPECT_TRUE(comp > 0);
}

TEST(FlexInteger, CompareNegTenNegSixTest) {
    integer n1(bigint_kernel_impl{}, -10);
    integer n2(bigint_kernel_impl{}, -6);
    integer n1_exp(bigint_kernel_impl{}, -10);
    integer n2_exp(bigint_kernel_impl{}, -6);

    int comp;
    std::tie(comp, n1, n2) = compare(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
    EXPECT_TRUE(comp < 0);
}

TEST(FlexInteger, CompareTenNegTenTest) {
    integer n1(bigint_kernel_impl{}, 10);
    integer n2(bigint_kernel_impl{}, -10);
    integer n1_exp(bigint_kernel_impl{}, 10);
    integer n2_exp(bigint_kernel_impl{}, -10);

    int comp;
    std::tie(comp, n1, n2) = compare(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
    EXPECT_TRUE(comp > 0);
}

TEST(FlexInteger, CompareNegTenTenTest) {
    integer n1(bigint_kernel_impl{}, -10);
    integer n2(bigint_kernel_impl{}, 10);
    integer n1_exp(bigint_kernel_impl{}, -10);
    integer n2_exp(bigint_kernel_impl{}, 10);

    int comp;
    std::tie(comp, n1, n2) = compare(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
    EXPECT_TRUE(comp < 0);
}

TEST(FlexInteger, AddZeroZeroTest) {
    integer n1(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{});
    integer n2_exp(bigint_kernel_impl{});

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddZeroFiveTest) {
    integer n1(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, 5);
    integer n1_exp(bigint_kernel_impl{}, 5);
    integer n2_exp(bigint_kernel_impl{}, 5);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddFiveZeroTest) {
    integer n1(bigint_kernel_impl{}, 5);
    integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{}, 5);
    integer n2_exp(bigint_kernel_impl{});

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddFourFourTest) {
    integer n1(bigint_kernel_impl{}, 4);
    integer n2(bigint_kernel_impl{}, 4);
    integer n1_exp(bigint_kernel_impl{}, 8);
    integer n2_exp(bigint_kernel_impl{}, 4);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddFiveFiveTest) {
    integer n1(bigint_kernel_impl{}, 5);
    integer n2(bigint_kernel_impl{}, 5);
    integer n1_exp(bigint_kernel_impl{}, 10);
    integer n2_exp(bigint_kernel_impl{}, 5);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddTenTenTest) {
    integer n1(bigint_kernel_impl{}, 10);
    integer n2(bigint_kernel_impl{}, 10);
    integer n1_exp(bigint_kernel_impl{}, 20);
    integer n2_exp(bigint_kernel_impl{}, 10);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, Add57_66Test) {
    integer n1(bigint_kernel_impl{}, 57);
    integer n2(bigint_kernel_impl{}, 66);
    integer n1_exp(bigint_kernel_impl{}, 123);
    integer n2_exp(bigint_kernel_impl{}, 66);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddZeroNegFiveTest) {
    integer n1(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, -5);
    integer n1_exp(bigint_kernel_impl{}, -5);
    integer n2_exp(bigint_kernel_impl{}, -5);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddNegFiveZeroTest) {
    integer n1(bigint_kernel_impl{}, -5);
    integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{}, -5);
    integer n2_exp(bigint_kernel_impl{});

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddFourNegFourTest) {
    integer n1(bigint_kernel_impl{}, 4);
    integer n2(bigint_kernel_impl{}, -4);
    integer n1_exp(bigint_kernel_impl{}, 0);
    integer n2_exp(bigint_kernel_impl{}, -4);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddNegFourNegFourTest) {
    integer n1(bigint_kernel_impl{}, -4);
    integer n2(bigint_kernel_impl{}, -4);
    integer n1_exp(bigint_kernel_impl{}, -8);
    integer n2_exp(bigint_kernel_impl{}, -4);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddNegFiveNegFiveTest) {
    integer n1(bigint_kernel_impl{}, -5);
    integer n2(bigint_kernel_impl{}, -5);
    integer n1_exp(bigint_kernel_impl{}, -10);
    integer n2_exp(bigint_kernel_impl{}, -5);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, AddNegTenNegTenTest) {
    integer n1(bigint_kernel_impl{}, -10);
    integer n2(bigint_kernel_impl{}, -10);
    integer n1_exp(bigint_kernel_impl{}, -20);
    integer n2_exp(bigint_kernel_impl{}, -10);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, Add57_Neg66Test) {
    integer n1(bigint_kernel_impl{}, 67);
    integer n2(bigint_kernel_impl{}, -56);
    integer n1_exp(bigint_kernel_impl{}, 11);
    integer n2_exp(bigint_kernel_impl{}, -56);

    std::tie(n1, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, SubtractZeroZeroTest) {
    integer n1(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{});
    integer n2_exp(bigint_kernel_impl{});

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, SubtractFiveZeroTest) {
    integer n1(bigint_kernel_impl{}, 5);
    integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{}, 5);
    integer n2_exp(bigint_kernel_impl{});

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, SubtractFourFourTest) {
    integer n1(bigint_kernel_impl{}, 4);
    integer n2(bigint_kernel_impl{}, 4);
    integer n1_exp(bigint_kernel_impl{}, 0);
    integer n2_exp(bigint_kernel_impl{}, 4);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, SubtractTenTenTest) {
    integer n1(bigint_kernel_impl{}, 10);
    integer n2(bigint_kernel_impl{}, 10);
    integer n1_exp(bigint_kernel_impl{}, 0);
    integer n2_exp(bigint_kernel_impl{}, 10);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, Subtract77_66Test) {
    integer n1(bigint_kernel_impl{}, 77);
    integer n2(bigint_kernel_impl{}, 66);
    integer n1_exp(bigint_kernel_impl{}, 11);
    integer n2_exp(bigint_kernel_impl{}, 66);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, Subtract77_6Test) {
    integer n1(bigint_kernel_impl{}, 77);
    integer n2(bigint_kernel_impl{}, 6);
    integer n1_exp(bigint_kernel_impl{}, 71);
    integer n2_exp(bigint_kernel_impl{}, 6);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, Subtract71_66Test) {
    integer n1(bigint_kernel_impl{}, 71);
    integer n2(bigint_kernel_impl{}, 66);
    integer n1_exp(bigint_kernel_impl{}, 5);
    integer n2_exp(bigint_kernel_impl{}, 66);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, Subtract3_4Test) {
    integer n1(bigint_kernel_impl{}, 3);
    integer n2(bigint_kernel_impl{}, 4);
    integer n1_exp(bigint_kernel_impl{}, -1);
    integer n2_exp(bigint_kernel_impl{}, 4);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, SubtractNegFiveZeroTest) {
    integer n1(bigint_kernel_impl{}, -5);
    integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{}, -5);
    integer n2_exp(bigint_kernel_impl{});

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, SubtractFourNegFourTest) {
    integer n1(bigint_kernel_impl{}, 4);
    integer n2(bigint_kernel_impl{}, -4);
    integer n1_exp(bigint_kernel_impl{}, 8);
    integer n2_exp(bigint_kernel_impl{}, -4);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, SubtractNegFourNegFourTest) {
    integer n1(bigint_kernel_impl{}, -4);
    integer n2(bigint_kernel_impl{}, -4);
    integer n1_exp(bigint_kernel_impl{}, 0);
    integer n2_exp(bigint_kernel_impl{}, -4);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, Subtract77_Neg66Test) {
    integer n1(bigint_kernel_impl{}, 77);
    integer n2(bigint_kernel_impl{}, -66);
    integer n1_exp(bigint_kernel_impl{}, 143);
    integer n2_exp(bigint_kernel_impl{}, -66);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, SubtractNeg77_66Test) {
    integer n1(bigint_kernel_impl{}, -77);
    integer n2(bigint_kernel_impl{}, 66);
    integer n1_exp(bigint_kernel_impl{}, -143);
    integer n2_exp(bigint_kernel_impl{}, 66);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexInteger, Subtract1_2Test) {
    integer n1(bigint_kernel_impl{}, 1);
    integer n2(bigint_kernel_impl{}, 2);
    integer n1_exp(bigint_kernel_impl{}, -1);
    integer n2_exp(bigint_kernel_impl{}, 2);

    std::tie(n1, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}
