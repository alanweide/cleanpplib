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

static std::string nnToString(std::unique_ptr<natural_number_secondary> &o) {
	std::stringstream s;
	s << *o;
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
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_secondary> expected = std::make_unique<nn_type>(0);
    
    n->multiply_by_radix(0);
    
    std::string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_secondary> expected = std::make_unique<nn_type>(5);

    n->multiply_by_radix(5);
    
    std::string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> expected = std::make_unique<nn_type>(50);

    n->multiply_by_radix(0);
    
    std::string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> expected = std::make_unique<nn_type>(55);

    n->multiply_by_radix(5);
    
    std::string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_secondary> expected = std::make_unique<nn_type>(0);

    int d = 4;
    n->divide_by_radix(d);
    
    std::string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFive {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> expected = std::make_unique<nn_type>(0);

    int d = 4;
    n->divide_by_radix(d);
    
    std::string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(50);
    std::unique_ptr<natural_number_secondary> expected = std::make_unique<nn_type>(5);

    int d = 4;
    n->divide_by_radix(d);
    
    std::string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(55);
    std::unique_ptr<natural_number_secondary> expected = std::make_unique<nn_type>(5);

    int d = 4;
    n->divide_by_radix(d);
    
    std::string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testAddZeroZero {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>();
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroFive {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(5);
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>();
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourFour {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(8);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(4);
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveFive {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(5);
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddTenTen {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(20);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(10);
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_66{
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(57);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(123);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(66);
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractZeroZero {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>();
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFiveZero {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>();
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourFour {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(4);
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractTenTen {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(10);
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_66{
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(11);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(66);
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_6{
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(6);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(71);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(6);
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract71_66{
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(71);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(66);
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnToString(n1);
    std::string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

@end
