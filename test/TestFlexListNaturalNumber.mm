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
#include <flexible_list/flexible_list.hpp>

@interface TestFlexListNaturalNumber : XCTestCase

@end

@implementation TestFlexListNaturalNumber

using namespace cleanpp;

typedef stack_nn nn_type;
typedef stack_based_list<nn_type> list_nn_type;

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testInitializerDef {
    flex_list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmpty {
    flex_list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    list.clear();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmptyRem {
    flex_list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    nn_type a(5);
    list.insert(std::move(a));
    
    list.clear();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmptyPrec {
    flex_list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    nn_type a(5);
    list.insert(std::move(a));
    list.retreat();
    
    list.clear();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromNonEmpty {
    flex_list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    nn_type a(5), b(3);
    list.insert(std::move(a));
    list.insert(std::move(b));
    list.retreat();
    
    list.clear();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testAssignEmptyEmpty {
	flex_list<nn_type> list(stack_based_list<nn_type>{});
	flex_list<nn_type> list_2(stack_based_list<nn_type>{});
	std::string expected = "(<>, <>)";
	
	list = std::move(list_2);
	
	std::string list_str = list.to_str();
	XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testIsAtFrontEmpty {
    flex_list<nn_type> list(stack_based_list<nn_type>{});

    XCTAssert(list.is_at_front());
}

- (void)testIsAtEndEmpty {
    flex_list<nn_type> list(stack_based_list<nn_type>{});

    XCTAssert(list.is_at_end());
}

- (void)testIsAtFrontNonemptyTrue {
    flex_list<nn_type> list(stack_based_list<nn_type>{});

    nn_type a(1);
    list.insert(std::move(a));
    list.retreat();
    
    XCTAssert(list.is_at_front());
}

- (void)testIsAtFrontNonemptyFalse {
    flex_list<nn_type> list(stack_based_list<nn_type>{});

    nn_type a(1);
    list.insert(std::move(a));
    
    XCTAssert(!list.is_at_front());
}

- (void)testIsAtEndNonemptyTrue {
    flex_list<nn_type> list(stack_based_list<nn_type>{});

    nn_type a(1);
    list.insert(std::move(a));
    list.retreat();
    
    XCTAssert(!list.is_at_end());
}

- (void)testIsAtEndNonemptyFalse {
    flex_list<nn_type> list(stack_based_list<nn_type>{});

    nn_type a(1);
    list.insert(std::move(a));
    
    XCTAssert(list.is_at_end());
}

- (void)testInsertFromEmpty {
    flex_list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<1>, <>)";
    nn_type a_exp;
    
    nn_type a(1);
    
    list.insert(std::move(a));
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testInsertFromNonemptyAtEnd {
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
    flex_list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    list.reset();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromEmptyRem {
    flex_list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <4>)";
    
    nn_type a(4);
    list.insert(std::move(a));
    
    list.reset();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromEmptyPrec {
    flex_list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <4>)";
    
    nn_type a(4);
    list.insert(std::move(a));
    list.retreat();
    
    list.reset();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromNonEmpty {
    flex_list<nn_type> list(stack_based_list<nn_type>{});
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
