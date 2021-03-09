//
//  TestFlexibleStackInt.m
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
#include <clean_stack/stack.hpp>

@interface TestFlexibleStackInt : XCTestCase

@end

@implementation TestFlexibleStackInt

using namespace cleanpp;

typedef int item_type;
typedef linked_stack<item_type> impl_type;
typedef array_stack<item_type> impl_type2;
typedef stack<item_type> stack_type;

template<class Item>
static std::string stackToString(stack<Item> &s) {
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
    stack<item_type> s(impl_type{});
    std::string empty_stack = "<>";
    std::string s_str = stackToString(s);
    XCTAssert(s_str == empty_stack, @"%s", s_str.c_str());
}

- (void)testIsEmpty_Empty {
    stack<item_type> s(impl_type{});
    XCTAssert(s.is_empty());
}

- (void)testIsEmpty_NonEmpty {
    stack<item_type> s(impl_type{});
    int a(1);
    s.push(std::move(a));
    XCTAssert(!s.is_empty());
}

- (void)testIsEmpty_Empty_PushPop {
    stack<item_type> s(impl_type{});
    int a(1), b(2);
    s.push(std::move(a));
    b = s.pop();
    XCTAssert(s.is_empty());
}

- (void)testPushToEmpty {
    stack<item_type> s(impl_type{});
    std::string expected_stack = "<1>";
    
    int a(1);
    s.push(std::move(a));
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPushToNonEmpty {
    stack<item_type> s(impl_type{});
    std::string expected_stack = "<2, 1>";
    
    int a(1), b(2);
    s.push(std::move(a));
    s.push(std::move(b));
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPopEmptyToEmpty {
    stack<item_type> s(impl_type{});
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
    stack<item_type> s(impl_type{});
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
    stack<item_type> s(impl_type{});
    std::string expected_stack = "<>";
    
    s.clear();
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testClearNonempty {
    stack<item_type> s(impl_type{});
    std::string expected_stack = "<>";
    s.push(1);
    
    s.clear();
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testAssignEmptyEmpty {
    stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<>", t_exp = "<>";
    
    s = std::move(t);
    
    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
    XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignEmptyNonempty {
    stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<>", t_exp = "<>";
    s.push(1);
    
    s = std::move(t);
    
    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
    XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignNonemptyEmpty {
    stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<1>", t_exp = "<>";
    t.push(1);
    
    s = std::move(t);
    
    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
    XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignNonemptyNonempty {
    stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<1>", t_exp = "<>";
    s.push(2);
    t.push(1);
    
    s = std::move(t);
    
    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
    XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignEmptyEmptyMultiImpl {
	stack<item_type> s(impl_type{}), t(impl_type2{});
	std::string s_exp = "<>", t_exp = "<>";
	
	s = std::move(t);
	
	std::string s_str = stackToString(s);
	std::string t_str = stackToString(t);
	XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
	XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignEmptyNonemptyMultiImpl {
	stack<item_type> s(impl_type{}), t(impl_type2{});
	std::string s_exp = "<>", t_exp = "<>";
	s.push(1);
	
	s = std::move(t);
	
	std::string s_str = stackToString(s);
	std::string t_str = stackToString(t);
	XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
	XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignNonemptyEmptyMultiImpl {
	stack<item_type> s(impl_type{}), t(impl_type2{});
	std::string s_exp = "<1>", t_exp = "<>";
	t.push(1);
	
	s = std::move(t);
	
	std::string s_str = stackToString(s);
	std::string t_str = stackToString(t);
	XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
	XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignNonemptyNonemptyMultiImpl {
	stack<item_type> s(impl_type{}), t(impl_type2{});
	std::string s_exp = "<1>", t_exp = "<>";
	s.push(2);
	t.push(1);
	
	s = std::move(t);
	
	std::string s_str = stackToString(s);
	std::string t_str = stackToString(t);
	XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
	XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

@end
