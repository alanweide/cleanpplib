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

@interface TestCleanpp : XCTestCase
@end

@implementation TestCleanpp

using namespace cleanpp;

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
//    std::unique_ptr<cleanpp::natural_number> n = std::make_unique<cleanpp::bounded_nn>();
    
    bounded_nn n;
    n.increment();
    //    bounded_queue<std::string> q;
	
}

@end
