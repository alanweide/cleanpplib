//
//  TestTemplateStackInt.m
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
#include <template_stack/template_stack.hpp>

@interface TestTemplateStackInt : XCTestCase

@end

@implementation TestTemplateStackInt

using namespace cleanpp;

typedef linked_stack<int> stack_type;
typedef t_stack<linked_stack, int> template_st;

template<template<class> class I, class Item>
static std::string stackToString(t_stack<I, Item> &s) {
    std::stringstream s_stm;
    s_stm << s;
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
    template_st s;
    std::string empty_stack = "<>";
    std::string s_str = stackToString(s);
    XCTAssert(s_str == empty_stack, @"%s", s_str.c_str());
}

- (void)testIsEmpty_Empty {
    template_st s;
    XCTAssert(s.is_empty());
}

- (void)testIsEmpty_NonEmpty {
    template_st s;
    int a(1);
    s.push(std::move(a));
    XCTAssert(!s.is_empty());
}

- (void)testIsEmpty_Empty_PushPop {
    template_st s;
    int a(1), b(2);
    s.push(std::move(a));
    b = s.pop();
    XCTAssert(s.is_empty());
}

- (void)testPushToEmpty {
    template_st s;
    std::string expected_stack = "<1>";
    
    int a(1);
    s.push(std::move(a));
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPushToNonEmpty {
    template_st s;
    std::string expected_stack = "<2, 1>";
    
    int a(1), b(2);
    s.push(std::move(a));
    s.push(std::move(b));
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPopEmptyToEmpty {
    template_st s;
    std::string expected_stack = "<>";
    int expected_a(1);
    
    int a(1), b(2);
    s.push(std::move(a));
    b = s.pop();
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(a == expected_a);
}

- (void)testPopNonEmptyToEmpty {
    template_st s;
    std::string expected_stack = "<>";
    int expected_b(1);
    
    int a(1), b(2);
    s.push(std::move(a));
    b = s.pop();
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(b == expected_b);
}

- (void)testClearEmpty {
    template_st s;
    std::string expected_stack = "<>";
    
    s.clear();
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testClearNonempty {
    template_st s;
    std::string expected_stack = "<>";
    s.push(1);
    
    s.clear();
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

@end
