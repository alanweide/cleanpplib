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

@interface TestLinkedStackNaturalNumber : XCTestCase

@end

@implementation TestLinkedStackNaturalNumber

using namespace cleanpp;
using namespace std;

static string stackNNToString(unique_ptr<clean_stack<bounded_nn>> &s) {
    stringstream s_stm;
    s_stm << *static_cast<linked_stack<bounded_nn> *>(s.get());
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
    std::unique_ptr<clean_stack<bounded_nn>> s = std::make_unique<linked_stack<bounded_nn>>();
    string empty_stack = "<>";
    string s_str = stackNNToString(s);
    XCTAssert(s_str == empty_stack, @"%s", s_str.c_str());
}

- (void)testIsEmpty_Empty {
    unique_ptr<clean_stack<bounded_nn>> s = make_unique<linked_stack<bounded_nn>>();
    XCTAssert(s->is_empty());
}

- (void)testIsEmpty_NonEmpty {
    unique_ptr<clean_stack<bounded_nn>> s = make_unique<linked_stack<bounded_nn>>();
    bounded_nn a(1);
    s->push(a);
    XCTAssert(!s->is_empty());
}

- (void)testIsEmpty_Empty_PushPop {
    unique_ptr<clean_stack<bounded_nn>> s = make_unique<linked_stack<bounded_nn>>();
    bounded_nn a(1), b(2);
    s->push(a);
    s->pop(b);
    XCTAssert(s->is_empty());
}

- (void)testPushToEmpty {
    unique_ptr<clean_stack<bounded_nn>> s = make_unique<linked_stack<bounded_nn>>();
    string expected_stack = "<1>";
    
    bounded_nn a(1);
    s->push(a);
    
    string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPushToNonEmpty {
    unique_ptr<clean_stack<bounded_nn>> s = make_unique<linked_stack<bounded_nn>>();
    string expected_stack = "<2, 1>";
    
    bounded_nn a(1), b(2);
    s->push(a);
    s->push(b);
    
    string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPopEmptyToEmpty {
    unique_ptr<clean_stack<bounded_nn>> s = make_unique<linked_stack<bounded_nn>>();
    string expected_stack = "<>";
    bounded_nn expected_a(0);
    
    bounded_nn a(1), b(2);
    s->push(a);
    s->pop(b);
    
    string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(a == expected_a);
}

- (void)testPopNonEmptyToEmpty {
    unique_ptr<clean_stack<bounded_nn>> s = make_unique<linked_stack<bounded_nn>>();
    string expected_stack = "<>";
    bounded_nn expected_b(1);
    
    bounded_nn a(1), b(2);
    s->push(a);
    s->pop(b);
    
    string s_str = stackNNToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(b == expected_b);
}

@end
