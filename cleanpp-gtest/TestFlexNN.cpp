#include <gtest/gtest.h>

#include <stdio.h>
#include <sstream>
#include <natural_number.hpp>
#include <nn_impl/bounded_nn.hpp>
#include <nn_impl/stack_nn.hpp>
#include "../src/clean_nn/natural_number.cpp"

using namespace cleanpp;

typedef bounded_nn nn_type;
typedef stack_nn nn_type2;

static std::string nnToString(natural_number& o) {
	std::stringstream s;
	s << o;
	return s.str();
}

TEST(FlexNN, InitializerDefTest) {
	natural_number n(nn_type{});

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n_str == "0");
}

TEST(FlexNN, Initializer_SingleDigTest) {
	natural_number n(nn_type{}, 4);

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n_str == "4");
}

TEST(FlexNN, Initializer_TwoDigTest) {
	natural_number n(nn_type{}, 45);

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n_str == "45");
}

TEST(FlexNN, AssignZeroZeroTest) {
	natural_number n(nn_type{});
	natural_number m(nn_type{});
	natural_number expected(nn_type{});

	n = std::move(m);

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, AssignZeroNonzeroTest) {
	natural_number n(nn_type{});
	natural_number m(nn_type{}, 5);
	natural_number n_expected(nn_type{}, 5);
	natural_number m_expected(nn_type{}, 0);

	n = std::move(m);

	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	EXPECT_TRUE(n == n_expected);
	EXPECT_TRUE(m == m_expected);
}

TEST(FlexNN, AssignNonzeroZeroTest) {
	natural_number n(nn_type{}, 5);
	natural_number m(nn_type{});
	natural_number n_expected(nn_type{});
	natural_number m_expected(nn_type{});

	n = std::move(m);

	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	EXPECT_TRUE(n == n_expected);
	EXPECT_TRUE(m == m_expected);
}

TEST(FlexNN, AssignNonzeroNonzeroTest) {
	natural_number n(nn_type{}, 9);
	natural_number m(nn_type{}, 5);
	natural_number n_expected(nn_type{}, 5);
	natural_number m_expected(nn_type{}, 0);

	n = std::move(m);

	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	EXPECT_TRUE(n == n_expected);
	EXPECT_TRUE(m == m_expected);
}

TEST(FlexNN, AssignMultidigMultidigTest) {
	natural_number n(nn_type{}, 96);
	natural_number m(nn_type{}, 43);
	natural_number n_expected(nn_type{}, 43);
	natural_number m_expected(nn_type{}, 0);

	n = std::move(m);

	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	EXPECT_TRUE(n == n_expected);
	EXPECT_TRUE(m == m_expected);
}


TEST(FlexNN, AssignZeroZeroMultiImplTest) {
	natural_number n(nn_type{});
	natural_number m(nn_type2{});
	natural_number expected(nn_type{});

	n = std::move(m);

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, AssignZeroNonzeroMultiImplTest) {
	natural_number n(nn_type{});
	natural_number m(nn_type2{}, 5);
	natural_number n_expected(nn_type2{}, 5);
	natural_number m_expected(nn_type{}, 0);

	n = std::move(m);

	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	EXPECT_TRUE(n == n_expected);
	EXPECT_TRUE(m == m_expected);
}

TEST(FlexNN, AssignNonzeroZeroMultiImplTest) {
	natural_number n(nn_type2{}, 5);
	natural_number m(nn_type{});
	natural_number n_expected(nn_type2{});
	natural_number m_expected(nn_type{});

	n = std::move(m);

	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	EXPECT_TRUE(n == n_expected);
	EXPECT_TRUE(m == m_expected);
}

TEST(FlexNN, AssignNonzeroNonzeroMultiImplTest) {
	natural_number n(nn_type2{}, 9);
	natural_number m(nn_type{}, 5);
	natural_number n_expected(nn_type2{}, 5);
	natural_number m_expected(nn_type{}, 0);

	n = std::move(m);

	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	EXPECT_TRUE(n == n_expected);
	EXPECT_TRUE(m == m_expected);
}

TEST(FlexNN, AssignMultidigMultidigMultiImplTest) {
	natural_number n(nn_type2{}, 96);
	natural_number m(nn_type{}, 43);
	natural_number n_expected(nn_type2{}, 43);
	natural_number m_expected(nn_type{}, 0);

	n = std::move(m);

	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	EXPECT_TRUE(n == n_expected);
	EXPECT_TRUE(m == m_expected);
}


