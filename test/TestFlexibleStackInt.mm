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
#include <clean_stack/linked_stack.hpp>
#include <clean_stack/array_stack.hpp>
#include <flexible_stack/flexible_stack.hpp>

@interface TestFlexibleStackInt : XCTestCase

@end

@implementation TestFlexibleStackInt

using namespace cleanpp;

typedef int item_type;
typedef linked_stack<item_type> impl_type;
typedef array_stack<item_type> impl_type2;
typedef flex_stack<item_type> stack_type;

template<class Item>
static std::string stackToString(flex_stack<Item> &s) {
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
    flex_stack<item_type> s(impl_type{});
    std::string empty_stack = "<>";
    std::string s_str = stackToString(s);
    XCTAssert(s_str == empty_stack, @"%s", s_str.c_str());
}

- (void)testIsEmpty_Empty {
    flex_stack<item_type> s(impl_type{});
    XCTAssert(s.is_empty());
}

- (void)testIsEmpty_NonEmpty {
    flex_stack<item_type> s(impl_type{});
    int a(1);
    s.push(std::move(a));
    XCTAssert(!s.is_empty());
}

- (void)testIsEmpty_Empty_PushPop {
    flex_stack<item_type> s(impl_type{});
    int a(1), b(2);
    s.push(std::move(a));
    b = s.pop();
    XCTAssert(s.is_empty());
}

- (void)testPushToEmpty {
    flex_stack<item_type> s(impl_type{});
    std::string expected_stack = "<1>";
    
    int a(1);
    s.push(std::move(a));
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPushToNonEmpty {
    flex_stack<item_type> s(impl_type{});
    std::string expected_stack = "<2, 1>";
    
    int a(1), b(2);
    s.push(std::move(a));
    s.push(std::move(b));
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPopEmptyToEmpty {
    flex_stack<item_type> s(impl_type{});
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
    flex_stack<item_type> s(impl_type{});
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
    flex_stack<item_type> s(impl_type{});
    std::string expected_stack = "<>";
    
    s.clear();
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testClearNonempty {
    flex_stack<item_type> s(impl_type{});
    std::string expected_stack = "<>";
    s.push(1);
    
    s.clear();
    
    std::string s_str = stackToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testAssignEmptyEmpty {
    flex_stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<>", t_exp = "<>";
    
    s = std::move(t);
    
    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
    XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignEmptyNonempty {
    flex_stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<>", t_exp = "<>";
    s.push(1);
    
    s = std::move(t);
    
    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
    XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignNonemptyEmpty {
    flex_stack<item_type> s(impl_type{}), t(impl_type{});
    std::string s_exp = "<1>", t_exp = "<>";
    t.push(1);
    
    s = std::move(t);
    
    std::string s_str = stackToString(s);
    std::string t_str = stackToString(t);
    XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
    XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignNonemptyNonempty {
    flex_stack<item_type> s(impl_type{}), t(impl_type{});
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
	flex_stack<item_type> s(impl_type{}), t(impl_type2{});
	std::string s_exp = "<>", t_exp = "<>";
	
	s = std::move(t);
	
	std::string s_str = stackToString(s);
	std::string t_str = stackToString(t);
	XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
	XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignEmptyNonemptyMultiImpl {
	flex_stack<item_type> s(impl_type{}), t(impl_type2{});
	std::string s_exp = "<>", t_exp = "<>";
	s.push(1);
	
	s = std::move(t);
	
	std::string s_str = stackToString(s);
	std::string t_str = stackToString(t);
	XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
	XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignNonemptyEmptyMultiImpl {
	flex_stack<item_type> s(impl_type{}), t(impl_type2{});
	std::string s_exp = "<1>", t_exp = "<>";
	t.push(1);
	
	s = std::move(t);
	
	std::string s_str = stackToString(s);
	std::string t_str = stackToString(t);
	XCTAssert(s_str == s_exp, @"%s", s_str.c_str());
	XCTAssert(t_str == t_exp, @"%s", s_str.c_str());
}

- (void)testAssignNonemptyNonemptyMultiImpl {
	flex_stack<item_type> s(impl_type{}), t(impl_type2{});
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
