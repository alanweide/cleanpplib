//
//  TestLinkedStackInt.m
//  TestCleanpp
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <clean_stack/linked_stack.hpp>
#include <clean_nn/bounded_nn.hpp>
#include <clean_nn/stack_nn.hpp>

@interface TestLinkedStackInt : XCTestCase

@end

@implementation TestLinkedStackInt

using namespace cleanpp;

typedef linked_stack<int> stack_type;

static std::string stackNNToString(std::unique_ptr<stack<int>> &s) {
    std::stringstream s_stm;
    s_stm << *s;
    std::string s_str = s_stm.str();
    return s_str;
}

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testInitializerDef {
    std::unique_ptr<stack<int>> s = std::make_unique<stack_type>();
    std::string empty_stack = "<>";
    std::string s_str = stackNNToString(s);
    XCTAssert(s_str == empty_stack, @"%s", s_str.c_str());
}

- (void)testIsEmpty_Empty {
    std::unique_ptr<stack<int>> s = std::make_unique<stack_type>();
    XCTAssert(s->is_empty());
}

- (void)testIsEmpty_NonEmpty {
    std::unique_ptr<stack<int>> s = std::make_unique<stack_type>();
    int a(1);
    s->push(std::move(a));
    XCTAssert(!s->is_empty());
}

- (void)testIsEmpty_Empty_PushPop {
    std::unique_ptr<stack<int>> s = std::make_unique<stack_type>();
    int a(1), b(2);
    s->push(std::move(a));
    b = s->pop();
    XCTAssert(s->is_empty());
}

- (void)testPushToEmpty {
    std::unique_ptr<stack<int>> s = std::make_unique<stack_type>();
    std::string expected_stack = "<1>";
    
    int a(1);
    s->push(std::move(a));
    
    std::string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPushToNonEmpty {
    std::unique_ptr<stack<int>> s = std::make_unique<stack_type>();
    std::string expected_stack = "<2, 1>";
    
    int a(1), b(2);
    s->push(std::move(a));
    s->push(std::move(b));
    
    std::string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPopEmptyToEmpty {
    std::unique_ptr<stack<int>> s = std::make_unique<stack_type>();
    std::string expected_stack = "<>";
    int expected_a(1);
    
    int a(1), b(2);
    s->push(std::move(a));
    b = s->pop();
    
    std::string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(a == expected_a);
}

- (void)testPopNonEmptyToEmpty {
    std::unique_ptr<stack<int>> s = std::make_unique<stack_type>();
    std::string expected_stack = "<>";
    int expected_b(1);
    
    int a(1), b(2);
    s->push(std::move(a));
    b = s->pop();
    
    std::string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(b == expected_b);
}

@end
