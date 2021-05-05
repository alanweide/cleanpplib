//
//  TestFlexInteger.m
//  TestFlexInteger
//
//  Created by Alan Weide on 11/29/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <integer_impls/nn_integer.hpp>
#include <integer_impls/vector_integer.hpp>
#include <clean_integer/integer.hpp>

@interface TestFlexInteger : XCTestCase
@end

@implementation TestFlexInteger

using namespace cleanpp;

typedef nn_integer bigint_kernel_impl;

static std::string bigintToString(integer &o) {
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
    integer n(bigint_kernel_impl{});
    
    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "0");
    XCTAssert(n.sign() == ZERO);
}

- (void)testInitializer_SingleDig {
	integer n(bigint_kernel_impl{}, 4);

    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == POSITIVE);
}

- (void)testInitializer_TwoDig {
	integer n(bigint_kernel_impl{}, 45);

    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == POSITIVE);
}


- (void)testInitializer_SingleDigNeg {
	integer n(bigint_kernel_impl{}, -4);

	std::string n_str = bigintToString(n);
	XCTAssert(n_str == "-4", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == NEGATIVE);
}

- (void)testInitializer_TwoDigNeg {
	integer n(bigint_kernel_impl{}, -45);

	std::string n_str = bigintToString(n);
	XCTAssert(n_str == "-45", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == NEGATIVE);
}

