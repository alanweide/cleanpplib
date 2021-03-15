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
#include <clean_nn/natural_number.hpp>
#include <natural_number_impls/bounded_nn.hpp>
#include <natural_number_impls/stack_nn.hpp>

@interface TestFlexNN: XCTestCase
@end

@implementation TestFlexNN

using namespace cleanpp;

typedef bounded_nn nn_type;
typedef stack_nn nn_type2;

static std::string nnToString(natural_number &o) {
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
	natural_number n(nn_type{});
	
	std::string n_str = nnToString(n);
	XCTAssert(n_str == "0");
}

- (void)testInitializer_SingleDig {
	natural_number n(nn_type{}, 4);
	
	std::string n_str = nnToString(n);
	XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
}

- (void)testInitializer_TwoDig {
	natural_number n(nn_type{}, 45);
	
	std::string n_str = nnToString(n);
	XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
}

- (void)testAssignZeroZero {
    natural_number n(nn_type{});
    natural_number m(nn_type{});
    natural_number expected(nn_type{});
    
    n = std::move(m);
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testAssignZeroNonzero {
	natural_number n(nn_type{});
	natural_number m(nn_type{}, 5);
	natural_number n_expected(nn_type{}, 5);
	natural_number m_expected(nn_type{}, 0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignNonzeroZero {
	natural_number n(nn_type{}, 5);
	natural_number m(nn_type{});
	natural_number n_expected(nn_type{});
	natural_number m_expected(nn_type{});
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignNonzeroNonzero {
	natural_number n(nn_type{}, 9);
	natural_number m(nn_type{}, 5);
	natural_number n_expected(nn_type{}, 5);
	natural_number m_expected(nn_type{}, 0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignMultidigMultidig {
    natural_number n(nn_type{}, 96);
    natural_number m(nn_type{}, 43);
    natural_number n_expected(nn_type{}, 43);
    natural_number m_expected(nn_type{}, 0);
    
    n = std::move(m);
    
    std::string n_str = nnToString(n);
    std::string m_str = nnToString(m);
    XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
    XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}


- (void)testAssignZeroZeroMultiImpl {
	natural_number n(nn_type{});
	natural_number m(nn_type2{});
	natural_number expected(nn_type{});
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testAssignZeroNonzeroMultiImpl {
	natural_number n(nn_type{});
	natural_number m(nn_type2{}, 5);
	natural_number n_expected(nn_type2{}, 5);
	natural_number m_expected(nn_type{}, 0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignNonzeroZeroMultiImpl {
	natural_number n(nn_type2{}, 5);
	natural_number m(nn_type{});
	natural_number n_expected(nn_type2{});
	natural_number m_expected(nn_type{});
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignNonzeroNonzeroMultiImpl {
	natural_number n(nn_type2{}, 9);
	natural_number m(nn_type{}, 5);
	natural_number n_expected(nn_type2{}, 5);
	natural_number m_expected(nn_type{}, 0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}

- (void)testAssignMultidigMultidigMultiImpl {
	natural_number n(nn_type2{}, 96);
	natural_number m(nn_type{}, 43);
	natural_number n_expected(nn_type2{}, 43);
	natural_number m_expected(nn_type{}, 0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected, @"m = %s", m_str.c_str());
}


- (void)testClearZero {
	natural_number n(nn_type{});
	natural_number expected(nn_type{}, 0);
	
	n.clear();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testClearNonZero {
	natural_number n(nn_type{}, 47);
	natural_number expected(nn_type{}, 0);
	
	n.clear();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
	natural_number n(nn_type{});
	natural_number expected(nn_type{}, 1);
	
	n.increment();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
	natural_number n(nn_type{}, 9);
	natural_number expected(nn_type{}, 10);
	
	n.increment();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
	natural_number n(nn_type{}, 5);
	natural_number expected(nn_type{}, 6);
	
	n.increment();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
	natural_number n(nn_type{}, 1);
	natural_number expected(nn_type{}, 0);
	
	n.decrement();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
	natural_number n(nn_type{}, 10);
	natural_number expected(nn_type{}, 9);
	
	n.decrement();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
	natural_number n(nn_type{}, 5);
	natural_number expected(nn_type{}, 4);
	
	n.decrement();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
	natural_number n(nn_type{}, 0);
	natural_number expected(nn_type{}, 0);
	
	n.multiply_by_radix(0);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
	natural_number n(nn_type{}, 0);
	natural_number expected(nn_type{}, 5);
	
	n.multiply_by_radix(5);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
	natural_number n(nn_type{}, 5);
	natural_number expected(nn_type{}, 50);
	
	n.multiply_by_radix(0);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
	natural_number n(nn_type{}, 5);
	natural_number expected(nn_type{}, 55);
	
	n.multiply_by_radix(5);
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
	natural_number n(nn_type{}, 0);
	natural_number expected(nn_type{}, 0);
	
	int d = 4;
	d = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadFive {
	natural_number n(nn_type{}, 5);
	natural_number expected(nn_type{}, 0);
	
	int d = 4;
	d = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
	natural_number n(nn_type{}, 50);
	natural_number expected(nn_type{}, 5);
	
	int d = 4;
	d = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
	natural_number n(nn_type{}, 55);
	natural_number expected(nn_type{}, 5);
	
	int d = 4;
	d = n.divide_by_radix();
	// vs. d = n.divide_by_radix()
	// d = n.get_last_digit(); n = n.divide_by_radix();
	
	std::string n_str = nnToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testAddZeroZero {
	natural_number n1(nn_type{});
	natural_number n2(nn_type{});
	natural_number n1_exp(nn_type{});
	natural_number n2_exp(nn_type{});
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroFive {
	natural_number n1(nn_type{}, 0);
	natural_number n2(nn_type{}, 5);
	natural_number n1_exp(nn_type{}, 5);
	natural_number n2_exp(nn_type{}, 5);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
	natural_number n1(nn_type{}, 5);
	natural_number n2(nn_type{}, 0);
	natural_number n1_exp(nn_type{}, 5);
	natural_number n2_exp(nn_type{}, 0);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourFour {
	natural_number n1(nn_type{}, 4);
	natural_number n2(nn_type{}, 4);
	natural_number n1_exp(nn_type{}, 8);
	natural_number n2_exp(nn_type{}, 4);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveFive {
	natural_number n1(nn_type{}, 5);
	natural_number n2(nn_type{}, 5);
	natural_number n1_exp(nn_type{}, 10);
	natural_number n2_exp(nn_type{}, 5);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddTenTen {
	natural_number n1(nn_type{}, 10);
	natural_number n2(nn_type{}, 10);
	natural_number n1_exp(nn_type{}, 20);
	natural_number n2_exp(nn_type{}, 10);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_66{
	natural_number n1(nn_type{}, 57);
	natural_number n2(nn_type{}, 66);
	natural_number n1_exp(nn_type{}, 123);
	natural_number n2_exp(nn_type{}, 66);
	
	n1 = add(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractZeroZero {
	natural_number n1(nn_type{});
	natural_number n2(nn_type{});
	natural_number n1_exp(nn_type{});
	natural_number n2_exp(nn_type{});
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFiveZero {
	natural_number n1(nn_type{}, 5);
	natural_number n2(nn_type{}, 0);
	natural_number n1_exp(nn_type{}, 5);
	natural_number n2_exp(nn_type{}, 0);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourFour {
	natural_number n1(nn_type{}, 4);
	natural_number n2(nn_type{}, 4);
	natural_number n1_exp(nn_type{}, 0);
	natural_number n2_exp(nn_type{}, 4);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractTenTen {
	natural_number n1(nn_type{}, 10);
	natural_number n2(nn_type{}, 10);
	natural_number n1_exp(nn_type{}, 0);
	natural_number n2_exp(nn_type{}, 10);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_66{
	natural_number n1(nn_type{}, 77);
	natural_number n2(nn_type{}, 66);
	natural_number n1_exp(nn_type{}, 11);
	natural_number n2_exp(nn_type{}, 66);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_6{
	natural_number n1(nn_type{}, 77);
	natural_number n2(nn_type{}, 6);
	natural_number n1_exp(nn_type{}, 71);
	natural_number n2_exp(nn_type{}, 6);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract71_66{
	natural_number n1(nn_type{}, 71);
	natural_number n2(nn_type{}, 66);
	natural_number n1_exp(nn_type{}, 5);
	natural_number n2_exp(nn_type{}, 66);
	
	n1 = subtract(std::move(n1), n2);
	
	std::string n1_str = nnToString(n1);
	std::string n2_str = nnToString(n2);
	XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
	XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyZeroZero {
    natural_number n1(nn_type{});
    natural_number n2(nn_type{});
    natural_number n1_exp(nn_type{});
    natural_number n2_exp(nn_type{});
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyFiveZero {
    natural_number n1(nn_type{}, 5);
    natural_number n2(nn_type{});
    natural_number n1_exp(nn_type{}, 0);
    natural_number n2_exp(nn_type{});
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyFourFour {
    natural_number n1(nn_type{}, 4);
    natural_number n2(nn_type{}, 4);
    natural_number n1_exp(nn_type{}, 16);
    natural_number n2_exp(nn_type{}, 4);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiplyTenTen {
    natural_number n1(nn_type{}, 10);
    natural_number n2(nn_type{}, 10);
    natural_number n1_exp(nn_type{}, 100);
    natural_number n2_exp(nn_type{}, 10);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiply77_66{
    natural_number n1(nn_type{}, 77);
    natural_number n2(nn_type{}, 66);
    natural_number n1_exp(nn_type{}, 5082);
    natural_number n2_exp(nn_type{}, 66);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiply77_6{
    natural_number n1(nn_type{}, 77);
    natural_number n2(nn_type{}, 6);
    natural_number n1_exp(nn_type{}, 462);
    natural_number n2_exp(nn_type{}, 6);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testMultiply71_66{
    natural_number n1(nn_type{}, 71);
    natural_number n2(nn_type{}, 66);
    natural_number n1_exp(nn_type{}, 4686);
    natural_number n2_exp(nn_type{}, 66);
    
    n1 = multiply(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

@end
