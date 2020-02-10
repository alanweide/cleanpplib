//
//  TestNNInteger.m
//  TestNNInteger
//
//  Created by Alan Weide on 11/29/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <clean_integer/nn_integer.hpp>

@interface TestNNInteger : XCTestCase
@end

@implementation TestNNInteger

using namespace cleanpp;

typedef nn_integer bigint_type;

static std::string bigintToString(std::unique_ptr<big_integer> &o) {
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
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>();
    
    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "0");
}

- (void)testInitializer_SingleDig {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(4);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
}

- (void)testInitializer_TwoDig {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(45);
    
    std::string n_str = bigintToString(n);
    XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
}


- (void)testInitializer_SingleDigNeg {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-4);
	
	std::string n_str = bigintToString(n);
	XCTAssert(n_str == "-4", @"n = %s", n_str.c_str());
}

- (void)testInitializer_TwoDigNeg {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-45);
	
	std::string n_str = bigintToString(n);
	XCTAssert(n_str == "-45", @"n = %s", n_str.c_str());
}

- (void)testClearZero {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>();
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(0);
    
    n->clear();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testClearPositive {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(47);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(0);
    
    n->clear();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testClearNegative {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-47);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(0);
	
	n->clear();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>();
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(1);
    
    n->increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(9);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(10);
    
    n->increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(6);
    
    n->increment();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegTen {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-10);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(-9);
	
	n->increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegFive {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(-4);
	
	n->increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNegOne {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-1);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(0);
	
	n->increment();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(1);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(0);
    
    n->decrement();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(10);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(9);
    
    n->decrement();

    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(4);
    
    n->decrement();
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementZero {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(0);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(-1);
	
	n->decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementNegNine {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-9);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(-10);
	
	n->decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementNegFive {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(-6);
	
	n->decrement();
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(0);
    
    n->multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(5);

    n->multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(50);

    n->multiply_by_radix(0);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(55);

    n->multiply_by_radix(5);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadNegFive_Zero {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(-50);
	
	n->multiply_by_radix(0);
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadNegFive_Five {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(-55);
	
	n->multiply_by_radix(5);
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(0);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(0);

    int d = 4;
    n->divide_by_radix(d);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFive {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(5);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(0);

    int d = 4;
    n->divide_by_radix(d);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(50);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(5);

    int d = 4;
    n->divide_by_radix(d);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
    std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(55);
    std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(5);

    int d = 4;
    n->divide_by_radix(d);
    
    std::string n_str = bigintToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDivRadNegFive {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-5);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(0);
	
	int d = 4;
	n->divide_by_radix(d);
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadNegFifty {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-50);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(-5);
	
	int d = 4;
	n->divide_by_radix(d);
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 0);
}

- (void)testDivRadNegFiftyFive {
	std::unique_ptr<big_integer> n = std::make_unique<bigint_type>(-55);
	std::unique_ptr<big_integer> expected= std::make_unique<bigint_type>(-5);
	
	int d = 4;
	n->divide_by_radix(d);
	
	std::string n_str = bigintToString(n);
	XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
	XCTAssert(d == 5, @"d = %d", d);
}

//- (void)testAddZeroZero {
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>();
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>();
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>();
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>();
//
//    add(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testAddZeroFive {
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>();
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>(5);
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(5);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>(5);
//
//    add(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testAddFiveZero {
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(5);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>();
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(5);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>();
//
//    add(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testAddFourFour {
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(4);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>(4);
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(8);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>(4);
//
//    add(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testAddFiveFive {
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(5);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>(5);
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(10);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>(5);
//
//    add(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testAddTenTen {
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(10);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>(10);
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(20);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>(10);
//
//    add(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testAdd57_66{
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(57);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>(66);
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(123);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>(66);
//
//    add(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testSubtractZeroZero {
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>();
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>();
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>();
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>();
//
//    subtract(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testSubtractFiveZero {
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(5);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>();
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(5);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>();
//
//    subtract(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testSubtractFourFour {
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(4);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>(4);
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(0);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>(4);
//
//    subtract(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testSubtractTenTen {
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(10);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>(10);
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(0);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>(10);
//
//    subtract(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testSubtract77_66{
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(77);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>(66);
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(11);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>(66);
//
//    subtract(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testSubtract77_6{
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(77);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>(6);
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(71);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>(6);
//
//    subtract(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}
//
//- (void)testSubtract71_66{
//    std::unique_ptr<big_integer> n1 = std::make_unique<int_type>(71);
//    std::unique_ptr<big_integer> n2 = std::make_unique<int_type>(66);
//    std::unique_ptr<big_integer> n1_exp = std::make_unique<int_type>(5);
//    std::unique_ptr<big_integer> n2_exp = std::make_unique<int_type>(66);
//
//    subtract(*n1, *n2);
//
//    std::string n1_str = nnToString(n1);
//    std::string n2_str = nnToString(n2);
//    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
//    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
//}

@end
