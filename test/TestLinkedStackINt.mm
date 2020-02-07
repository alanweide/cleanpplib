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

@interface TestLinkedStackInt : XCTestCase

@end

@implementation TestLinkedStackInt

using namespace cleanpp;

static std::string stackIntToString(linked_stack<int> &s) {
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

//+ (NSString*)stringFromStackInt:(linked_stack<int>)

- (void)testInitializerDef {
    linked_stack<int> s{};
    std::string empty_stack = "<>";
	
    std::string s_str = stackIntToString(s);
    XCTAssert(s_str == empty_stack, @"%s", s_str.c_str());
}

- (void)testIsEmpty_Empty {
    linked_stack<int> s{};
    XCTAssert(s.is_empty());
}

- (void)testIsEmpty_NonEmpty {
    linked_stack<int> s{};
    int a = 1;
    s.push(a);
    XCTAssert(!s.is_empty());
}

- (void)testIsEmpty_Empty_PushPop {
    linked_stack<int> s{};
    int a = 1, b = 5;
    s.push(a);
    s.pop(b);
    XCTAssert(s.is_empty());
}

- (void)testPushToEmpty {
    linked_stack<int> s{};
    std::string expected_stack = "<0>";
    
    int z = 0;
    s.push(z);
    
    std::string s_str = stackIntToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPushToNonEmpty {
    linked_stack<int> s{};
    std::string expected_stack = "<1, 0>";
    
    int z = 0, o = 1;
    s.push(z);
    s.push(o);
    
    std::string s_str = stackIntToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
}

- (void)testPopZeroToEmpty {
    linked_stack<int> s{};
    std::string expected_stack = "<>";
    
    int z = 0, o = 1;
    s.push(z);
    s.pop(o);
    
    std::string s_str = stackIntToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(o == 0, @"%d", o);
}

- (void)testPopFiveToEmpty {
    linked_stack<int> s{};
    std::string expected_stack = "<>";
    
    int a = 5, b = 1;
    s.push(a);
    s.pop(b);
    
    std::string s_str = stackIntToString(s);
    XCTAssert(s_str == expected_stack, @"%s", s_str.c_str());
    XCTAssert(b == 5, @"%d", b);
}

@end
