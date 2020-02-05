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
using namespace std;

typedef stack_nn nn_type;

static string nnToString(unique_ptr<natural_number> &o) {
    stringstream s;
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
    unique_ptr<natural_number> n = make_unique<nn_type>();
    
    string n_str = nnToString(n);
    XCTAssert(n_str == "0");
}

- (void)testInitializer_SingleDig {
    unique_ptr<natural_number> n = make_unique<nn_type>(4);
    
    string n_str = nnToString(n);
    XCTAssert(n_str == "4", @"n = %s", n_str.c_str());
}

- (void)testInitializer_TwoDig {
    unique_ptr<natural_number> n = make_unique<nn_type>(45);
    
    string n_str = nnToString(n);
    XCTAssert(n_str == "45", @"n = %s", n_str.c_str());
}

- (void)testClearZero {
    unique_ptr<natural_number> n = make_unique<nn_type>();
    unique_ptr<natural_number> expected= make_unique<nn_type>(0);
    
    n->clear();
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testClearNonZero {
    unique_ptr<natural_number> n = make_unique<nn_type>(47);
    unique_ptr<natural_number> expected= make_unique<nn_type>(0);
    
    n->clear();
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementZero {
    unique_ptr<natural_number> n = make_unique<nn_type>();
    unique_ptr<natural_number> expected= make_unique<nn_type>(1);
    
    n->increment();
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementNine {
    unique_ptr<natural_number> n = make_unique<nn_type>(9);
    unique_ptr<natural_number> expected= make_unique<nn_type>(10);
    
    n->increment();
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testIncrementFive {
    unique_ptr<natural_number> n = make_unique<nn_type>(5);
    unique_ptr<natural_number> expected= make_unique<nn_type>(6);
    
    n->increment();
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementOne {
    unique_ptr<natural_number> n = make_unique<nn_type>(1);
    unique_ptr<natural_number> expected= make_unique<nn_type>(0);
    
    n->decrement();
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementTen {
    unique_ptr<natural_number> n = make_unique<nn_type>(10);
    unique_ptr<natural_number> expected= make_unique<nn_type>(9);
    
    n->decrement();

    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDecrementFive {
    unique_ptr<natural_number> n = make_unique<nn_type>(5);
    unique_ptr<natural_number> expected= make_unique<nn_type>(4);
    
    n->decrement();
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Zero {
    unique_ptr<natural_number> n = make_unique<nn_type>(0);
    unique_ptr<natural_number> expected= make_unique<nn_type>(0);
    
    n->multiply_by_radix(0);
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadZero_Five {
    unique_ptr<natural_number> n = make_unique<nn_type>(0);
    unique_ptr<natural_number> expected= make_unique<nn_type>(5);

    n->multiply_by_radix(5);
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Zero {
    unique_ptr<natural_number> n = make_unique<nn_type>(5);
    unique_ptr<natural_number> expected= make_unique<nn_type>(50);

    n->multiply_by_radix(0);
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testMultRadFive_Five {
    unique_ptr<natural_number> n = make_unique<nn_type>(5);
    unique_ptr<natural_number> expected= make_unique<nn_type>(55);

    n->multiply_by_radix(5);
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
}

- (void)testDivRadZero {
    unique_ptr<natural_number> n = make_unique<nn_type>(0);
    unique_ptr<natural_number> expected= make_unique<nn_type>(0);

    int d = 4;
    n->divide_by_radix(d);
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFive {
    unique_ptr<natural_number> n = make_unique<nn_type>(5);
    unique_ptr<natural_number> expected= make_unique<nn_type>(0);

    int d = 4;
    n->divide_by_radix(d);
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
    unique_ptr<natural_number> n = make_unique<nn_type>(50);
    unique_ptr<natural_number> expected= make_unique<nn_type>(5);

    int d = 4;
    n->divide_by_radix(d);
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
    unique_ptr<natural_number> n = make_unique<nn_type>(55);
    unique_ptr<natural_number> expected= make_unique<nn_type>(5);

    int d = 4;
    n->divide_by_radix(d);
    
    string n_str = nnToString(n);
    XCTAssert(*n == *expected, @"n = %s", n_str.c_str());
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testAddZeroZero {
    unique_ptr<natural_number> n1 = make_unique<nn_type>();
    unique_ptr<natural_number> n2 = make_unique<nn_type>();
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>();
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>();
    
    add(*n1, *n2);
    
    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddZeroFive {
    unique_ptr<natural_number> n1 = make_unique<nn_type>();
    unique_ptr<natural_number> n2 = make_unique<nn_type>(5);
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(5);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>(5);
    
    add(*n1, *n2);
    
    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveZero {
    unique_ptr<natural_number> n1 = make_unique<nn_type>(5);
    unique_ptr<natural_number> n2 = make_unique<nn_type>();
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(5);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>();
    
    add(*n1, *n2);
    
    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFourFour {
    unique_ptr<natural_number> n1 = make_unique<nn_type>(4);
    unique_ptr<natural_number> n2 = make_unique<nn_type>(4);
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(8);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>(4);
    
    add(*n1, *n2);
    
    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddFiveFive {
    unique_ptr<natural_number> n1 = make_unique<nn_type>(5);
    unique_ptr<natural_number> n2 = make_unique<nn_type>(5);
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(10);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>(5);
    
    add(*n1, *n2);
    
    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAddTenTen {
    unique_ptr<natural_number> n1 = make_unique<nn_type>(10);
    unique_ptr<natural_number> n2 = make_unique<nn_type>(10);
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(20);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>(10);
    
    add(*n1, *n2);
    
    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testAdd57_66{
    unique_ptr<natural_number> n1 = make_unique<nn_type>(57);
    unique_ptr<natural_number> n2 = make_unique<nn_type>(66);
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(123);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>(66);
    
    add(*n1, *n2);
    
    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractZeroZero {
    unique_ptr<natural_number> n1 = make_unique<nn_type>();
    unique_ptr<natural_number> n2 = make_unique<nn_type>();
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>();
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>();
    
    subtract(*n1, *n2);

    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFiveZero {
    unique_ptr<natural_number> n1 = make_unique<nn_type>(5);
    unique_ptr<natural_number> n2 = make_unique<nn_type>();
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(5);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>();
    
    subtract(*n1, *n2);

    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractFourFour {
    unique_ptr<natural_number> n1 = make_unique<nn_type>(4);
    unique_ptr<natural_number> n2 = make_unique<nn_type>(4);
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(0);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>(4);
    
    subtract(*n1, *n2);

    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtractTenTen {
    unique_ptr<natural_number> n1 = make_unique<nn_type>(10);
    unique_ptr<natural_number> n2 = make_unique<nn_type>(10);
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(0);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>(10);
    
    subtract(*n1, *n2);

    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_66{
    unique_ptr<natural_number> n1 = make_unique<nn_type>(77);
    unique_ptr<natural_number> n2 = make_unique<nn_type>(66);
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(11);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>(66);
    
    subtract(*n1, *n2);

    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract77_6{
    unique_ptr<natural_number> n1 = make_unique<nn_type>(77);
    unique_ptr<natural_number> n2 = make_unique<nn_type>(6);
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(71);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>(6);
    
    subtract(*n1, *n2);

    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

- (void)testSubtract71_66{
    unique_ptr<natural_number> n1 = make_unique<nn_type>(71);
    unique_ptr<natural_number> n2 = make_unique<nn_type>(66);
    unique_ptr<natural_number> n1_exp = make_unique<nn_type>(5);
    unique_ptr<natural_number> n2_exp = make_unique<nn_type>(66);
    
    subtract(*n1, *n2);

    string n1_str = nnToString(n1);
    string n2_str = nnToString(n2);
    XCTAssert(*n1 == *n1_exp, @"n = %s", n1_str.c_str());
    XCTAssert(*n2 == *n2_exp, @"n = %s", n2_str.c_str());
}

@end
