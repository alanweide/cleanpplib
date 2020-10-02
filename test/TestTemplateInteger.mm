//
//  TestTemplateInteger.m
//  TestTemplateInteger
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
#include <template_integer/template_integer.hpp>

@interface TestTemplateInteger : XCTestCase
@end

@implementation TestTemplateInteger

using namespace cleanpp;

typedef nn_integer bigint_type;
typedef t_integer<bigint_type> bigint_t;

static std::string bigintToString(bigint_t &o) {
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
    bigint_t n;
    
    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "0");
    XCTAssert(n.sign() == ZERO);
}

- (void)testInitializer_SingleDig {
	bigint_t n(4);

    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == POSITIVE);
}

- (void)testInitializer_TwoDig {
	bigint_t n(45);

    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == POSITIVE);
}


- (void)testInitializer_SingleDigNeg {
	bigint_t n(-4);

	std::string n_str = bigintToString(n);
	XCTAssert(n_str == "-4", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == NEGATIVE);
}

- (void)testInitializer_TwoDigNeg {
	bigint_t n(-45);

	std::string n_str = bigintToString(n);
	XCTAssert(n_str == "-45", @"n = %s", n_str.c_str());
	XCTAssert(n.sign() == NEGATIVE);
}

- (void)testClearZero {
	bigint_t n;
	bigint_t expected;

	n.clear();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testClearPositive {
	t_integer<nn_integer> n(47);
	t_integer<nn_integer> expected(0);

	n.clear();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testClearNegative {
	bigint_t n(-47);
	bigint_t expected(0);

	n.clear();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
	bigint_t n(0);
	bigint_t expected(1);

	n.increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
	bigint_t n(9);
	bigint_t expected(10);

	n.increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
	bigint_t n(5);
	bigint_t expected(6);

	n.increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegTen {
	bigint_t n(-10);
	bigint_t expected(-9);

	n.increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegFive {
	bigint_t n(-5);
	bigint_t expected(-4);

	n.increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegOne {
	bigint_t n(-1);
	bigint_t expected(0);

	n.increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
	bigint_t n(1);
	bigint_t expected(0);

	n.decrement();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
	bigint_t n(10);
	bigint_t expected(9);

	n.decrement();

    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
	bigint_t n(5);
	bigint_t expected(4);

	n.decrement();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementZero {
	bigint_t n(0);
	bigint_t expected(-1);

	n.decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementNegNine {
	bigint_t n(-9);
	bigint_t expected(-10);

	n.decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementNegFive {
	bigint_t n(-5);
	bigint_t expected(-6);

	n.decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
	bigint_t n(0);
	bigint_t expected(0);

	n.multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
	bigint_t n(0);
	bigint_t expected(5);

	n.multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
	bigint_t n(5);
	bigint_t expected(50);

	n.multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
	bigint_t n(5);
	bigint_t expected(55);

	n.multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadNegFive_Zero {
	bigint_t n(-5);
	bigint_t expected(-50);

	n.multiply_by_radix(0);
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadNegFive_Five {
	bigint_t n(-5);
	bigint_t expected(-55);

	n.multiply_by_radix(5);
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
	bigint_t n(0);
	bigint_t expected(0);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFive {
	bigint_t n(5);
	bigint_t expected(0);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
	bigint_t n(50);
	bigint_t expected(5);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
	bigint_t n(55);
	bigint_t expected(5);

    int d = n.divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDivRadNegFive {
	bigint_t n(-5);
	bigint_t expected(0);

	int d = n.divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadNegFifty {
	bigint_t n(-50);
	bigint_t expected(-5);

	int d = n.divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadNegFiftyFive {
	bigint_t n(-55);
	bigint_t expected(-5);

	int d = n.divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(n == expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testCloneFromZero {
    bigint_t n;
	bigint_t n2;
    bigint_t n_exp;
    bigint_t n2_exp;

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromOne {
	bigint_t n;
	bigint_t n2(1);
	bigint_t n_exp(1);
	bigint_t n2_exp(1);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromThree {
	bigint_t n;
	bigint_t n2(3);
	bigint_t n_exp(3);
	bigint_t n2_exp(3);

	n = n2.clone();
    
    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromFive {
	bigint_t n;
	bigint_t n2(5);
	bigint_t n_exp(5);
	bigint_t n2_exp(5);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFrom25 {
	bigint_t n;
	bigint_t n2(25);
	bigint_t n_exp(25);
	bigint_t n2_exp(25);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegOne {
	bigint_t n;
	bigint_t n2(-1);
	bigint_t n_exp(-1);
	bigint_t n2_exp(-1);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegThree {
	bigint_t n;
	bigint_t n2(-3);
	bigint_t n_exp(-3);
	bigint_t n2_exp(-3);

	n = n2.clone();
    
    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegFive {
	bigint_t n;
	bigint_t n2(-5);
	bigint_t n_exp(-5);
	bigint_t n2_exp(-5);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNeg25 {
	bigint_t n;
	bigint_t n2(-25);
	bigint_t n_exp(-25);
	bigint_t n2_exp(-25);

	n = n2.clone();

    XCTAssert(n == n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(n2 == n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

/* ----------------------------
 * friend functions
 * ---------------------------- */

- (void)testCompareZeroZero {
	bigint_t n1;
	bigint_t n2;
	bigint_t n1_exp;
	bigint_t n2_exp;

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp == 0, @"comp = %d", comp);
}

- (void)testCompareZeroOne {
	bigint_t n1;
	bigint_t n2(1);
	bigint_t n1_exp;
	bigint_t n2_exp(1);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareOneZero {
	bigint_t n1(1);
	bigint_t n2(0);
	bigint_t n1_exp(1);
	bigint_t n2_exp(0);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareFiveTwo {
	bigint_t n1(5);
	bigint_t n2(2);
	bigint_t n1_exp(5);
	bigint_t n2_exp(2);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareFiveNeg4 {
	bigint_t n1(5);
	bigint_t n2(-4);
	bigint_t n1_exp(5);
	bigint_t n2_exp(-4);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegFourFive {
	bigint_t n1(-4);
	bigint_t n2(5);
	bigint_t n1_exp(-4);
	bigint_t n2_exp(5);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareTenSix {
	bigint_t n1(10);
	bigint_t n2(6);
	bigint_t n1_exp(10);
	bigint_t n2_exp(6);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegTenNegSix {
	bigint_t n1(-10);
	bigint_t n2(-6);
	bigint_t n1_exp(-10);
	bigint_t n2_exp(-6);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareTenNegTen {
    bigint_t n1(10);
	bigint_t n2(-10);
    bigint_t n1_exp(10);
    bigint_t n2_exp(-10);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegTenTen {
    bigint_t n1(-10);
    bigint_t n2(10);
    bigint_t n1_exp(-10);
    bigint_t n2_exp(10);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testAddZeroZero {
	bigint_t n1;
	bigint_t n2;
	bigint_t n1_exp;
	bigint_t n2_exp;

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroFive {
	bigint_t n1;
    bigint_t n2(5);
    bigint_t n1_exp(5);
    bigint_t n2_exp(5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
    bigint_t n1(5);
	bigint_t n2;
    bigint_t n1_exp(5);
	bigint_t n2_exp;

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourFour {
    bigint_t n1(4);
    bigint_t n2(4);
    bigint_t n1_exp(8);
    bigint_t n2_exp(4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveFive {
    bigint_t n1(5);
    bigint_t n2(5);
    bigint_t n1_exp(10);
    bigint_t n2_exp(5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddTenTen {
    bigint_t n1(10);
    bigint_t n2(10);
    bigint_t n1_exp(20);
    bigint_t n2_exp(10);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_66{
    bigint_t n1(57);
    bigint_t n2(66);
    bigint_t n1_exp(123);
    bigint_t n2_exp(66);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroNegFive {
	bigint_t n1;
    bigint_t n2(-5);
    bigint_t n1_exp(-5);
    bigint_t n2_exp(-5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFiveZero {
    bigint_t n1(-5);
	bigint_t n2;
    bigint_t n1_exp(-5);
	bigint_t n2_exp;

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourNegFour {
    bigint_t n1(4);
    bigint_t n2(-4);
    bigint_t n1_exp(0);
    bigint_t n2_exp(-4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFourNegFour {
    bigint_t n1(-4);
    bigint_t n2(-4);
    bigint_t n1_exp(-8);
    bigint_t n2_exp(-4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFiveNegFive {
    bigint_t n1(-5);
    bigint_t n2(-5);
    bigint_t n1_exp(-10);
    bigint_t n2_exp(-5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegTenNegTen {
    bigint_t n1(-10);
    bigint_t n2(-10);
    bigint_t n1_exp(-20);
    bigint_t n2_exp(-10);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_Neg66{
    bigint_t n1(67);
    bigint_t n2(-56);
    bigint_t n1_exp(11);
    bigint_t n2_exp(-56);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractZeroZero {
	bigint_t n1;
	bigint_t n2;
	bigint_t n1_exp;
	bigint_t n2_exp;

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFiveZero {
    bigint_t n1(5);
	bigint_t n2;
    bigint_t n1_exp(5);
	bigint_t n2_exp;

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourFour {
    bigint_t n1(4);
    bigint_t n2(4);
    bigint_t n1_exp(0);
    bigint_t n2_exp(4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractTenTen {
    bigint_t n1(10);
    bigint_t n2(10);
    bigint_t n1_exp(0);
    bigint_t n2_exp(10);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_66{
    bigint_t n1(77);
    bigint_t n2(66);
    bigint_t n1_exp(11);
    bigint_t n2_exp(66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_6{
    bigint_t n1(77);
    bigint_t n2(6);
    bigint_t n1_exp(71);
    bigint_t n2_exp(6);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract71_66{
    bigint_t n1(71);
    bigint_t n2(66);
    bigint_t n1_exp(5);
    bigint_t n2_exp(66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract3_4 {
    bigint_t n1(3);
    bigint_t n2(4);
    bigint_t n1_exp(-1);
    bigint_t n2_exp(4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNegFiveZero {
    bigint_t n1(-5);
	bigint_t n2;
    bigint_t n1_exp(-5);
	bigint_t n2_exp;

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourNegFour {
    bigint_t n1(4);
    bigint_t n2(-4);
    bigint_t n1_exp(8);
    bigint_t n2_exp(-4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNegFourNegFour {
    bigint_t n1(-4);
    bigint_t n2(-4);
    bigint_t n1_exp(0);
    bigint_t n2_exp(-4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_Neg66{
    bigint_t n1(77);
    bigint_t n2(-66);
    bigint_t n1_exp(143);
    bigint_t n2_exp(-66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNeg77_66{
    bigint_t n1(-77);
    bigint_t n2(66);
    bigint_t n1_exp(-143);
    bigint_t n2_exp(66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract1_2{
    bigint_t n1(1);
    bigint_t n2(2);
    bigint_t n1_exp(-1);
    bigint_t n2_exp(2);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

@end
