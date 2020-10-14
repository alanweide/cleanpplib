//
//  TestFlexNN.m
//  TestFlexNN
//
//  Created by Alan Weide on 07/23/2020.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <stdio.h>
#include <sstream>
#include <flexible_nn/flexible_nn.hpp>
#include <clean_nn/bounded_nn.hpp>
#include <clean_nn/stack_nn.hpp>

@interface TestFlexNN: XCTestCase
@end

@implementation TestFlexNN

using namespace cleanpp;

typedef bounded_nn nn_type;
typedef stack_nn nn_type2;

static std::string nnToString(flex_natural_number &o) {
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
	flex_natural_number n(nn_type{});
	
	std::string n_str = nnToString(n);
	XCTAssert(n_str == "0");
}

- (void)testInitializer_SingleDig {
	flex_natural_number n(nn_type{}, 4);
	
	std::string n_str = nnToString(n);
	XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
}

- (void)testInitializer_TwoDig {
	flex_natural_number n(nn_type{}, 45);
	
	std::string n_str = nnToString(n);
	XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
}

- (void)testAssignZeroZero {
    flex_natural_number n(nn_type{});
    flex_natural_number m(nn_type{});
    flex_natural_number expected(nn_type{});
    
    n = std::move(m);
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testAssignZeroNonzero {
	flex_natural_number n(nn_type{});
	flex_natural_number m(nn_type{}, 5);
	flex_natural_number n_expected(nn_type{}, 5);
	flex_natural_number m_expected(nn_type{}, 0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignNonzeroZero {
	flex_natural_number n(nn_type{}, 5);
	flex_natural_number m(nn_type{});
	flex_natural_number n_expected(nn_type{});
	flex_natural_number m_expected(nn_type{});
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignNonzeroNonzero {
	flex_natural_number n(nn_type{}, 9);
	flex_natural_number m(nn_type{}, 5);
	flex_natural_number n_expected(nn_type{}, 5);
	flex_natural_number m_expected(nn_type{}, 0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignMultidigMultidig {
    flex_natural_number n(nn_type{}, 96);
    flex_natural_number m(nn_type{}, 43);
    flex_natural_number n_expected(nn_type{}, 43);
    flex_natural_number m_expected(nn_type{}, 0);
    
    n = std::move(m);
    
    std::string n_str = nnToString(n);
    std::string m_str = nnToString(m);
    XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
    XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}


- (void)testAssignZeroZeroMultiImpl {
	flex_natural_number n(nn_type{});
	flex_natural_number m(nn_type2{});
	flex_natural_number expected(nn_type{});
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testAssignZeroNonzeroMultiImpl {
	flex_natural_number n(nn_type{});
	flex_natural_number m(nn_type2{}, 5);
	flex_natural_number n_expected(nn_type2{}, 5);
	flex_natural_number m_expected(nn_type{}, 0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignNonzeroZeroMultiImpl {
	flex_natural_number n(nn_type2{}, 5);
	flex_natural_number m(nn_type{});
	flex_natural_number n_expected(nn_type2{});
	flex_natural_number m_expected(nn_type{});
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignNonzeroNonzeroMultiImpl {
	flex_natural_number n(nn_type2{}, 9);
	flex_natural_number m(nn_type{}, 5);
	flex_natural_number n_expected(nn_type2{}, 5);
	flex_natural_number m_expected(nn_type{}, 0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignMultidigMultidigMultiImpl {
	flex_natural_number n(nn_type2{}, 96);
	flex_natural_number m(nn_type{}, 43);
	flex_natural_number n_expected(nn_type2{}, 43);
	flex_natural_number m_expected(nn_type{}, 0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}


- (void)testClearZero {
	flex_natural_number n(nn_type{});
	flex_natural_number expected(nn_type{}, 0);
	
	n.clear();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testClearNonZero {
	flex_natural_number n(nn_type{}, 47);
	flex_natural_number expected(nn_type{}, 0);
	
	n.clear();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
	flex_natural_number n(nn_type{});
	flex_natural_number expected(nn_type{}, 1);
	
	n.increment();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
	flex_natural_number n(nn_type{}, 9);
	flex_natural_number expected(nn_type{}, 10);
	
	n.increment();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
	flex_natural_number n(nn_type{}, 5);
	flex_natural_number expected(nn_type{}, 6);
	
	n.increment();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
	flex_natural_number n(nn_type{}, 1);
	flex_natural_number expected(nn_type{}, 0);
	
	n.decrement();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
	flex_natural_number n(nn_type{}, 10);
	flex_natural_number expected(nn_type{}, 9);
	
	n.decrement();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
	flex_natural_number n(nn_type{}, 5);
	flex_natural_number expected(nn_type{}, 4);
	
	n.decrement();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
	flex_natural_number n(nn_type{}, 0);
	flex_natural_number expected(nn_type{}, 0);
	
	n.multiply_by_radix(0);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
	flex_natural_number n(nn_type{}, 0);
	flex_natural_number expected(nn_type{}, 5);
	
	n.multiply_by_radix(5);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
	flex_natural_number n(nn_type{}, 5);
	flex_natural_number expected(nn_type{}, 50);
	
	n.multiply_by_radix(0);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
	flex_natural_number n(nn_type{}, 5);
	flex_natural_number expected(nn_type{}, 55);
	
	n.multiply_by_radix(5);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
	flex_natural_number n(nn_type{}, 0);
	flex_natural_number expected(nn_type{}, 0);
	
	int d = 4;
	d = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadFive {
	flex_natural_number n(nn_type{}, 5);
	flex_natural_number expected(nn_type{}, 0);
	
	int d = 4;
	d = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
	flex_natural_number n(nn_type{}, 50);
	flex_natural_number expected(nn_type{}, 5);
	
	int d = 4;
	d = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
	flex_natural_number n(nn_type{}, 55);
	flex_natural_number expected(nn_type{}, 5);
	
	int d = 4;
	d = n.divide_by_radix();
	// vs. d = n.divide_by_radix()
	// d = n.get_last_digit(); n = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testAddZeroZero {
	flex_natural_number n1(nn_type{});
	flex_natural_number n2(nn_type{});
	flex_natural_number n1_exp(nn_type{});
	flex_natural_number n2_exp(nn_type{});
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroFive {
	flex_natural_number n1(nn_type{}, 0);
	flex_natural_number n2(nn_type{}, 5);
	flex_natural_number n1_exp(nn_type{}, 5);
	flex_natural_number n2_exp(nn_type{}, 5);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
	flex_natural_number n1(nn_type{}, 5);
	flex_natural_number n2(nn_type{}, 0);
	flex_natural_number n1_exp(nn_type{}, 5);
	flex_natural_number n2_exp(nn_type{}, 0);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourFour {
	flex_natural_number n1(nn_type{}, 4);
	flex_natural_number n2(nn_type{}, 4);
	flex_natural_number n1_exp(nn_type{}, 8);
	flex_natural_number n2_exp(nn_type{}, 4);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveFive {
	flex_natural_number n1(nn_type{}, 5);
	flex_natural_number n2(nn_type{}, 5);
	flex_natural_number n1_exp(nn_type{}, 10);
	flex_natural_number n2_exp(nn_type{}, 5);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddTenTen {
	flex_natural_number n1(nn_type{}, 10);
	flex_natural_number n2(nn_type{}, 10);
	flex_natural_number n1_exp(nn_type{}, 20);
	flex_natural_number n2_exp(nn_type{}, 10);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_66{
	flex_natural_number n1(nn_type{}, 57);
	flex_natural_number n2(nn_type{}, 66);
	flex_natural_number n1_exp(nn_type{}, 123);
	flex_natural_number n2_exp(nn_type{}, 66);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractZeroZero {
	flex_natural_number n1(nn_type{});
	flex_natural_number n2(nn_type{});
	flex_natural_number n1_exp(nn_type{});
	flex_natural_number n2_exp(nn_type{});
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFiveZero {
	flex_natural_number n1(nn_type{}, 5);
	flex_natural_number n2(nn_type{}, 0);
	flex_natural_number n1_exp(nn_type{}, 5);
	flex_natural_number n2_exp(nn_type{}, 0);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourFour {
	flex_natural_number n1(nn_type{}, 4);
	flex_natural_number n2(nn_type{}, 4);
	flex_natural_number n1_exp(nn_type{}, 0);
	flex_natural_number n2_exp(nn_type{}, 4);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractTenTen {
	flex_natural_number n1(nn_type{}, 10);
	flex_natural_number n2(nn_type{}, 10);
	flex_natural_number n1_exp(nn_type{}, 0);
	flex_natural_number n2_exp(nn_type{}, 10);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_66{
	flex_natural_number n1(nn_type{}, 77);
	flex_natural_number n2(nn_type{}, 66);
	flex_natural_number n1_exp(nn_type{}, 11);
	flex_natural_number n2_exp(nn_type{}, 66);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_6{
	flex_natural_number n1(nn_type{}, 77);
	flex_natural_number n2(nn_type{}, 6);
	flex_natural_number n1_exp(nn_type{}, 71);
	flex_natural_number n2_exp(nn_type{}, 6);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract71_66{
	flex_natural_number n1(nn_type{}, 71);
	flex_natural_number n2(nn_type{}, 66);
	flex_natural_number n1_exp(nn_type{}, 5);
	flex_natural_number n2_exp(nn_type{}, 66);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyZeroZero {
    flex_natural_number n1(nn_type{});
    flex_natural_number n2(nn_type{});
    flex_natural_number n1_exp(nn_type{});
    flex_natural_number n2_exp(nn_type{});
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyFiveZero {
    flex_natural_number n1(nn_type{}, 5);
    flex_natural_number n2(nn_type{});
    flex_natural_number n1_exp(nn_type{}, 0);
    flex_natural_number n2_exp(nn_type{});
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyFourFour {
    flex_natural_number n1(nn_type{}, 4);
    flex_natural_number n2(nn_type{}, 4);
    flex_natural_number n1_exp(nn_type{}, 16);
    flex_natural_number n2_exp(nn_type{}, 4);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyTenTen {
    flex_natural_number n1(nn_type{}, 10);
    flex_natural_number n2(nn_type{}, 10);
    flex_natural_number n1_exp(nn_type{}, 100);
    flex_natural_number n2_exp(nn_type{}, 10);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiply77_66{
    flex_natural_number n1(nn_type{}, 77);
    flex_natural_number n2(nn_type{}, 66);
    flex_natural_number n1_exp(nn_type{}, 5082);
    flex_natural_number n2_exp(nn_type{}, 66);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiply77_6{
    flex_natural_number n1(nn_type{}, 77);
    flex_natural_number n2(nn_type{}, 6);
    flex_natural_number n1_exp(nn_type{}, 462);
    flex_natural_number n2_exp(nn_type{}, 6);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiply71_66{
    flex_natural_number n1(nn_type{}, 71);
    flex_natural_number n2(nn_type{}, 66);
    flex_natural_number n1_exp(nn_type{}, 4686);
    flex_natural_number n2_exp(nn_type{}, 66);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

@end
