//
//  TestCleanpp.m
//  TestCleanpp
//
//  Created by Alan Weide on 11/29/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <stack_nn.hpp>
#include <stdio.h>

@interface TestStackNN : XCTestCase
@end

@implementation TestStackNN

using namespace cleanpp;

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testIncrementZero {
    std::unique_ptr<natural_number> n = std::make_unique<stack_nn>();
    std::unique_ptr<natural_number> one = std::make_unique<stack_nn>(1);
    n->increment();
    XCTAssert(*n == *one);
}

- (void)testIncrementNine {
    std::unique_ptr<natural_number> n = std::make_unique<stack_nn>(9);
    std::unique_ptr<natural_number> ten = std::make_unique<stack_nn>(10);
    n->increment();
    XCTAssert(*n == *ten);
}

- (void)testIncrementFive {
    std::unique_ptr<natural_number> n = std::make_unique<stack_nn>(5);
    std::unique_ptr<natural_number> six = std::make_unique<stack_nn>(6);
    n->increment();
    XCTAssert(*n == *six);
}

- (void)testDecrementOne {
    std::unique_ptr<natural_number> n = std::make_unique<stack_nn>(1);
    std::unique_ptr<natural_number> zero = std::make_unique<stack_nn>(0);
    n->decrement();
    XCTAssert(*n == *zero);
}

- (void)testDecrementTen {
    std::unique_ptr<natural_number> n = std::make_unique<stack_nn>(10);
    std::unique_ptr<natural_number> nine = std::make_unique<stack_nn>(9);
    n->decrement();
    XCTAssert(*n == *nine);
}

- (void)testDecrementFive {
    std::unique_ptr<natural_number> n = std::make_unique<stack_nn>(5);
    std::unique_ptr<natural_number> four = std::make_unique<stack_nn>(4);
    n->decrement();
    XCTAssert(*n == *four);
}

@end
