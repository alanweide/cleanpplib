#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <integer_impls/nn_integer.hpp>

using namespace cleanpp;

typedef nn_integer bigint_type;

static std::string bigintToString(std::unique_ptr<integer_impl> &o) {
	std::stringstream s;
    s << *o;
    return s.str();
}

TEST(NNInteger, InitializerDefTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "0");
    EXPECT_TRUE(n->sign() == ZERO);
}

TEST(NNInteger, Initializer_SingleDigTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(4);
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "4");
    EXPECT_TRUE(n->sign() == POSITIVE);
}

TEST(NNInteger, Initializer_TwoDigTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(45);
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(n_str == "45");
    EXPECT_TRUE(n->sign() == POSITIVE);
}


TEST(NNInteger, Initializer_SingleDigNegTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-4);
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(n_str == "-4");
    EXPECT_TRUE(n->sign() == NEGATIVE);
}

TEST(NNInteger, Initializer_TwoDigNegTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-45);
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(n_str == "-45");
    EXPECT_TRUE(n->sign() == NEGATIVE);
}

TEST(NNInteger, ClearZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
    
    n->clear();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, ClearPositiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(47);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
    
    n->clear();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, ClearNegativeTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-47);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
	
	n->clear();
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, IncrementZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(1);
    
    n->increment();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, IncrementNineTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(9);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(10);
    
    n->increment();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, IncrementFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(6);
    
    n->increment();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, IncrementNegTenTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-10);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-9);
	
	n->increment();
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, IncrementNegFiveTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-4);
	
	n->increment();
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, IncrementNegOneTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-1);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
	
	n->increment();
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, DecrementOneTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
    
    n->decrement();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, DecrementTenTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(9);
    
    n->decrement();

    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, DecrementFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(4);
    
    n->decrement();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, DecrementZeroTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-1);
	
	n->decrement();
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, DecrementNegNineTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-9);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-10);
	
	n->decrement();
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, DecrementNegFiveTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-6);
	
	n->decrement();
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, MultRadZero_ZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
    
    n->multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, MultRadZero_FiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(5);

    n->multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, MultRadFive_ZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(50);

    n->multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, MultRadFive_FiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(55);

    n->multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, MultRadNegFive_ZeroTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-50);
	
	n->multiply_by_radix(0);
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, MultRadNegFive_FiveTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-55);
	
	n->multiply_by_radix(5);
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
}

TEST(NNInteger, DivRadZeroTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 0);
}

TEST(NNInteger, DivRadFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 5);
}

TEST(NNInteger, DiveRadFiftyTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(50);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(5);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 0);
}

TEST(NNInteger, DivRadFiftyFiveTest) {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(55);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(5);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = bigintToString(n);
    EXPECT_TRUE(*n == *expected);
    EXPECT_TRUE(d == 5);
}

TEST(NNInteger, DivRadNegFiveTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
	
	int d = 4;
	d = n->divide_by_radix();
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
	EXPECT_TRUE(d == 5);
}

TEST(NNInteger, DiveRadNegFiftyTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-50);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-5);
	
	int d = 4;
	d = n->divide_by_radix();
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
	EXPECT_TRUE(d == 0);
}

TEST(NNInteger, DivRadNegFiftyFiveTest) {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-55);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-5);
	
	int d = 4;
	d = n->divide_by_radix();
	
	std::string n_str = bigintToString(n);
	EXPECT_TRUE(*n == *expected);
	EXPECT_TRUE(d == 5);
}

TEST(NNInteger, CloneFromZeroTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, CloneFromOneTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(1);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, CloneFromThreeTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(3);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(3);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(3);

    n = n2->clone();
    
    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, CloneFromFiveTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, CloneFrom25Test) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(25);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(25);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(25);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, CloneFromNegOneTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-1);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, CloneFromNegThreeTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-3);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-3);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-3);

    n = n2->clone();
    
    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, CloneFromNegFiveTest) {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-5);

    n = n2->clone();

    EXPECT_TRUE(*n == *n_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, CloneFromNeg25Test) {
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

TEST(NNInteger, CompareZeroZeroTest) {
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

TEST(NNInteger, CompareZeroOneTest) {
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

TEST(NNInteger, CompareOneZeroTest) {
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

TEST(NNInteger, CompareFiveTwoTest) {
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

TEST(NNInteger, CompareFiveNeg4Test) {
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

TEST(NNInteger, CompareNegFourFiveTest) {
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

TEST(NNInteger, CompareTenSixTest) {
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

TEST(NNInteger, CompareNegTenNegSixTest) {
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

TEST(NNInteger, CompareTenNegTenTest) {
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

TEST(NNInteger, CompareNegTenTenTest) {
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

TEST(NNInteger, AddZeroZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddZeroFiveTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddFiveZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddFourFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(8);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddFiveFiveTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddTenTenTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(20);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(10);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, Add57_66Test){
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(57);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(123);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddZeroNegFiveTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddNegFiveZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddFourNegFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddNegFourNegFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-8);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddNegFiveNegFiveTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, AddNegTenNegTenTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-20);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-10);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, Add57_Neg66Test){
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(67);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-56);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(11);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-56);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, SubtractZeroZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, SubtractFiveZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, SubtractFourFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, SubtractTenTenTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(10);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, Subtract77_66Test){
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(11);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, Subtract77_6Test){
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(6);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(71);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(6);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, Subtract71_66Test){
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(71);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, Subtract3_4Test) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(3);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, SubtractNegFiveZeroTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, SubtractFourNegFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(8);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, SubtractNegFourNegFourTest) {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, Subtract77_Neg66Test){
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(143);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, SubtractNeg77_66Test){
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-143);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}

TEST(NNInteger, Subtract1_2Test){
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(2);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(2);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    EXPECT_TRUE(*n1 == *n1_exp);
    EXPECT_TRUE(*n2 == *n2_exp);
}
