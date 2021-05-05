//
//  TestVectorInteger.m
//  TestVectorInteger
//
//  Created by Alan Weide on 11/29/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <integer_impls/vector_integer.hpp>

@interface TestVectorInteger : XCTestCase
@end

@implementation TestVectorInteger

using namespace cleanpp;

typedef vector_integer bigint_type;

static std::string bigintToString(std::unique_ptr<integer_impl> &o) {
	std::stringstream s;
    s << *o;
    return s.str();
}

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testInitializerDef {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "0");
    XCTAssert(n->sign() == ZERO);
}

- (void)testInitializer_SingleDig {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(4);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
    XCTAssert(n->sign() == POSITIVE);
}

- (void)testInitializer_TwoDig {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(45);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
    XCTAssert(n->sign() == POSITIVE);
}


- (void)testInitializer_SingleDigNeg {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-4);
	
	std::string n_str = bigintToString(n);
	XCTAssert(n_str == "-4", @"n = %s", n_str.c_str());
    XCTAssert(n->sign() == NEGATIVE);
}

- (void)testInitializer_TwoDigNeg {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-45);
	
	std::string n_str = bigintToString(n);
	XCTAssert(n_str == "-45", @"n = %s", n_str.c_str());
    XCTAssert(n->sign() == NEGATIVE);
}

- (void)testClearZero {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
    
    n->clear();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testClearPositive {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(47);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
    
    n->clear();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testClearNegative {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-47);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
	
	n->clear();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(1);
    
    n->increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(9);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(10);
    
    n->increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(6);
    
    n->increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegTen {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-10);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-9);
	
	n->increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegFive {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-4);
	
	n->increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegOne {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-1);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
	
	n->increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
    
    n->decrement();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(9);
    
    n->decrement();

    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(4);
    
    n->decrement();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementZero {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-1);
	
	n->decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementNegNine {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-9);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-10);
	
	n->decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementNegFive {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-6);
	
	n->decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
    
    n->multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(5);

    n->multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(50);

    n->multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(55);

    n->multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadNegFive_Zero {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-50);
	
	n->multiply_by_radix(0);
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadNegFive_Five {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-55);
	
	n->multiply_by_radix(5);
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFive {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(50);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(5);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
    std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(55);
    std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(5);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDivRadNegFive {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(0);
	
	int d = 4;
	d = n->divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadNegFifty {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-50);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-5);
	
	int d = 4;
	d = n->divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadNegFiftyFive {
	std::unique_ptr<integer_impl> n = std::make_unique<bigint_type>(-55);
	std::unique_ptr<integer_impl> expected= std::make_unique<bigint_type>(-5);
	
	int d = 4;
	d = n->divide_by_radix();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testCloneFromZero {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n = n2->clone();

    XCTAssert(*n == *n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(*n2 == *n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromOne {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(1);

    n = n2->clone();

    XCTAssert(*n == *n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(*n2 == *n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromThree {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(3);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(3);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(3);

    n = n2->clone();
    
    XCTAssert(*n == *n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(*n2 == *n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromFive {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);

    n = n2->clone();

    XCTAssert(*n == *n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(*n2 == *n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFrom25 {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(25);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(25);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(25);

    n = n2->clone();

    XCTAssert(*n == *n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(*n2 == *n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegOne {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-1);

    n = n2->clone();

    XCTAssert(*n == *n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(*n2 == *n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegThree {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-3);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-3);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-3);

    n = n2->clone();
    
    XCTAssert(*n == *n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(*n2 == *n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNegFive {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-5);

    n = n2->clone();

    XCTAssert(*n == *n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(*n2 == *n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

- (void)testCloneFromNeg25 {
    std::unique_ptr<integer_impl> n;
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-25);
    std::unique_ptr<integer_impl> n_exp = std::make_unique<bigint_type>(-25);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-25);

    n = n2->clone();

    XCTAssert(*n == *n_exp, @"n = %s", bigintToString(n).c_str());
    XCTAssert(*n2 == *n2_exp, @"n2 = %s", bigintToString(n2).c_str());
}

/* ----------------------------
 * friend functions
 * ---------------------------- */

- (void)testCompareZeroZero {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp == 0, @"comp = %d", comp);
}

- (void)testCompareZeroOne {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(1);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareOneZero {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(0);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareFiveTwo {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(2);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(2);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareFiveNeg4 {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegFourFive {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-4);

    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareTenSix {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(6);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(6);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegTenNegSix {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-6);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-6);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testCompareTenNegTen {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-10);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp > 0, @"comp = %d", comp);
}

- (void)testCompareNegTenTen {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(10);
    
    int comp = compare(n1, n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
    XCTAssert(comp < 0, @"comp = %d", comp);
}

- (void)testAddZeroZero {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroFive {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourFour {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(8);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveFive {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddTenTen {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(20);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(10);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_66{
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(57);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(123);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroNegFive {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFiveZero {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourNegFour {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFourNegFour {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-8);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegFiveNegFive {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-5);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddNegTenNegTen {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-20);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-10);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd67_Neg56{
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(67);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-56);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(11);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-56);

    n1 = add(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractZeroZero {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFiveZero {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourFour {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractTenTen {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(10);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(10);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_66{
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(11);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_6{
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(6);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(71);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(6);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract71_66{
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(71);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract3_4 {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(3);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNegFiveZero {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>();
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-5);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>();

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourNegFour {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(8);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNegFourNegFour {
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-4);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(0);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-4);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_Neg66{
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(-66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(143);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(-66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractNeg77_66{
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(-77);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(66);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-143);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(66);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract1_2{
    std::unique_ptr<integer_impl> n1 = std::make_unique<bigint_type>(1);
    std::unique_ptr<integer_impl> n2 = std::make_unique<bigint_type>(2);
    std::unique_ptr<integer_impl> n1_exp = std::make_unique<bigint_type>(-1);
    std::unique_ptr<integer_impl> n2_exp = std::make_unique<bigint_type>(2);

    n1 = subtract(std::move(n1), n2);

    std::string n1_str = bigintToString(n1);
    std::string n2_str = bigintToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

@end