TEST(FlexNN, ClearZeroTest) {
	natural_number n(nn_type{});
	natural_number expected(nn_type{}, 0);

	n.clear();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, ClearNonZeroTest) {
	natural_number n(nn_type{}, 47);
	natural_number expected(nn_type{}, 0);

	n.clear();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, IncrementZeroTest) {
	natural_number n(nn_type{});
	natural_number expected(nn_type{}, 1);

	n.increment();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, IncrementNineTest) {
	natural_number n(nn_type{}, 9);
	natural_number expected(nn_type{}, 10);

	n.increment();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, IncrementFiveTest) {
	natural_number n(nn_type{}, 5);
	natural_number expected(nn_type{}, 6);

	n.increment();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, DecrementOneTest) {
	natural_number n(nn_type{}, 1);
	natural_number expected(nn_type{}, 0);

	n.decrement();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, DecrementTenTest) {
	natural_number n(nn_type{}, 10);
	natural_number expected(nn_type{}, 9);

	n.decrement();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, DecrementFiveTest) {
	natural_number n(nn_type{}, 5);
	natural_number expected(nn_type{}, 4);

	n.decrement();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, MultRadZero_ZeroTest) {
	natural_number n(nn_type{}, 0);
	natural_number expected(nn_type{}, 0);

	n.multiply_by_radix(0);

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, MultRadZero_FiveTest) {
	natural_number n(nn_type{}, 0);
	natural_number expected(nn_type{}, 5);

	n.multiply_by_radix(5);

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, MultRadFive_ZeroTest) {
	natural_number n(nn_type{}, 5);
	natural_number expected(nn_type{}, 50);

	n.multiply_by_radix(0);

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, MultRadFive_FiveTest) {
	natural_number n(nn_type{}, 5);
	natural_number expected(nn_type{}, 55);

	n.multiply_by_radix(5);

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
}

TEST(FlexNN, DivRadZeroTest) {
	natural_number n(nn_type{}, 0);
	natural_number expected(nn_type{}, 0);

	int d = 4;
	d = n.divide_by_radix();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
	EXPECT_TRUE(d == 0);
}

TEST(FlexNN, DivRadFiveTest) {
	natural_number n(nn_type{}, 5);
	natural_number expected(nn_type{}, 0);

	int d = 4;
	d = n.divide_by_radix();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
	EXPECT_TRUE(d == 5);
}

TEST(FlexNN, DiveRadFiftyTest) {
	natural_number n(nn_type{}, 50);
	natural_number expected(nn_type{}, 5);

	int d = 4;
	d = n.divide_by_radix();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
	EXPECT_TRUE(d == 0);
}

TEST(FlexNN, DivRadFiftyFiveTest) {
	natural_number n(nn_type{}, 55);
	natural_number expected(nn_type{}, 5);

	int d = 4;
	d = n.divide_by_radix();
	// vs. d = n.divide_by_radix()
	// d = n.get_last_digit(); n = n.divide_by_radix();

	std::string n_str = nnToString(n);
	EXPECT_TRUE(n == expected);
	EXPECT_TRUE(d == 5);
}

