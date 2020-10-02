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
#include <clean_integer/nn_integer.hpp>
#include <clean_integer/vector_integer.hpp>
#include <flexible_integer/flexible_integer.hpp>

@interface TestFlexInteger : XCTestCase
@end

@implementation TestFlexInteger

using namespace cleanpp;

typedef nn_integer bigint_kernel_impl;

static std::string bigintToString(flex_integer &o) {
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
    flex_integer n(bigint_kernel_impl{});
    
    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "0");
    XCTAssert(n.sign() == ZERO);
}

- (void)testInitializer_SingleDig {
	flex_integer n(bigint_kernel_impl{}, 4);

    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == POSITIVE);
}

- (void)testInitializer_TwoDig {
	flex_integer n(bigint_kernel_impl{}, 45);

    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == POSITIVE);
}


- (void)testInitializer_SingleDigNeg {
	flex_integer n(bigint_kernel_impl{}, -4);

	std::string n_str = bigintToString(n);
	XCTAssert(n_str == "-4", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == NEGATIVE);
}

- (void)testInitializer_TwoDigNeg {
	flex_integer n(bigint_kernel_impl{}, -45);

	std::string n_str = bigintToString(n);
	XCTAssert(n_str == "-45", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == NEGATIVE);
}

- (void)testClearZero {
	flex_integer n(bigint_kernel_impl{});
	flex_integer expected(bigint_kernel_impl{});

	n.clear();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testClearPositive {
	flex_integer n(bigint_kernel_impl{}, 47);
	flex_integer expected(bigint_kernel_impl{}, 0);

	n.clear();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testClearNegative {
	flex_integer n(bigint_kernel_impl{}, -47);
	flex_integer expected(bigint_kernel_impl{}, 0);

	n.clear();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
	flex_integer n(bigint_kernel_impl{}, 0);
	flex_integer expected(bigint_kernel_impl{}, 1);

	n.increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
	flex_integer n(bigint_kernel_impl{}, 9);
	flex_integer expected(bigint_kernel_impl{}, 10);

	n.increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
	flex_integer n(bigint_kernel_impl{}, 5);
	flex_integer expected(bigint_kernel_impl{}, 6);

	n.increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegTen {
	flex_integer n(nn_integer{}, -10);
	flex_integer expected(nn_integer{}, -9);

	n.increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegFive {
	flex_integer n(bigint_kernel_impl{}, -5);
	flex_integer expected(bigint_kernel_impl{}, -4);

	n.increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegOne {
	flex_integer n(bigint_kernel_impl{}, -1);
	flex_integer expected(bigint_kernel_impl{}, 0);

	n.increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
	flex_integer n(bigint_kernel_impl{}, 1);
	flex_integer expected(bigint_kernel_impl{}, 0);

	n.decrement();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
	flex_integer n(bigint_kernel_impl{}, 10);
	flex_integer expected(bigint_kernel_impl{}, 9);

	n.decrement();

    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
	flex_integer n(bigint_kernel_impl{}, 5);
	flex_integer expected(bigint_kernel_impl{}, 4);

	n.decrement();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementZero {
	flex_integer n(bigint_kernel_impl{}, 0);
	flex_integer expected(bigint_kernel_impl{}, -1);

	n.decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementNegNine {
	flex_integer n(bigint_kernel_impl{}, -9);
	flex_integer expected(bigint_kernel_impl{}, -10);

	n.decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementNegFive {
	flex_integer n(bigint_kernel_impl{}, -5);
	flex_integer expected(bigint_kernel_impl{}, -6);

	n.decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
	flex_integer n(bigint_kernel_impl{}, 0);
	flex_integer expected(bigint_kernel_impl{}, 0);

	n.multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
	flex_integer n(bigint_kernel_impl{}, 0);
	flex_integer expected(bigint_kernel_impl{}, 5);

	n.multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
	flex_integer n(bigint_kernel_impl{}, 5);
	flex_integer expected(bigint_kernel_impl{}, 50);

	n.multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
	flex_integer n(bigint_kernel_impl{}, 5);
	flex_integer expected(bigint_kernel_impl{}, 55);

	n.multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadNegFive_Zero {
	flex_integer n(bigint_kernel_impl{}, -5);
	flex_integer expected(bigint_kernel_impl{}, -50);

	n.multiply_by_radix(0);
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadNegFive_Five {
	flex_integer n(bigint_kernel_impl{}, -5);
	flex_integer expected(bigint_kernel_impl{}, -55);

	n.multiply_by_radix(5);
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
	flex_integer n(bigint_kernel_impl{}, 0);
	flex_integer expected(bigint_kernel_impl{}, 0);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFive {
	flex_integer n(bigint_kernel_impl{}, 5);
	flex_integer expected(bigint_kernel_impl{}, 0);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
	flex_integer n(bigint_kernel_impl{}, 50);
	flex_integer expected(bigint_kernel_impl{}, 5);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
	flex_integer n(bigint_kernel_impl{}, 55);
	flex_integer expected(bigint_kernel_impl{}, 5);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDivRadNegFive {
	flex_integer n(bigint_kernel_impl{}, -5);
	flex_integer expected(bigint_kernel_impl{}, 0);

	int d = n.divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadNegFifty {
	flex_integer n(bigint_kernel_impl{}, -50);
	flex_integer expected(bigint_kernel_impl{}, -5);

	int d = n.divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadNegFiftyFive {
	flex_integer n(bigint_kernel_impl{}, -55);
	flex_integer expected(bigint_kernel_impl{}, -5);

	int d = n.divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testCloneFromZero {
    flex_integer n(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{});
    flex_integer n_exp(bigint_kernel_impl{});
    flex_integer n2_exp(bigint_kernel_impl{});

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromOne {
	flex_integer n(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{}, 1);
	flex_integer n_exp(bigint_kernel_impl{}, 1);
	flex_integer n2_exp(bigint_kernel_impl{}, 1);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromThree {
	flex_integer n(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{}, 3);
	flex_integer n_exp(bigint_kernel_impl{}, 3);
	flex_integer n2_exp(bigint_kernel_impl{}, 3);

	n = n2.clone();
    
    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromFive {
	flex_integer n(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{}, 5);
	flex_integer n_exp(bigint_kernel_impl{}, 5);
	flex_integer n2_exp(bigint_kernel_impl{}, 5);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFrom25 {
	flex_integer n(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{}, 25);
	flex_integer n_exp(bigint_kernel_impl{}, 25);
	flex_integer n2_exp(bigint_kernel_impl{}, 25);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegOne {
	flex_integer n(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{}, -1);
	flex_integer n_exp(bigint_kernel_impl{}, -1);
	flex_integer n2_exp(bigint_kernel_impl{}, -1);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegThree {
	flex_integer n(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{}, -3);
	flex_integer n_exp(bigint_kernel_impl{}, -3);
	flex_integer n2_exp(bigint_kernel_impl{}, -3);

	n = n2.clone();
    
    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegFive {
	flex_integer n(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{}, -5);
	flex_integer n_exp(bigint_kernel_impl{}, -5);
	flex_integer n2_exp(bigint_kernel_impl{}, -5);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNeg25 {
	flex_integer n(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{}, -25);
	flex_integer n_exp(bigint_kernel_impl{}, -25);
	flex_integer n2_exp(bigint_kernel_impl{}, -25);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

/* ----------------------------
 * friend functions
 * ---------------------------- */

- (void)testCompareZeroZero {
	flex_integer n1(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{});
	flex_integer n1_exp(bigint_kernel_impl{});
	flex_integer n2_exp(bigint_kernel_impl{});

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp == 0, @"comp = %d", comp);
}

- (void)testCompareZeroOne {
	flex_integer n1(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{}, 1);
	flex_integer n1_exp(bigint_kernel_impl{});
	flex_integer n2_exp(bigint_kernel_impl{}, 1);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareOneZero {
	flex_integer n1(bigint_kernel_impl{}, 1);
	flex_integer n2(bigint_kernel_impl{}, 0);
	flex_integer n1_exp(bigint_kernel_impl{}, 1);
	flex_integer n2_exp(bigint_kernel_impl{}, 0);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareFiveTwo {
	flex_integer n1(bigint_kernel_impl{}, 5);
	flex_integer n2(bigint_kernel_impl{}, 2);
	flex_integer n1_exp(bigint_kernel_impl{}, 5);
	flex_integer n2_exp(bigint_kernel_impl{}, 2);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareFiveNeg4 {
	flex_integer n1(bigint_kernel_impl{}, 5);
	flex_integer n2(bigint_kernel_impl{}, -4);
	flex_integer n1_exp(bigint_kernel_impl{}, 5);
	flex_integer n2_exp(bigint_kernel_impl{}, -4);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegFourFive {
	flex_integer n1(bigint_kernel_impl{}, -4);
	flex_integer n2(bigint_kernel_impl{}, 5);
	flex_integer n1_exp(bigint_kernel_impl{}, -4);
	flex_integer n2_exp(bigint_kernel_impl{}, 5);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareTenSix {
	flex_integer n1(bigint_kernel_impl{}, 10);
	flex_integer n2(bigint_kernel_impl{}, 6);
	flex_integer n1_exp(bigint_kernel_impl{}, 10);
	flex_integer n2_exp(bigint_kernel_impl{}, 6);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegTenNegSix {
	flex_integer n1(bigint_kernel_impl{}, -10);
	flex_integer n2(bigint_kernel_impl{}, -6);
	flex_integer n1_exp(bigint_kernel_impl{}, -10);
	flex_integer n2_exp(bigint_kernel_impl{}, -6);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareTenNegTen {
    flex_integer n1(bigint_kernel_impl{}, 10);
	flex_integer n2(bigint_kernel_impl{}, -10);
    flex_integer n1_exp(bigint_kernel_impl{}, 10);
    flex_integer n2_exp(bigint_kernel_impl{}, -10);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegTenTen {
    flex_integer n1(bigint_kernel_impl{}, -10);
    flex_integer n2(bigint_kernel_impl{}, 10);
    flex_integer n1_exp(bigint_kernel_impl{}, -10);
    flex_integer n2_exp(bigint_kernel_impl{}, 10);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testAddZeroZero {
	flex_integer n1(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{});
	flex_integer n1_exp(bigint_kernel_impl{});
	flex_integer n2_exp(bigint_kernel_impl{});

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroFive {
	flex_integer n1(bigint_kernel_impl{});
    flex_integer n2(bigint_kernel_impl{}, 5);
    flex_integer n1_exp(bigint_kernel_impl{}, 5);
    flex_integer n2_exp(bigint_kernel_impl{}, 5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
    flex_integer n1(bigint_kernel_impl{}, 5);
	flex_integer n2(bigint_kernel_impl{});
    flex_integer n1_exp(bigint_kernel_impl{}, 5);
	flex_integer n2_exp(bigint_kernel_impl{});

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourFour {
    flex_integer n1(bigint_kernel_impl{}, 4);
    flex_integer n2(bigint_kernel_impl{}, 4);
    flex_integer n1_exp(bigint_kernel_impl{}, 8);
    flex_integer n2_exp(bigint_kernel_impl{}, 4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveFive {
    flex_integer n1(bigint_kernel_impl{}, 5);
    flex_integer n2(bigint_kernel_impl{}, 5);
    flex_integer n1_exp(bigint_kernel_impl{}, 10);
    flex_integer n2_exp(bigint_kernel_impl{}, 5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddTenTen {
    flex_integer n1(bigint_kernel_impl{}, 10);
    flex_integer n2(bigint_kernel_impl{}, 10);
    flex_integer n1_exp(bigint_kernel_impl{}, 20);
    flex_integer n2_exp(bigint_kernel_impl{}, 10);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_66{
    flex_integer n1(bigint_kernel_impl{}, 57);
    flex_integer n2(bigint_kernel_impl{}, 66);
    flex_integer n1_exp(bigint_kernel_impl{}, 123);
    flex_integer n2_exp(bigint_kernel_impl{}, 66);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroNegFive {
	flex_integer n1(bigint_kernel_impl{});
    flex_integer n2(bigint_kernel_impl{}, -5);
    flex_integer n1_exp(bigint_kernel_impl{}, -5);
    flex_integer n2_exp(bigint_kernel_impl{}, -5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFiveZero {
    flex_integer n1(bigint_kernel_impl{}, -5);
	flex_integer n2(bigint_kernel_impl{});
    flex_integer n1_exp(bigint_kernel_impl{}, -5);
	flex_integer n2_exp(bigint_kernel_impl{});

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourNegFour {
    flex_integer n1(bigint_kernel_impl{}, 4);
    flex_integer n2(bigint_kernel_impl{}, -4);
    flex_integer n1_exp(bigint_kernel_impl{}, 0);
    flex_integer n2_exp(bigint_kernel_impl{}, -4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFourNegFour {
    flex_integer n1(bigint_kernel_impl{}, -4);
    flex_integer n2(bigint_kernel_impl{}, -4);
    flex_integer n1_exp(bigint_kernel_impl{}, -8);
    flex_integer n2_exp(bigint_kernel_impl{}, -4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFiveNegFive {
    flex_integer n1(bigint_kernel_impl{}, -5);
    flex_integer n2(bigint_kernel_impl{}, -5);
    flex_integer n1_exp(bigint_kernel_impl{}, -10);
    flex_integer n2_exp(bigint_kernel_impl{}, -5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegTenNegTen {
    flex_integer n1(bigint_kernel_impl{}, -10);
    flex_integer n2(bigint_kernel_impl{}, -10);
    flex_integer n1_exp(bigint_kernel_impl{}, -20);
    flex_integer n2_exp(bigint_kernel_impl{}, -10);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_Neg66{
    flex_integer n1(bigint_kernel_impl{}, 67);
    flex_integer n2(bigint_kernel_impl{}, -56);
    flex_integer n1_exp(bigint_kernel_impl{}, 11);
    flex_integer n2_exp(bigint_kernel_impl{}, -56);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractZeroZero {
	flex_integer n1(bigint_kernel_impl{});
	flex_integer n2(bigint_kernel_impl{});
	flex_integer n1_exp(bigint_kernel_impl{});
	flex_integer n2_exp(bigint_kernel_impl{});

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFiveZero {
    flex_integer n1(bigint_kernel_impl{}, 5);
	flex_integer n2(bigint_kernel_impl{});
    flex_integer n1_exp(bigint_kernel_impl{}, 5);
	flex_integer n2_exp(bigint_kernel_impl{});

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourFour {
    flex_integer n1(bigint_kernel_impl{}, 4);
    flex_integer n2(bigint_kernel_impl{}, 4);
    flex_integer n1_exp(bigint_kernel_impl{}, 0);
    flex_integer n2_exp(bigint_kernel_impl{}, 4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractTenTen {
    flex_integer n1(bigint_kernel_impl{}, 10);
    flex_integer n2(bigint_kernel_impl{}, 10);
    flex_integer n1_exp(bigint_kernel_impl{}, 0);
    flex_integer n2_exp(bigint_kernel_impl{}, 10);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_66{
    flex_integer n1(bigint_kernel_impl{}, 77);
    flex_integer n2(bigint_kernel_impl{}, 66);
    flex_integer n1_exp(bigint_kernel_impl{}, 11);
    flex_integer n2_exp(bigint_kernel_impl{}, 66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_6{
    flex_integer n1(bigint_kernel_impl{}, 77);
    flex_integer n2(bigint_kernel_impl{}, 6);
    flex_integer n1_exp(bigint_kernel_impl{}, 71);
    flex_integer n2_exp(bigint_kernel_impl{}, 6);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract71_66{
    flex_integer n1(bigint_kernel_impl{}, 71);
    flex_integer n2(bigint_kernel_impl{}, 66);
    flex_integer n1_exp(bigint_kernel_impl{}, 5);
    flex_integer n2_exp(bigint_kernel_impl{}, 66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract3_4 {
    flex_integer n1(bigint_kernel_impl{}, 3);
    flex_integer n2(bigint_kernel_impl{}, 4);
    flex_integer n1_exp(bigint_kernel_impl{}, -1);
    flex_integer n2_exp(bigint_kernel_impl{}, 4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNegFiveZero {
    flex_integer n1(bigint_kernel_impl{}, -5);
	flex_integer n2(bigint_kernel_impl{});
    flex_integer n1_exp(bigint_kernel_impl{}, -5);
	flex_integer n2_exp(bigint_kernel_impl{});

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourNegFour {
    flex_integer n1(bigint_kernel_impl{}, 4);
    flex_integer n2(bigint_kernel_impl{}, -4);
    flex_integer n1_exp(bigint_kernel_impl{}, 8);
    flex_integer n2_exp(bigint_kernel_impl{}, -4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNegFourNegFour {
    flex_integer n1(bigint_kernel_impl{}, -4);
    flex_integer n2(bigint_kernel_impl{}, -4);
    flex_integer n1_exp(bigint_kernel_impl{}, 0);
    flex_integer n2_exp(bigint_kernel_impl{}, -4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_Neg66{
    flex_integer n1(bigint_kernel_impl{}, 77);
    flex_integer n2(bigint_kernel_impl{}, -66);
    flex_integer n1_exp(bigint_kernel_impl{}, 143);
    flex_integer n2_exp(bigint_kernel_impl{}, -66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNeg77_66{
    flex_integer n1(bigint_kernel_impl{}, -77);
    flex_integer n2(bigint_kernel_impl{}, 66);
    flex_integer n1_exp(bigint_kernel_impl{}, -143);
    flex_integer n2_exp(bigint_kernel_impl{}, 66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract1_2{
    flex_integer n1(bigint_kernel_impl{}, 1);
    flex_integer n2(bigint_kernel_impl{}, 2);
    flex_integer n1_exp(bigint_kernel_impl{}, -1);
    flex_integer n2_exp(bigint_kernel_impl{}, 2);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

@end