- (void)testClearZero {
	integer n(bigint_kernel_impl{});
	integer expected(bigint_kernel_impl{});

	n.clear();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testClearPositive {
	integer n(bigint_kernel_impl{}, 47);
	integer expected(bigint_kernel_impl{}, 0);

	n.clear();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testClearNegative {
	integer n(bigint_kernel_impl{}, -47);
	integer expected(bigint_kernel_impl{}, 0);

	n.clear();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
	integer n(bigint_kernel_impl{}, 0);
	integer expected(bigint_kernel_impl{}, 1);

	n.increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
	integer n(bigint_kernel_impl{}, 9);
	integer expected(bigint_kernel_impl{}, 10);

	n.increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
	integer n(bigint_kernel_impl{}, 5);
	integer expected(bigint_kernel_impl{}, 6);

	n.increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegTen {
	integer n(nn_integer{}, -10);
	integer expected(nn_integer{}, -9);

	n.increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegFive {
	integer n(bigint_kernel_impl{}, -5);
	integer expected(bigint_kernel_impl{}, -4);

	n.increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegOne {
	integer n(bigint_kernel_impl{}, -1);
	integer expected(bigint_kernel_impl{}, 0);

	n.increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
	integer n(bigint_kernel_impl{}, 1);
	integer expected(bigint_kernel_impl{}, 0);

	n.decrement();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
	integer n(bigint_kernel_impl{}, 10);
	integer expected(bigint_kernel_impl{}, 9);

	n.decrement();

    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
	integer n(bigint_kernel_impl{}, 5);
	integer expected(bigint_kernel_impl{}, 4);

	n.decrement();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementZero {
	integer n(bigint_kernel_impl{}, 0);
	integer expected(bigint_kernel_impl{}, -1);

	n.decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementNegNine {
	integer n(bigint_kernel_impl{}, -9);
	integer expected(bigint_kernel_impl{}, -10);

	n.decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementNegFive {
	integer n(bigint_kernel_impl{}, -5);
	integer expected(bigint_kernel_impl{}, -6);

	n.decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
	integer n(bigint_kernel_impl{}, 0);
	integer expected(bigint_kernel_impl{}, 0);

	n.multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
	integer n(bigint_kernel_impl{}, 0);
	integer expected(bigint_kernel_impl{}, 5);

	n.multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
	integer n(bigint_kernel_impl{}, 5);
	integer expected(bigint_kernel_impl{}, 50);

	n.multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
	integer n(bigint_kernel_impl{}, 5);
	integer expected(bigint_kernel_impl{}, 55);

	n.multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadNegFive_Zero {
	integer n(bigint_kernel_impl{}, -5);
	integer expected(bigint_kernel_impl{}, -50);

	n.multiply_by_radix(0);
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadNegFive_Five {
	integer n(bigint_kernel_impl{}, -5);
	integer expected(bigint_kernel_impl{}, -55);

	n.multiply_by_radix(5);
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
	integer n(bigint_kernel_impl{}, 0);
	integer expected(bigint_kernel_impl{}, 0);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFive {
	integer n(bigint_kernel_impl{}, 5);
	integer expected(bigint_kernel_impl{}, 0);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
	integer n(bigint_kernel_impl{}, 50);
	integer expected(bigint_kernel_impl{}, 5);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
	integer n(bigint_kernel_impl{}, 55);
	integer expected(bigint_kernel_impl{}, 5);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDivRadNegFive {
	integer n(bigint_kernel_impl{}, -5);
	integer expected(bigint_kernel_impl{}, 0);

	int d = n.divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadNegFifty {
	integer n(bigint_kernel_impl{}, -50);
	integer expected(bigint_kernel_impl{}, -5);

	int d = n.divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadNegFiftyFive {
	integer n(bigint_kernel_impl{}, -55);
	integer expected(bigint_kernel_impl{}, -5);

	int d = n.divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testCloneFromZero {
    integer n(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{});
    integer n_exp(bigint_kernel_impl{});
    integer n2_exp(bigint_kernel_impl{});

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromOne {
	integer n(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{}, 1);
	integer n_exp(bigint_kernel_impl{}, 1);
	integer n2_exp(bigint_kernel_impl{}, 1);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromThree {
	integer n(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{}, 3);
	integer n_exp(bigint_kernel_impl{}, 3);
	integer n2_exp(bigint_kernel_impl{}, 3);

	n = n2.clone();
    
    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromFive {
	integer n(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{}, 5);
	integer n_exp(bigint_kernel_impl{}, 5);
	integer n2_exp(bigint_kernel_impl{}, 5);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFrom25 {
	integer n(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{}, 25);
	integer n_exp(bigint_kernel_impl{}, 25);
	integer n2_exp(bigint_kernel_impl{}, 25);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegOne {
	integer n(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{}, -1);
	integer n_exp(bigint_kernel_impl{}, -1);
	integer n2_exp(bigint_kernel_impl{}, -1);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegThree {
	integer n(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{}, -3);
	integer n_exp(bigint_kernel_impl{}, -3);
	integer n2_exp(bigint_kernel_impl{}, -3);

	n = n2.clone();
    
    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegFive {
	integer n(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{}, -5);
	integer n_exp(bigint_kernel_impl{}, -5);
	integer n2_exp(bigint_kernel_impl{}, -5);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNeg25 {
	integer n(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{}, -25);
	integer n_exp(bigint_kernel_impl{}, -25);
	integer n2_exp(bigint_kernel_impl{}, -25);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

/* ----------------------------
 * friend functions
 * ---------------------------- */

- (void)testCompareZeroZero {
	integer n1(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{});
	integer n1_exp(bigint_kernel_impl{});
	integer n2_exp(bigint_kernel_impl{});

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp == 0, @"comp = %d", comp);
}

- (void)testCompareZeroOne {
	integer n1(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{}, 1);
	integer n1_exp(bigint_kernel_impl{});
	integer n2_exp(bigint_kernel_impl{}, 1);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareOneZero {
	integer n1(bigint_kernel_impl{}, 1);
	integer n2(bigint_kernel_impl{}, 0);
	integer n1_exp(bigint_kernel_impl{}, 1);
	integer n2_exp(bigint_kernel_impl{}, 0);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareFiveTwo {
	integer n1(bigint_kernel_impl{}, 5);
	integer n2(bigint_kernel_impl{}, 2);
	integer n1_exp(bigint_kernel_impl{}, 5);
	integer n2_exp(bigint_kernel_impl{}, 2);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareFiveNeg4 {
	integer n1(bigint_kernel_impl{}, 5);
	integer n2(bigint_kernel_impl{}, -4);
	integer n1_exp(bigint_kernel_impl{}, 5);
	integer n2_exp(bigint_kernel_impl{}, -4);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegFourFive {
	integer n1(bigint_kernel_impl{}, -4);
	integer n2(bigint_kernel_impl{}, 5);
	integer n1_exp(bigint_kernel_impl{}, -4);
	integer n2_exp(bigint_kernel_impl{}, 5);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareTenSix {
	integer n1(bigint_kernel_impl{}, 10);
	integer n2(bigint_kernel_impl{}, 6);
	integer n1_exp(bigint_kernel_impl{}, 10);
	integer n2_exp(bigint_kernel_impl{}, 6);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegTenNegSix {
	integer n1(bigint_kernel_impl{}, -10);
	integer n2(bigint_kernel_impl{}, -6);
	integer n1_exp(bigint_kernel_impl{}, -10);
	integer n2_exp(bigint_kernel_impl{}, -6);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareTenNegTen {
    integer n1(bigint_kernel_impl{}, 10);
	integer n2(bigint_kernel_impl{}, -10);
    integer n1_exp(bigint_kernel_impl{}, 10);
    integer n2_exp(bigint_kernel_impl{}, -10);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegTenTen {
    integer n1(bigint_kernel_impl{}, -10);
    integer n2(bigint_kernel_impl{}, 10);
    integer n1_exp(bigint_kernel_impl{}, -10);
    integer n2_exp(bigint_kernel_impl{}, 10);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testAddZeroZero {
	integer n1(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{});
	integer n1_exp(bigint_kernel_impl{});
	integer n2_exp(bigint_kernel_impl{});

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroFive {
	integer n1(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, 5);
    integer n1_exp(bigint_kernel_impl{}, 5);
    integer n2_exp(bigint_kernel_impl{}, 5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
    integer n1(bigint_kernel_impl{}, 5);
	integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{}, 5);
	integer n2_exp(bigint_kernel_impl{});

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourFour {
    integer n1(bigint_kernel_impl{}, 4);
    integer n2(bigint_kernel_impl{}, 4);
    integer n1_exp(bigint_kernel_impl{}, 8);
    integer n2_exp(bigint_kernel_impl{}, 4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveFive {
    integer n1(bigint_kernel_impl{}, 5);
    integer n2(bigint_kernel_impl{}, 5);
    integer n1_exp(bigint_kernel_impl{}, 10);
    integer n2_exp(bigint_kernel_impl{}, 5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddTenTen {
    integer n1(bigint_kernel_impl{}, 10);
    integer n2(bigint_kernel_impl{}, 10);
    integer n1_exp(bigint_kernel_impl{}, 20);
    integer n2_exp(bigint_kernel_impl{}, 10);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_66{
    integer n1(bigint_kernel_impl{}, 57);
    integer n2(bigint_kernel_impl{}, 66);
    integer n1_exp(bigint_kernel_impl{}, 123);
    integer n2_exp(bigint_kernel_impl{}, 66);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroNegFive {
	integer n1(bigint_kernel_impl{});
    integer n2(bigint_kernel_impl{}, -5);
    integer n1_exp(bigint_kernel_impl{}, -5);
    integer n2_exp(bigint_kernel_impl{}, -5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFiveZero {
    integer n1(bigint_kernel_impl{}, -5);
	integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{}, -5);
	integer n2_exp(bigint_kernel_impl{});

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourNegFour {
    integer n1(bigint_kernel_impl{}, 4);
    integer n2(bigint_kernel_impl{}, -4);
    integer n1_exp(bigint_kernel_impl{}, 0);
    integer n2_exp(bigint_kernel_impl{}, -4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFourNegFour {
    integer n1(bigint_kernel_impl{}, -4);
    integer n2(bigint_kernel_impl{}, -4);
    integer n1_exp(bigint_kernel_impl{}, -8);
    integer n2_exp(bigint_kernel_impl{}, -4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFiveNegFive {
    integer n1(bigint_kernel_impl{}, -5);
    integer n2(bigint_kernel_impl{}, -5);
    integer n1_exp(bigint_kernel_impl{}, -10);
    integer n2_exp(bigint_kernel_impl{}, -5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegTenNegTen {
    integer n1(bigint_kernel_impl{}, -10);
    integer n2(bigint_kernel_impl{}, -10);
    integer n1_exp(bigint_kernel_impl{}, -20);
    integer n2_exp(bigint_kernel_impl{}, -10);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_Neg66{
    integer n1(bigint_kernel_impl{}, 67);
    integer n2(bigint_kernel_impl{}, -56);
    integer n1_exp(bigint_kernel_impl{}, 11);
    integer n2_exp(bigint_kernel_impl{}, -56);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractZeroZero {
	integer n1(bigint_kernel_impl{});
	integer n2(bigint_kernel_impl{});
	integer n1_exp(bigint_kernel_impl{});
	integer n2_exp(bigint_kernel_impl{});

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFiveZero {
    integer n1(bigint_kernel_impl{}, 5);
	integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{}, 5);
	integer n2_exp(bigint_kernel_impl{});

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourFour {
    integer n1(bigint_kernel_impl{}, 4);
    integer n2(bigint_kernel_impl{}, 4);
    integer n1_exp(bigint_kernel_impl{}, 0);
    integer n2_exp(bigint_kernel_impl{}, 4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractTenTen {
    integer n1(bigint_kernel_impl{}, 10);
    integer n2(bigint_kernel_impl{}, 10);
    integer n1_exp(bigint_kernel_impl{}, 0);
    integer n2_exp(bigint_kernel_impl{}, 10);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_66{
    integer n1(bigint_kernel_impl{}, 77);
    integer n2(bigint_kernel_impl{}, 66);
    integer n1_exp(bigint_kernel_impl{}, 11);
    integer n2_exp(bigint_kernel_impl{}, 66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_6{
    integer n1(bigint_kernel_impl{}, 77);
    integer n2(bigint_kernel_impl{}, 6);
    integer n1_exp(bigint_kernel_impl{}, 71);
    integer n2_exp(bigint_kernel_impl{}, 6);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract71_66{
    integer n1(bigint_kernel_impl{}, 71);
    integer n2(bigint_kernel_impl{}, 66);
    integer n1_exp(bigint_kernel_impl{}, 5);
    integer n2_exp(bigint_kernel_impl{}, 66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract3_4 {
    integer n1(bigint_kernel_impl{}, 3);
    integer n2(bigint_kernel_impl{}, 4);
    integer n1_exp(bigint_kernel_impl{}, -1);
    integer n2_exp(bigint_kernel_impl{}, 4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNegFiveZero {
    integer n1(bigint_kernel_impl{}, -5);
	integer n2(bigint_kernel_impl{});
    integer n1_exp(bigint_kernel_impl{}, -5);
	integer n2_exp(bigint_kernel_impl{});

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourNegFour {
    integer n1(bigint_kernel_impl{}, 4);
    integer n2(bigint_kernel_impl{}, -4);
    integer n1_exp(bigint_kernel_impl{}, 8);
    integer n2_exp(bigint_kernel_impl{}, -4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNegFourNegFour {
    integer n1(bigint_kernel_impl{}, -4);
    integer n2(bigint_kernel_impl{}, -4);
    integer n1_exp(bigint_kernel_impl{}, 0);
    integer n2_exp(bigint_kernel_impl{}, -4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_Neg66{
    integer n1(bigint_kernel_impl{}, 77);
    integer n2(bigint_kernel_impl{}, -66);
    integer n1_exp(bigint_kernel_impl{}, 143);
    integer n2_exp(bigint_kernel_impl{}, -66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNeg77_66{
    integer n1(bigint_kernel_impl{}, -77);
    integer n2(bigint_kernel_impl{}, 66);
    integer n1_exp(bigint_kernel_impl{}, -143);
    integer n2_exp(bigint_kernel_impl{}, 66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract1_2{
    integer n1(bigint_kernel_impl{}, 1);
    integer n2(bigint_kernel_impl{}, 2);
    integer n1_exp(bigint_kernel_impl{}, -1);
    integer n2_exp(bigint_kernel_impl{}, 2);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

@end
