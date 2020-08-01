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
#include <clean_nn/bounded_nn.hpp>
#include <template_nn/template_nn.hpp>

@interface TestTemplateNN: XCTestCase
@end

@implementation TestTemplateNN

using namespace cleanpp;

typedef bounded_nn nn_type;

typedef t_natural_number_secondary<bounded_nn> template_t;

static std::string nnToString(template_t &o) {
    std::stringstream s;
    s << o;
    return s.str();
}

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
//    template_t n;
//    n.is_zero();
//	XCTAssert(n.is_zero());
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testInitializerDef {
    template_t n;
    
    std::string n_str = nnToString(n);
    XCTAssert(n_str == "0");
}

- (void)testInitializer_SingleDig {
	template_t n(4);

    std::string n_str = nnToString(n);
    XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
}

- (void)testInitializer_TwoDig {
	template_t n(45);

    std::string n_str = nnToString(n);
    XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
}

- (void)testClearZero {
	template_t n;
	template_t expected(0);

	n.clear();
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testClearNonZero {
	template_t n(47);
	template_t expected(0);

	n.clear();
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
	template_t n;
	template_t expected(1);
    
	n.increment();
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
	template_t n(9);
	template_t expected(10);

	n.increment();
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
	template_t n(5);
	template_t expected(6);

	n.increment();
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
	template_t n(1);
	template_t expected(0);

	n.decrement();
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
	template_t n(10);
	template_t expected(9);

	n.decrement();

    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
	template_t n(5);
	template_t expected(4);

	n.decrement();
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
	template_t n(0);
	template_t expected(0);

	n.multiply_by_radix(0);
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
	template_t n(0);
	template_t expected(5);

	n.multiply_by_radix(5);
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
	template_t n(5);
	template_t expected(50);

	n.multiply_by_radix(0);
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
	template_t n(5);
	template_t expected(55);

	n.multiply_by_radix(5);
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
	template_t n(5);
	template_t expected(6);

    int d = 4;
	n.divide_by_radix(d);
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFive {
	template_t n(5);
	template_t expected(0);

    int d = 4;
	n.divide_by_radix(d);
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
	template_t n(50);
	template_t expected(5);

    int d = 4;
	n.divide_by_radix(d);
    
    std::string n_str = nnToString(n);
    XCTAssert(n == expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
	template_t n(55);
	template_t expected(5);

    int d = 4;
	n.divide_by_radix(d);
    
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

    add(n1, n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
	template_t n1(5);
	template_t n2(0);
	template_t n1_exp(5);
	template_t n2_exp(0);

    add(n1, n2);

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

    add(n1, n2);

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

    add(n1, n2);

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

    add(n1, n2);

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

    add(n1, n2);

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

    subtract(n1, n2);

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

    subtract(n1, n2);

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

    subtract(n1, n2);

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

    subtract(n1, n2);

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

    subtract(n1, n2);

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

    subtract(n1, n2);

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

    subtract(n1, n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(n1 == n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(n2 == n2_exp, @"n = %s", n2_str.c_str());
}

@end
