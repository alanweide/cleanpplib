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
#include <clean_nn/stack_nn.hpp>

@interface TestLinkedStackNaturalNumber : XCTestCase

@end

@implementation TestLinkedStackNaturalNumber

using namespace cleanpp;
using namespace std;

static NSString *stringToNSString(const std::string &s_str) {
    NSString *s_ns = [NSString stringWithCString:s_str.c_str() encoding:[NSString defaultCStringEncoding]];
    return s_ns;
}

static std::string stackNNToString(linked_stack<stack_nn> &s) {
    stringstream s_stm;
    s_stm << s;
    string s_str = s_stm.str();
    return s_str;
}

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

//+ (NSString*)stringFromStackInt:(linked_stack<int>)

- (void)testInitializerDef {
    linked_stack<stack_nn> s{};
    string empty_stack = "<>";
    std::string s_str = stackNNToString(s);
    NSString * s_ns = stringToNSString(s_str);
    XCTAssert(s_str == empty_stack, @"%@", s_ns);
}

- (void)testIsEmpty_Empty {
    linked_stack<stack_nn> s{};
    XCTAssert(s.is_empty());
}

- (void)testIsEmpty_NonEmpty {
    linked_stack<stack_nn> s{};
    stack_nn a(1);
    s.push(a);
    XCTAssert(!s.is_empty());
}

- (void)testIsEmpty_Empty_PushPop {
    linked_stack<stack_nn> s{};
    stack_nn a(1), b(2);
    s.push(a);
    s.pop(b);
    XCTAssert(s.is_empty());
}

- (void)testPushToEmpty {
    linked_stack<stack_nn> s{};
    string expected_stack = "<1>";
    
    stack_nn a(1);
    s.push(a);
    
    std::string s_str = stackNNToString(s);
    NSString * s_ns = stringToNSString(s_str);
    XCTAssert(s_str == expected_stack, @"%@", s_ns);
}

- (void)testPushToNonEmpty {
    linked_stack<stack_nn> s{};
    string expected_stack = "<2, 1>";
    
    stack_nn a(1), b(2);
    s.push(a);
    s.push(b);
    
    std::string s_str = stackNNToString(s);
    NSString * s_ns = stringToNSString(s_str);
    XCTAssert(s_str == expected_stack, @"%@", s_ns);
}

- (void)testPopEmptyToEmpty {
    linked_stack<stack_nn> s{};
    string expected_stack = "<>";
    stack_nn expected_a(0);
    
    stack_nn a(1), b(2);
    s.push(a);
    s.pop(b);
    
    std::string s_str = stackNNToString(s);
    NSString * s_ns = stringToNSString(s_str);
    XCTAssert(s_str == expected_stack, @"%@", s_ns);
    XCTAssert(a == expected_a);
}

- (void)testPopNonEmptyToEmpty {
    linked_stack<stack_nn> s{};
    string expected_stack = "<>";
    stack_nn expected_b(1);
    
    stack_nn a(1), b(2);
    s.push(a);
    s.pop(b);
    
    std::string s_str = stackNNToString(s);
    NSString * s_ns = stringToNSString(s_str);
    XCTAssert(s_str == expected_stack, @"%@", s_ns);
    XCTAssert(b == expected_b);
}

@end
