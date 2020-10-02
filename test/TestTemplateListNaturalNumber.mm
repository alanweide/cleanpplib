//
//  TestTemplateListNaturalNumber.m
//  TestCleanpp
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <clean_list/stack_based_list.hpp>
#include <clean_nn/bounded_nn.hpp>
#include <clean_nn/stack_nn.hpp>
#include <template_list/template_list.hpp>

@interface TestTemplateListNaturalNumber : XCTestCase

@end

@implementation TestTemplateListNaturalNumber

using namespace cleanpp;

typedef stack_nn nn_type;
typedef stack_based_list<nn_type> list_nn_type;
typedef t_list<stack_based_list, nn_type> list_t;

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testInitializerDef {
    list_t list;
    std::string expected = "(<>, <>)";
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmpty {
    list_t list;
    std::string expected = "(<>, <>)";
    
    list.clear();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmptyRem {
    list_t list;
    std::string expected = "(<>, <>)";
    
    nn_type a(5);
    list.insert(std::move(a));
    
    list.clear();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmptyPrec {
    list_t list;
    std::string expected = "(<>, <>)";
    
    nn_type a(5);
    list.insert(std::move(a));
    list.retreat();
    
    list.clear();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromNonEmpty {
    list_t list;
    std::string expected = "(<>, <>)";
    
    nn_type a(5), b(3);
    list.insert(std::move(a));
    list.insert(std::move(b));
    list.retreat();
    
    list.clear();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testIsAtFrontEmpty {
    list_t list;

    XCTAssert(list.is_at_front());
}

- (void)testIsAtEndEmpty {
    list_t list;

    XCTAssert(list.is_at_end());
}

- (void)testIsAtFrontNonemptyTrue {
    list_t list;

    nn_type a(1);
    list.insert(std::move(a));
    list.retreat();
    
    XCTAssert(list.is_at_front());
}

- (void)testIsAtFrontNonemptyFalse {
    list_t list;

    nn_type a(1);
    list.insert(std::move(a));
    
    XCTAssert(!list.is_at_front());
}

- (void)testIsAtEndNonemptyTrue {
    list_t list;

    nn_type a(1);
    list.insert(std::move(a));
    list.retreat();
    
    XCTAssert(!list.is_at_end());
}

- (void)testIsAtEndNonemptyFalse {
    list_t list;

    nn_type a(1);
    list.insert(std::move(a));
    
    XCTAssert(list.is_at_end());
}

- (void)testInsertFromEmpty {
    list_t list;
    std::string expected = "(<1>, <>)";
    nn_type a_exp;
    
    nn_type a(1);
    
    list.insert(std::move(a));
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testInsertFromNonemptyAtEnd {
    list_t list;
    std::string expected = "(<1, 2>, <>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list.insert(std::move(a));
    
    list.insert(std::move(b));
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testInsertFromNonemptyAtFront {
    list_t list;
    std::string expected = "(<2>, <1>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list.insert(std::move(a));
    list.retreat();
    
    list.insert(std::move(b));
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testInsertNonemptyInMiddle {
    list_t list;
    std::string expected = "(<1, 3>, <2>)";
    nn_type a_exp, b_exp, c_exp;
    
    nn_type a(1), b(2), c(3);
    list.insert(std::move(a));
    list.insert(std::move(b));
    list.retreat();
    
    list.insert(std::move(c));
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
    XCTAssert(c == c_exp);
}

- (void)testRetreatFromEndToFront {
    list_t list;
    std::string expected = "(<>, <1>)";
    nn_type a_exp;
    
    nn_type a(1);
    list.insert(std::move(a));
    
    list.retreat();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testRetreatFromMiddleToFront {
    list_t list;
    std::string expected = "(<>, <2, 1>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list.insert(std::move(a));
    list.retreat();
    list.insert(std::move(b));
    
    list.retreat();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testRetreatFromEndToMiddle {
    list_t list;
    std::string expected = "(<1>, <2>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list.insert(std::move(a));
    list.insert(std::move(b));
    
    list.retreat();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testRetreatMiddle {
    list_t list;
    std::string expected = "(<1>, <3, 2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list.insert(std::move(a));
    list.insert(std::move(b));
    list.retreat();
    list.insert(std::move(c));
    
    list.retreat();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
    XCTAssert(c == c_exp);
}

- (void)testAdvanceFrontToEnd {
    list_t list;
    std::string expected = "(<1>, <>)";
    nn_type a_exp;
    
    nn_type a(1);
    list.insert(std::move(a));
    list.retreat();
    
    list.advance();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testAdvanceFromMiddleToEnd {
    list_t list;
    std::string expected = "(<2, 1>, <>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list.insert(std::move(a));
    list.retreat();
    list.insert(std::move(b));

    list.advance();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testAdvanceFromFrontToMiddle {
    list_t list;
    std::string expected = "(<1>, <2>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list.insert(std::move(a));
    list.insert(std::move(b));
    list.retreat();
    list.retreat();
    
    list.advance();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testAdvanceMiddle {
    list_t list;
    std::string expected = "(<1, 3>, <2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list.insert(std::move(a));
    list.insert(std::move(b));
    list.retreat();
    list.insert(std::move(c));
    list.retreat();
    
    list.advance();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
    XCTAssert(c == c_exp);
}

- (void)testRemoveToEmpty {
    list_t list;
    std::string expected = "(<>, <>)";
    nn_type a_exp(5);
    
    nn_type a, b(5);
    list.insert(std::move(b));
    list.retreat();
    
    a = list.remove();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testRemoveToNonEmptyRem {
    list_t list;
    std::string expected = "(<>, <1>)";
    nn_type a_exp(5);
    
    nn_type a, b(5), c(1);
    list.insert(std::move(b));
    list.insert(std::move(c));
    list.retreat();
    list.retreat();
    
    a = list.remove();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testRemoveToNonEmptyPrecRem {
    list_t list;
    std::string expected = "(<1>, <3>)";
    nn_type a_exp(5);
    
    nn_type a, b(5), c(1), d(3);
    list.insert(std::move(c));
    list.insert(std::move(b));
    list.insert(std::move(d));
    list.retreat();
    list.retreat();
    
    a = list.remove();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testResetFromEmpty {
    list_t list;
    std::string expected = "(<>, <>)";
    
    list.reset();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromEmptyRem {
    list_t list;
    std::string expected = "(<>, <4>)";
    
    nn_type a(4);
    list.insert(std::move(a));
    
    list.reset();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromEmptyPrec {
    list_t list;
    std::string expected = "(<>, <4>)";
    
    nn_type a(4);
    list.insert(std::move(a));
    list.retreat();
    
    list.reset();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromNonEmpty {
    list_t list;
    std::string expected = "(<>, <5, 4>)";
    
    nn_type a(4), b(5);
    list.insert(std::move(a));
    list.retreat();
    list.insert(std::move(b));
    
    list.reset();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

@end
