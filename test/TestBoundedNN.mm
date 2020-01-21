//
//  TestCleanpp.m
//  TestCleanpp
//
//  Created by Alan Weide on 11/29/19.
//  Copyright © 2019 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>
//#include "CleanQueue.hpp"
//#include "CleanStack.hpp"
#include "BoundedNN.hpp"
//#include "BoundedQueue.hpp"
#include <stdio.h>

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
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    std::unique_ptr<natural_number> n = std::make_unique<bounded_nn>();
    std::unique_ptr<natural_number> one = std::make_unique<bounded_nn>(1);
    n->increment();
    XCTAssert(*n == *one);
}

- (void)testIncrementNine {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    std::unique_ptr<natural_number> n = std::make_unique<bounded_nn>(9);
    std::unique_ptr<natural_number> ten = std::make_unique<bounded_nn>(10);
    n->increment();
    XCTAssert(*n == *ten);
}

- (void)testDecrementOne {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    std::unique_ptr<natural_number> n = std::make_unique<bounded_nn>(1);
    std::unique_ptr<natural_number> zero = std::make_unique<bounded_nn>(0);
    n->decrement();
    XCTAssert(*n == *zero);
}

- (void)testDecrementTen {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    std::unique_ptr<natural_number> n = std::make_unique<bounded_nn>(10);
    std::unique_ptr<natural_number> nine = std::make_unique<bounded_nn>(9);
    n->decrement();
    XCTAssert(*n == *nine);
}

@end
