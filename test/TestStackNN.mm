//
//  TestStackNN.m
//  TestStackNN
//
//  Created by Alan Weide on 11/29/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <clean_nn/stack_nn.hpp>

@interface TestStackNN : XCTestCase
@end

@implementation TestStackNN

using namespace cleanpp;

typedef stack_nn nn_type;

static std::string nnPtrToString(std::unique_ptr<natural_number_secondary> &o) {
	std::stringstream s;
    s << *o;
    return s.str();
}

static std::string nnToString(nn_type &o) {
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
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(n_str == "0");
}

- (void)testInitializer_SingleDig {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(4);
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
}

- (void)testInitializer_TwoDig {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(45);
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
}

- (void)testMoveInit_Zero {
	nn_type m, m_expected;
	std::unique_ptr<natural_number_secondary> n_expected = std::make_unique<nn_type>();
	
	std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(std::move(m));
	
	std::string n_str = nnPtrToString(n);
	XCTAssert(*n == *n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected);
}

- (void)testMoveInit_SingleDig {
	nn_type m(5), m_expected;
	std::unique_ptr<natural_number_secondary> n_expected = std::make_unique<nn_type>(5);
	
	std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(std::move(m));
	
	std::string n_str = nnPtrToString(n);
	XCTAssert(*n == *n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected);
}

- (void)testMoveInit_MultiDig {
	nn_type m(76), m_expected;
	std::unique_ptr<natural_number_secondary> n_expected = std::make_unique<nn_type>(76);
	
	std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(std::move(m));
	
	std::string n_str = nnPtrToString(n);
	XCTAssert(*n == *n_expected, @"n = %s", n_str.c_str());
	XCTAssert(m == m_expected);
}

- (void)testAssign_ZeroToZero {
	nn_type n, m, n_exp, m_exp;
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_exp, @"n = %s", n_str.c_str());
	XCTAssert(m == m_exp, @"m = %s", m_str.c_str());
}

- (void)testAssign_ZeroToNonZero {
	nn_type n(5), m, n_exp, m_exp;
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_exp, @"n = %s", n_str.c_str());
	XCTAssert(m == m_exp, @"m = %s", m_str.c_str());
}

- (void)testAssign_NonzeroToZero {
	nn_type n, m(5), n_exp(5), m_exp;
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_exp, @"n = %s", n_str.c_str());
	XCTAssert(m == m_exp, @"m = %s", m_str.c_str());
}

- (void)testAssign_NonzeroToNonzero {
	nn_type n(3), m(5), n_exp(5), m_exp(0);
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_exp, @"n = %s", n_str.c_str());
	XCTAssert(m == m_exp, @"m = %s", m_str.c_str());
}

- (void)testAssign_MultidigToZero {
	nn_type n, m(76), n_exp(76), m_exp;
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_exp, @"n = %s", n_str.c_str());
	XCTAssert(m == m_exp, @"m = %s", m_str.c_str());
}


- (void)testAssign_MultidigToMultidig {
	nn_type n(89), m(76), n_exp(76), m_exp;
	
	n = std::move(m);
	
	std::string n_str = nnToString(n);
	std::string m_str = nnToString(m);
	XCTAssert(n == n_exp, @"n = %s", n_str.c_str());
	XCTAssert(m == m_exp, @"m = %s", m_str.c_str());
}

- (void)testClearZero {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(0);
    
    n->clear();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testClearNonZero {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(47);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(0);
    
    n->clear();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(1);
    
    n->increment();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(9);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(10);
    
    n->increment();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(6);
    
    n->increment();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(1);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(0);
    
    n->decrement();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(9);
    
    n->decrement();

    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(4);
    
    n->decrement();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(0);
    
    n->multiply_by_radix(0);
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(5);

    n->multiply_by_radix(5);
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(50);

    n->multiply_by_radix(0);
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(55);

    n->multiply_by_radix(5);
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(0);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFive {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(0);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(50);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(5);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
    std::unique_ptr<natural_number_secondary> n = std::make_unique<nn_type>(55);
    std::unique_ptr<natural_number_secondary> expected= std::make_unique<nn_type>(5);

    int d = 4;
    d = n->divide_by_radix();
    
    std::string n_str = nnPtrToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testAddZeroZero {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>();
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroFive {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(5);
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>();
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourFour {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(8);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(4);
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveFive {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(5);
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddTenTen {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(20);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(10);
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_66{
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(57);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(123);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(66);
    
    n1 = add(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractZeroZero {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>();
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFiveZero {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>();
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>();
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourFour {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(4);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(4);
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractTenTen {
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(10);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(0);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(10);
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_66{
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(11);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(66);
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_6{
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(77);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(6);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(71);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(6);
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract71_66{
    std::unique_ptr<natural_number_secondary> n1 = std::make_unique<nn_type>(71);
    std::unique_ptr<natural_number_secondary> n2 = std::make_unique<nn_type>(66);
    std::unique_ptr<natural_number_secondary> n1_exp = std::make_unique<nn_type>(5);
    std::unique_ptr<natural_number_secondary> n2_exp = std::make_unique<nn_type>(66);
    
    n1 = subtract(std::move(n1), n2);

    std::string n1_str = nnPtrToString(n1);
    std::string n2_str = nnPtrToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

@end