TEST(FlexNN, AddZeroZeroTest) {
	natural_number n1(nn_type{});
	natural_number n2(nn_type{});
	natural_number n1_exp(nn_type{});
	natural_number n2_exp(nn_type{});
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, AddZeroFiveTest) {
	natural_number n1(nn_type{}, 0);
	natural_number n2(nn_type{}, 5);
	natural_number n1_exp(nn_type{}, 5);
	natural_number n2_exp(nn_type{}, 5);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, AddFiveZeroTest) {
	natural_number n1(nn_type{}, 5);
	natural_number n2(nn_type{}, 0);
	natural_number n1_exp(nn_type{}, 5);
	natural_number n2_exp(nn_type{}, 0);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, AddFourFourTest) {
	natural_number n1(nn_type{}, 4);
	natural_number n2(nn_type{}, 4);
	natural_number n1_exp(nn_type{}, 8);
	natural_number n2_exp(nn_type{}, 4);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, AddFiveFiveTest) {
	natural_number n1(nn_type{}, 5);
	natural_number n2(nn_type{}, 5);
	natural_number n1_exp(nn_type{}, 10);
	natural_number n2_exp(nn_type{}, 5);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, AddTenTenTest) {
	natural_number n1(nn_type{}, 10);
	natural_number n2(nn_type{}, 10);
	natural_number n1_exp(nn_type{}, 20);
	natural_number n2_exp(nn_type{}, 10);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, Add57_66Test) {
	natural_number n1(nn_type{}, 57);
	natural_number n2(nn_type{}, 66);
	natural_number n1_exp(nn_type{}, 123);
	natural_number n2_exp(nn_type{}, 66);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = add(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, SubtractZeroZeroTest) {
	natural_number n1(nn_type{});
	natural_number n2(nn_type{});
	natural_number n1_exp(nn_type{});
	natural_number n2_exp(nn_type{});
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, SubtractFiveZeroTest) {
	natural_number n1(nn_type{}, 5);
	natural_number n2(nn_type{}, 0);
	natural_number n1_exp(nn_type{}, 5);
	natural_number n2_exp(nn_type{}, 0);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, SubtractFourFourTest) {
	natural_number n1(nn_type{}, 4);
	natural_number n2(nn_type{}, 4);
	natural_number n1_exp(nn_type{}, 0);
	natural_number n2_exp(nn_type{}, 4);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, SubtractTenTenTest) {
	natural_number n1(nn_type{}, 10);
	natural_number n2(nn_type{}, 10);
	natural_number n1_exp(nn_type{}, 0);
	natural_number n2_exp(nn_type{}, 10);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, Subtract77_66Test) {
	natural_number n1(nn_type{}, 77);
	natural_number n2(nn_type{}, 66);
	natural_number n1_exp(nn_type{}, 11);
	natural_number n2_exp(nn_type{}, 66);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, Subtract77_6Test) {
	natural_number n1(nn_type{}, 77);
	natural_number n2(nn_type{}, 6);
	natural_number n1_exp(nn_type{}, 71);
	natural_number n2_exp(nn_type{}, 6);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, Subtract71_66Test) {
	natural_number n1(nn_type{}, 71);
	natural_number n2(nn_type{}, 66);
	natural_number n1_exp(nn_type{}, 5);
	natural_number n2_exp(nn_type{}, 66);
	
	natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = subtract(std::move(n1), std::move(n2));
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, MultiplyZeroZeroTest) {
    natural_number n1(nn_type{});
    natural_number n2(nn_type{});
    natural_number n1_exp(nn_type{});
    natural_number n2_exp(nn_type{});
    
    natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = multiply(std::move(n1), std::move(n2));

	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, MultiplyFiveZeroTest) {
    natural_number n1(nn_type{}, 5);
    natural_number n2(nn_type{});
    natural_number n1_exp(nn_type{}, 0);
    natural_number n2_exp(nn_type{});
    
    natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = multiply(std::move(n1), std::move(n2));

	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, MultiplyFourFourTest) {
    natural_number n1(nn_type{}, 4);
    natural_number n2(nn_type{}, 4);
    natural_number n1_exp(nn_type{}, 16);
    natural_number n2_exp(nn_type{}, 4);
    
    natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = multiply(std::move(n1), std::move(n2));

	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	EXPECT_TRUE(n1 == n1_exp);
	EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, MultiplyTenTenTest) {
    natural_number n1(nn_type{}, 10);
    natural_number n2(nn_type{}, 10);
    natural_number n1_exp(nn_type{}, 100);
    natural_number n2_exp(nn_type{}, 10);
    
    natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, Multiply77_66Test){
    natural_number n1(nn_type{}, 77);
    natural_number n2(nn_type{}, 66);
    natural_number n1_exp(nn_type{}, 5082);
    natural_number n2_exp(nn_type{}, 66);
    
    natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, Multiply77_6Test){
    natural_number n1(nn_type{}, 77);
    natural_number n2(nn_type{}, 6);
    natural_number n1_exp(nn_type{}, 462);
    natural_number n2_exp(nn_type{}, 6);
    
    natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}

TEST(FlexNN, Multiply71_66Test){
    natural_number n1(nn_type{}, 71);
    natural_number n2(nn_type{}, 66);
    natural_number n1_exp(nn_type{}, 4686);
    natural_number n2_exp(nn_type{}, 66);
    
    natural_number dummy(nn_type{});
	std::tie(n1, dummy, n2) = multiply(std::move(n1), std::move(n2));

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    EXPECT_TRUE(n1 == n1_exp);
    EXPECT_TRUE(n2 == n2_exp);
}
