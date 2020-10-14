//
//  TestTemplateNN.m
//  TestTemplateNN
//
//  Created by Alan Weide on 07/23/2020.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <stdio.h>
#include <sstream>
#include <template_nn/template_nn.hpp>
#include <clean_nn/bounded_nn.hpp>
#include <clean_nn/stack_nn.hpp>

@interface TestTemplateNN: XCTestCase
@end

@implementation TestTemplateNN

using namespace cleanpp;

typedef bounded_nn nn_type;
typedef stack_nn nn_type2;

typedef t_natural_number<nn_type> template_t;
typedef t_natural_number<nn_type2> template_t2;

template<class I>
static std::string nnToString(t_natural_number<I> &o) {
	std::stringstream s;
	s << o;
	return s.str();
}

- (void)setUp {
	// Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
	// Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testInitializerDef {
	t_natural_number<nn_type> n;
	
	std::string n_str = nnToString(n);
	XCTAssert(n_str == "0");
}

- (void)testInitializer_SingleDig {
	t_natural_number<nn_type> n(4);
	
	std::string n_str = nnToString(n);
	XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
}

- (void)testInitializer_TwoDig {
	t_natural_number<nn_type> n(45);
	
	std::string n_str = nnToString(n);
	XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
}

- (void)testAssignZeroZero {
    t_natural_number<nn_type> n;
    t_natural_number<nn_type> m;
    t_natural_number<nn_type> expected;
    
    n = std::move(m);
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testAssignZeroNonzero {
	t_natural_number<nn_type> n;
	t_natural_number<nn_type> m(5);
	t_natural_number<nn_type> n_expected(5);
	t_natural_number<nn_type> m_expected(0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignNonzeroZero {
	t_natural_number<nn_type> n(5);
	t_natural_number<nn_type> m;
	t_natural_number<nn_type> n_expected;
	t_natural_number<nn_type> m_expected;
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignNonzeroNonzero {
	t_natural_number<nn_type> n(9);
	t_natural_number<nn_type> m(5);
	t_natural_number<nn_type> n_expected(5);
	t_natural_number<nn_type> m_expected(0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignMultidigMultidig {
    t_natural_number<nn_type> n(96);
    t_natural_number<nn_type> m(43);
    t_natural_number<nn_type> n_expected(43);
    t_natural_number<nn_type> m_expected(0);
    
    n = std::move(m);
    
    std::string n_str = nnToString(n);
    std::string m_str = nnToString(m);
    XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
    XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testClearZero {
	t_natural_number<nn_type> n;
	t_natural_number<nn_type> expected(0);
	
	n.clear();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testClearNonZero {
	t_natural_number<nn_type> n(47);
	t_natural_number<nn_type> expected(0);
	
	n.clear();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
	t_natural_number<nn_type> n;
	t_natural_number<nn_type> expected(1);
	
	n.increment();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
	t_natural_number<nn_type> n(9);
	t_natural_number<nn_type> expected(10);
	
	n.increment();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
	t_natural_number<nn_type> n(5);
	t_natural_number<nn_type> expected(6);
	
	n.increment();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
	t_natural_number<nn_type> n(1);
	t_natural_number<nn_type> expected(0);
	
	n.decrement();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
	t_natural_number<nn_type> n(10);
	t_natural_number<nn_type> expected(9);
	
	n.decrement();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
	t_natural_number<nn_type> n(5);
	t_natural_number<nn_type> expected(4);
	
	n.decrement();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
	t_natural_number<nn_type> n(0);
	t_natural_number<nn_type> expected(0);
	
	n.multiply_by_radix(0);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
	t_natural_number<nn_type> n(0);
	t_natural_number<nn_type> expected(5);
	
	n.multiply_by_radix(5);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
	t_natural_number<nn_type> n(5);
	t_natural_number<nn_type> expected(50);
	
	n.multiply_by_radix(0);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
	t_natural_number<nn_type> n(5);
	t_natural_number<nn_type> expected(55);
	
	n.multiply_by_radix(5);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
	t_natural_number<nn_type> n(0);
	t_natural_number<nn_type> expected(0);
	
	int d = 4;
	d = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadFive {
	template_t n(5);
	template_t expected(0);
	
	int d = 4;
	d = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
	template_t n(50);
	template_t expected(5);
	
	int d = 4;
	d = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
	template_t n(55);
	template_t expected(5);
	
	int d = 4;
	d = n.divide_by_radix();
	// vs. d = n.divide_by_radix()
	// d = n.get_last_digit(); n = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testAddZeroZero {
	template_t n1;
	template_t n2;
	template_t n1_exp;
	template_t n2_exp;
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroFive {
	template_t n1(0);
	template_t n2(5);
	template_t n1_exp(5);
	template_t n2_exp(5);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
    t_natural_number<nn_type> n1(5);
    t_natural_number<nn_type> n2(0);
    t_natural_number<nn_type> n1_exp(5);
    t_natural_number<nn_type> n2_exp(0);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourFour {
	template_t n1(4);
	template_t n2(4);
	template_t n1_exp(8);
	template_t n2_exp(4);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveFive {
	template_t n1(5);
	template_t n2(5);
	template_t n1_exp(10);
	template_t n2_exp(5);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddTenTen {
	template_t n1(10);
	template_t n2(10);
	template_t n1_exp(20);
	template_t n2_exp(10);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_66{
	template_t n1(57);
	template_t n2(66);
	template_t n1_exp(123);
	template_t n2_exp(66);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractZeroZero {
	template_t n1;
	template_t n2;
	template_t n1_exp;
	template_t n2_exp;
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFiveZero {
	template_t n1(5);
	template_t n2(0);
	template_t n1_exp(5);
	template_t n2_exp(0);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourFour {
	template_t n1(4);
	template_t n2(4);
	template_t n1_exp(0);
	template_t n2_exp(4);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractTenTen {
	template_t n1(10);
	template_t n2(10);
	template_t n1_exp(0);
	template_t n2_exp(10);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_66{
	template_t n1(77);
	template_t n2(66);
	template_t n1_exp(11);
	template_t n2_exp(66);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_6{
	template_t n1(77);
	template_t n2(6);
	template_t n1_exp(71);
	template_t n2_exp(6);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract71_66{
	template_t n1(71);
	template_t n2(66);
	template_t n1_exp(5);
	template_t n2_exp(66);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}


- (void)testMultiplyZeroZero {
    template_t n1;
    template_t n2;
    template_t n1_exp;
    template_t n2_exp;
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyFiveZero {
    template_t n1(5);
    template_t n2;
    template_t n1_exp(0);
    template_t n2_exp;
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyFourFour {
    template_t n1(4);
    template_t n2(4);
    template_t n1_exp(16);
    template_t n2_exp(4);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyTenTen {
    template_t n1(10);
    template_t n2(10);
    template_t n1_exp(100);
    template_t n2_exp(10);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiply77_66{
    template_t n1(77);
    template_t n2(66);
    template_t n1_exp(5082);
    template_t n2_exp(66);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiply77_6{
    template_t n1(77);
    template_t n2(6);
    template_t n1_exp(462);
    template_t n2_exp(6);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiply71_66{
    template_t n1(71);
    template_t n2(66);
    template_t n1_exp(4686);
    template_t n2_exp(66);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

@end
