//
//  TestCleanpp.m
//  TestCleanpp
//
//  Created by Alan Weide on 11/29/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <stdio.h>
#include <clean_nn/bounded_nn.hpp>

@interface TestBoundedNN : XCTestCase
@end

@implementation TestBoundedNN

using namespace cleanpp;

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testIncrementZero {
    bounded_nn n;
    bounded_nn one(1);
    n.increment();
    XCTAssert(n == one);
}

- (void)testIncrementNine {
    bounded_nn n(9);
    bounded_nn ten(10);
    n.increment();
    XCTAssert(n == ten);
}

- (void)testIncrementFive {
    bounded_nn n(5);
    bounded_nn six(6);
    n.increment();
    XCTAssert(n == six);
}

- (void)testDecrementOne {
    bounded_nn n(1);
    bounded_nn zero(0);
    n.decrement();
    XCTAssert(n == zero);
}

- (void)testDecrementTen {
    bounded_nn n(10);
    bounded_nn nine(9);
    n.decrement();
    XCTAssert(n == nine);
}

- (void)testDecrementFive {
    bounded_nn n(5);
    bounded_nn four(4);
    n.decrement();
    XCTAssert(n == four);
}

@end
