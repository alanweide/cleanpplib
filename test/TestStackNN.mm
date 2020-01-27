//
//  TestCleanpp.m
//  TestCleanpp
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

static string nnToString(stack_nn &o) {
    stringstream s;
    s << o;
    return s.str();
}

static NSString *stringToNSString(const string &n_str) {
    NSString *n_ns = [NSString stringWithCString:n_str.c_str() encoding:[NSString defaultCStringEncoding]];
    return n_ns;
}

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testInitializerDef {
    stack_nn n;
    string n_str = nnToString(n);
    XCTAssert(n_str == "0");
}

- (void)testInitializer_SingleDig {
    stack_nn n(4);
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n_str == "4", @"n = %@", n_ns);
}

- (void)testInitializer_TwoDig {
    stack_nn n(45);
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n_str == "45", @"n = %@", n_ns);
}

- (void)testIncrementZero {
    stack_nn n;
    stack_nn expected(1);
    n.increment();
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
}

- (void)testIncrementNine {
    stack_nn n(9);
    stack_nn expected(10);
    n.increment();
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
}

- (void)testIncrementFive {
    stack_nn n(5);
    stack_nn expected(6);
    n.increment();
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
}

- (void)testDecrementOne {
    stack_nn n(1);
    stack_nn expected(0);
    n.decrement();
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
}

- (void)testDecrementTen {
    stack_nn n(10);
    stack_nn expected(9);
    n.decrement();
//    std::cout << "n = " << n << "\n";
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
}

- (void)testDecrementFive {
    stack_nn n(5);
    stack_nn expected(4);
    n.decrement();
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
}

- (void)testMultRadZero_Zero {
    stack_nn n(0);
    stack_nn expected(0);
    n.multiply_by_radix(0);
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
}

- (void)testMultRadZero_Five {
    stack_nn n(0);
    stack_nn expected(5);
    
    n.multiply_by_radix(5);
    
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
}

- (void)testMultRadFive_Zero {
    stack_nn n(5);
    stack_nn expected(50);
    
    n.multiply_by_radix(0);
    
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
}

- (void)testMultRadFive_Five {
    stack_nn n(5);
    stack_nn expected(55);
    
    n.multiply_by_radix(5);
    
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
}

- (void)testDivRadZero {
    stack_nn n(0);
    stack_nn expected(0);
    
    int d = 4;
    n.divide_by_radix(d);
    
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
    XCTAssert(d == 0);
}

- (void)testDivRadFive {
    stack_nn n(5);
    stack_nn expected(0);
    
    int d = 4;
    n.divide_by_radix(d);
    
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
    XCTAssert(d == 5, @"d = %d", d);
}

- (void)testDiveRadFifty {
    stack_nn n(50);
    stack_nn expected(5);
    
    int d = 4;
    n.divide_by_radix(d);
    
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
    XCTAssert(d == 0);
}

- (void)testDivRadFiftyFive {
    stack_nn n(55);
    stack_nn expected(5);
    
    int d = 4;
    n.divide_by_radix(d);
    
    string n_str = nnToString(n);
    NSString * n_ns = stringToNSString(n_str);
    XCTAssert(n == expected, @"n = %@", n_ns);
    XCTAssert(d == 5, @"d = %d", d);
}

@end
