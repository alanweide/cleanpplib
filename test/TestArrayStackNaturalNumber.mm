//
//  TestLinkedStackNaturalNumber.m
//  TestCleanpp
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <stack_impls/linked_stack.hpp>
#include <stack_impls/array_stack.hpp>
#include <natural_number_impls/bounded_nn.hpp>
#include <natural_number_impls/stack_nn.hpp>

@interface TestArrayStackNaturalNumber : XCTestCase

@end

@implementation TestArrayStackNaturalNumber

using namespace cleanpp;

typedef stack_nn nn_type;
typedef array_stack<nn_type> stack_nn_type;

static std::string stackNNToString(std::unique_ptr<stack_impl<nn_type>> &s) {
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
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string empty_stack = "<>";
    std::string s_str = stackNNToString(s);
    XCTAssert(s_str == empty_stack, @"%s", s_str.c_str());
}

- (void)testIsEmpty_Empty {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    XCTAssert(s->is_empty());
}

- (void)testIsEmpty_NonEmpty {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    nn_type a(1);
    s->push(std::move(a));
    XCTAssert(!s->is_empty());
}

- (void)testIsEmpty_Empty_PushPop {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    nn_type a(1), b(2);
    s->push(std::move(a));
    b = s->pop();
    XCTAssert(s->is_empty());
}

- (void)testPushToEmpty {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<1>";
    
    nn_type a(1);
    s->push(std::move(a));
    
    std::string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPushToNonEmpty {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<2, 1>";
    
    nn_type a(1), b(2);
    s->push(std::move(a));
    s->push(std::move(b));
    
    std::string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPopEmptyToEmpty {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<>";
    nn_type expected_a(0);
    
    nn_type a(1), b(2);
    s->push(std::move(a));
    b = s->pop();
    
    std::string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(a == expected_a);
}

- (void)testPopNonEmptyToEmpty {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    std::string expected_stack = "<>";
    nn_type expected_b(1);
    
    nn_type a(1), b(2);
    s->push(std::move(a));
    b = s->pop();
    
    std::string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(b == expected_b);
}

- (void)testNonMonotonicResizing {
    std::unique_ptr<stack_impl<nn_type>> s = std::make_unique<stack_nn_type>();
    nn_type expected_b(1);
    
    const int cap = 100;
    for (int i = 0; i < cap; i++) {
        nn_type n(i);
        s->push(std::move(n));
    }
    while (!s->is_empty()) {
        nn_type n;
        n = s->pop();
    }
    
    XCTAssert(s->is_empty());
}

@end
