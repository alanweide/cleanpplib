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
#include <clean_stack/linked_stack.hpp>
#include <clean_nn/bounded_nn.hpp>
#include <clean_nn/stack_nn.hpp>

@interface TestLinkedStackNaturalNumber : XCTestCase

@end

@implementation TestLinkedStackNaturalNumber

using namespace cleanpp;
using namespace std;

typedef stack_nn nn_type;
typedef linked_stack<nn_type> stack_nn_type;

static string stackNNToString(unique_ptr<clean_stack<nn_type>> &s) {
    stringstream s_stm;
    s_stm << *s;
    string s_str = s_stm.str();
    return s_str;
}

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testInitializerDef {
    std::unique_ptr<clean_stack<nn_type>> s = std::make_unique<stack_nn_type>();
    string empty_stack = "<>";
    string s_str = stackNNToString(s);
    XCTAssert(s_str == empty_stack, @"%s", s_str.c_str());
}

- (void)testIsEmpty_Empty {
    std::unique_ptr<clean_stack<nn_type>> s = std::make_unique<stack_nn_type>();
    XCTAssert(s->is_empty());
}

- (void)testIsEmpty_NonEmpty {
    std::unique_ptr<clean_stack<nn_type>> s = std::make_unique<stack_nn_type>();
    nn_type a(1);
    s->push(a);
    XCTAssert(!s->is_empty());
}

- (void)testIsEmpty_Empty_PushPop {
    std::unique_ptr<clean_stack<nn_type>> s = std::make_unique<stack_nn_type>();
    nn_type a(1), b(2);
    s->push(a);
    s->pop(b);
    XCTAssert(s->is_empty());
}

- (void)testPushToEmpty {
    std::unique_ptr<clean_stack<nn_type>> s = std::make_unique<stack_nn_type>();
    string expected_stack = "<1>";
    
    nn_type a(1);
    s->push(a);
    
    string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPushToNonEmpty {
    std::unique_ptr<clean_stack<nn_type>> s = std::make_unique<stack_nn_type>();
    string expected_stack = "<2, 1>";
    
    nn_type a(1), b(2);
    s->push(a);
    s->push(b);
    
    string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPopEmptyToEmpty {
    std::unique_ptr<clean_stack<nn_type>> s = std::make_unique<stack_nn_type>();
    string expected_stack = "<>";
    nn_type expected_a(0);
    
    nn_type a(1), b(2);
    s->push(a);
    s->pop(b);
    
    string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(a == expected_a);
}

- (void)testPopNonEmptyToEmpty {
    std::unique_ptr<clean_stack<nn_type>> s = std::make_unique<stack_nn_type>();
    string expected_stack = "<>";
    nn_type expected_b(1);
    
    nn_type a(1), b(2);
    s->push(a);
    s->pop(b);
    
    string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(b == expected_b);
}

@end
