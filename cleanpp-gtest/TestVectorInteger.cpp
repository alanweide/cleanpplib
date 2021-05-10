#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <integer_impl/vector_integer.hpp>
#include "../src/clean_integer/integer_impl.cpp"

using namespace cleanpp;

typedef vector_integer bigint_type;

static std::string bigintToString(std::unique_ptr<integer_impl>& o) {
    std::stringstream s;
    s << *o;
    return s.str();
}

TEST(VectorInteger, InitializerDefTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "0");
    EXPECT_TRUE(n->sign() == ZERO);
}

TEST(VectorInteger, Initializer_SingleDigTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(4);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "4");
    EXPECT_TRUE(n->sign() == POSITIVE);
}

TEST(VectorInteger, Initializer_TwoDigTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(45);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "45");
    EXPECT_TRUE(n->sign() == POSITIVE);
}


TEST(VectorInteger, Initializer_SingleDigNegTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-4);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "-4");
    EXPECT_TRUE(n->sign() == NEGATIVE);
}

TEST(VectorInteger, Initializer_TwoDigNegTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-45);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "-45");
    EXPECT_TRUE(n->sign() == NEGATIVE);
}

TEST(VectorInteger, ClearZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(0);

    n->clear();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, ClearPositiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(47);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(0);

    n->clear();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, ClearNegativeTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-47);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(0);

    n->clear();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, IncrementZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(1);

    n->increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, IncrementNineTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(9);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(10);

    n->increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, IncrementFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(6);

    n->increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, IncrementNegTenTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(-9);

    n->increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, IncrementNegFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(-4);

    n->increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, IncrementNegOneTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(0);

    n->increment();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, DecrementOneTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(0);

    n->decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, DecrementTenTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(9);

    n->decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, DecrementFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(4);

    n->decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, DecrementZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(-1);

    n->decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, DecrementNegNineTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-9);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(-10);

    n->decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, DecrementNegFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(-6);

    n->decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, MultRadZero_ZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(0);

    n->multiply_by_radix(0);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, MultRadZero_FiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(5);

    n->multiply_by_radix(5);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, MultRadFive_ZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(50);

    n->multiply_by_radix(0);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, MultRadFive_FiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(55);

    n->multiply_by_radix(5);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, MultRadNegFive_ZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(-50);

    n->multiply_by_radix(0);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, MultRadNegFive_FiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(-55);

    n->multiply_by_radix(5);

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(VectorInteger, DivRadZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(0);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 0);
}

TEST(VectorInteger, DivRadFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(0);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 5);
}

TEST(VectorInteger, DiveRadFiftyTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(50);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(5);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 0);
}

TEST(VectorInteger, DivRadFiftyFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(55);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(5);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 5);
}

TEST(VectorInteger, DivRadNegFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(0);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 5);
}

TEST(VectorInteger, DiveRadNegFiftyTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-50);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(-5);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 0);
}

TEST(VectorInteger, DivRadNegFiftyFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-55);
    std::unique_ptr<integer_impl> expected = std::make_unique<bigint_type>(-5);

    int d = 4;
    d = n->divide_by_radix();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 5);
}

TEST(VectorInteger, CloneFromZeroTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, CloneFromOneTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(1);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, CloneFromThreeTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(3);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(3);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(3);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, CloneFromFiveTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, CloneFrom25Test) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(25);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(25);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(25);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, CloneFromNegOneTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-1);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, CloneFromNegThreeTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-3);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-3);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-3);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, CloneFromNegFiveTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-5);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, CloneFromNeg25Test) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-25);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-25);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-25);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

/* ----------------------------
 * friend functions
 * ---------------------------- */

TEST(VectorInteger, CompareZeroZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
    EXPECT_TRUE(comp == 0);
}

TEST(VectorInteger, CompareZeroOneTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(1);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
    EXPECT_TRUE(comp < 0);
}

TEST(VectorInteger, CompareOneZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(0);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
    EXPECT_TRUE(comp > 0);
}

TEST(VectorInteger, CompareFiveTwoTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(2);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(2);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
    EXPECT_TRUE(comp > 0);
}

TEST(VectorInteger, CompareFiveNeg4Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
    EXPECT_TRUE(comp > 0);
}

TEST(VectorInteger, CompareNegFourFiveTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-4);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
    EXPECT_TRUE(comp < 0);
}

TEST(VectorInteger, CompareTenSixTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(6);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(6);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
    EXPECT_TRUE(comp > 0);
}

TEST(VectorInteger, CompareNegTenNegSixTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-6);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-6);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
    EXPECT_TRUE(comp < 0);
}

TEST(VectorInteger, CompareTenNegTenTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-10);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
    EXPECT_TRUE(comp > 0);
}

TEST(VectorInteger, CompareNegTenTenTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(10);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
    EXPECT_TRUE(comp < 0);
}

TEST(VectorInteger, AddZeroZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddZeroFiveTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddFiveZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddFourFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(8);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(4);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddFiveFiveTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddTenTenTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(20);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(10);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, Add57_66Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(57);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(123);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddZeroNegFiveTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-5);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddNegFiveZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddFourNegFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddNegFourNegFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-8);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddNegFiveNegFiveTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-5);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, AddNegTenNegTenTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-20);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-10);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, Add67_Neg56Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(67);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-56);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(11);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-56);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, SubtractZeroZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, SubtractFiveZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, SubtractFourFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(4);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, SubtractTenTenTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(10);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, Subtract77_66Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(11);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, Subtract77_6Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(6);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(71);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(6);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, Subtract71_66Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(71);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, Subtract3_4Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(3);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(4);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, SubtractNegFiveZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, SubtractFourNegFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(8);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, SubtractNegFourNegFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, Subtract77_Neg66Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(143);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-66);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, SubtractNeg77_66Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-143);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(VectorInteger, Subtract1_2Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(2);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(2);

    std::unique_ptr<integer_impl> dummy = std::make_unique<bigint_type>();
    std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}
