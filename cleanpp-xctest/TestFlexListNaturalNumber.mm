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
#include <list_impls/stack_based_list.hpp>
#include <natural_number_impls/bounded_nn.hpp>
#include <natural_number_impls/stack_nn.hpp>
#include <clean_list/list.hpp>

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
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    std::string list_str = my_list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmpty {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    my_list.clear();
    
    std::string list_str = my_list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmptyRem {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    nn_type a(5);
    my_list.insert(std::move(a));
    
    my_list.clear();
    
    std::string list_str = my_list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmptyPrec {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    nn_type a(5);
    my_list.insert(std::move(a));
    my_list.retreat();
    
    my_list.clear();
    
    std::string list_str = my_list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromNonEmpty {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    nn_type a(5), b(3);
    my_list.insert(std::move(a));
    my_list.insert(std::move(b));
    my_list.retreat();
    
    my_list.clear();
    
    std::string list_str = my_list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testAssignEmptyEmpty {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    list<nn_type> my_list2(stack_based_list<nn_type>{});
	std::string expected = "(<>, <>)";
	
	my_list = std::move(my_list2);
	
	std::string list_str = my_list.to_str();
	XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testIsAtFrontEmpty {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    XCTAssert(my_list.is_at_front());
}

- (void)testIsAtEndEmpty {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    XCTAssert(my_list.is_at_end());
}

- (void)testIsAtFrontNonemptyTrue {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    nn_type a(1);
    my_list.insert(std::move(a));
    my_list.retreat();
    
    XCTAssert(my_list.is_at_front());
}

- (void)testIsAtFrontNonemptyFalse {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    nn_type a(1);
    my_list.insert(std::move(a));
    
    XCTAssert(!my_list.is_at_front());
}

- (void)testIsAtEndNonemptyTrue {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    nn_type a(1);
    my_list.insert(std::move(a));
    my_list.retreat();
    
    XCTAssert(!my_list.is_at_end());
}

- (void)testIsAtEndNonemptyFalse {
    list<nn_type> my_list(stack_based_list<nn_type>{});

    nn_type a(1);
    my_list.insert(std::move(a));
    
    XCTAssert(my_list.is_at_end());
}

- (void)testInsertFromEmpty {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<1>, <>)";
    nn_type a_exp;
    
    nn_type a(1);
    
    my_list.insert(std::move(a));
    
    std::string list_str = my_list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testInsertFromNonemptyAtEnd {
    list<nn_type> my_list(stack_based_list<nn_type>{});
    std::string expected = "(<1, 2>, <>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    my_list.insert(std::move(a));
    
    my_list.insert(std::move(b));
    
    std::string list_str = my_list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testInsertFromNonemptyAtFront {
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
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
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <>)";
    
    list.reset();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromEmptyRem {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <4>)";
    
    nn_type a(4);
    list.insert(std::move(a));
    
    list.reset();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromEmptyPrec {
    list<nn_type> list(stack_based_list<nn_type>{});
    std::string expected = "(<>, <4>)";
    
    nn_type a(4);
    list.insert(std::move(a));
    list.retreat();
    
    list.reset();
    
    std::string list_str = list.to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromNonEmpty {
    list<nn_type> list(stack_based_list<nn_type>{});
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
