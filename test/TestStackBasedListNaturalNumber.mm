//
//  TestStackBasedListNaturalNumber.m
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

@interface TestStackBasedListNaturalNumber : XCTestCase

@end

@implementation TestStackBasedListNaturalNumber

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
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmpty {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    list->clear();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmptyRem {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    nn_type a(5);
    list->insert(std::move(a));
    
    list->clear();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromEmptyPrec {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    nn_type a(5);
    list->insert(std::move(a));
    list->retreat();
    
    list->clear();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testClearFromNonEmpty {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    nn_type a(5), b(3);
    list->insert(std::move(a));
    list->insert(std::move(b));
    list->retreat();
    
    list->clear();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testIsAtFrontEmpty {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();

    XCTAssert(list->is_at_front());
}

- (void)testIsAtEndEmpty {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();

    XCTAssert(list->is_at_end());
}

- (void)testIsAtFrontNonemptyTrue {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();

    nn_type a(1);
    list->insert(std::move(a));
    list->retreat();
    
    XCTAssert(list->is_at_front());
}

- (void)testIsAtFrontNonemptyFalse {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();

    nn_type a(1);
    list->insert(std::move(a));
    
    XCTAssert(!list->is_at_front());
}

- (void)testIsAtEndNonemptyTrue {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();

    nn_type a(1);
    list->insert(std::move(a));
    list->retreat();
    
    XCTAssert(!list->is_at_end());
}

- (void)testIsAtEndNonemptyFalse {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();

    nn_type a(1);
    list->insert(std::move(a));
    
    XCTAssert(list->is_at_end());
}

- (void)testInsertFromEmpty {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <>)";
    nn_type a_exp;
    
    nn_type a(1);
    
    list->insert(std::move(a));
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testInsertFromNonemptyAtEnd {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1, 2>, <>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    
    list->insert(std::move(b));
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testInsertFromNonemptyAtFront {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<2>, <1>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    list->retreat();
    
    list->insert(std::move(b));
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testInsertNonemptyInMiddle {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1, 3>, <2>)";
    nn_type a_exp, b_exp, c_exp;
    
    nn_type a(1), b(2), c(3);
    list->insert(std::move(a));
    list->insert(std::move(b));
    list->retreat();
    
    list->insert(std::move(c));
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
    XCTAssert(c == c_exp);
}

- (void)testRetreatFromEndToFront {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <1>)";
    nn_type a_exp;
    
    nn_type a(1);
    list->insert(std::move(a));
    
    list->retreat();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testRetreatFromMiddleToFront {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <2, 1>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    list->retreat();
    list->insert(std::move(b));
    
    list->retreat();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testRetreatFromEndToMiddle {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <2>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    list->insert(std::move(b));
    
    list->retreat();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testRetreatMiddle {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <3, 2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list->insert(std::move(a));
    list->insert(std::move(b));
    list->retreat();
    list->insert(std::move(c));
    
    list->retreat();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
    XCTAssert(c == c_exp);
}

- (void)testAdvanceFrontToEnd {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <>)";
    nn_type a_exp;
    
    nn_type a(1);
    list->insert(std::move(a));
    list->retreat();
    
    list->advance();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testAdvanceFromMiddleToEnd {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<2, 1>, <>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    list->retreat();
    list->insert(std::move(b));

    list->advance();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testAdvanceFromFrontToMiddle {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <2>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(std::move(a));
    list->insert(std::move(b));
    list->retreat();
    list->retreat();
    
    list->advance();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testAdvanceMiddle {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1, 3>, <2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list->insert(std::move(a));
    list->insert(std::move(b));
    list->retreat();
    list->insert(std::move(c));
    list->retreat();
    
    list->advance();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
    XCTAssert(c == c_exp);
}

- (void)testRemoveToEmpty {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    nn_type a_exp(5);
    
    nn_type a, b(5);
    list->insert(std::move(b));
    list->retreat();
    
    a = list->remove();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testRemoveToNonEmptyRem {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <1>)";
    nn_type a_exp(5);
    
    nn_type a, b(5), c(1);
    list->insert(std::move(b));
    list->insert(std::move(c));
    list->retreat();
    list->retreat();
    
    a = list->remove();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testRemoveToNonEmptyPrecRem {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<1>, <3>)";
    nn_type a_exp(5);
    
    nn_type a, b(5), c(1), d(3);
    list->insert(std::move(c));
    list->insert(std::move(b));
    list->insert(std::move(d));
    list->retreat();
    list->retreat();
    
    a = list->remove();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testResetFromEmpty {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <>)";
    
    list->reset();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromEmptyRem {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <4>)";
    
    nn_type a(4);
    list->insert(std::move(a));
    
    list->reset();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromEmptyPrec {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <4>)";
    
    nn_type a(4);
    list->insert(std::move(a));
    list->retreat();
    
    list->reset();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testResetFromNonEmpty {
    std::unique_ptr<list<nn_type>> list = std::make_unique<list_nn_type>();
    std::string expected = "(<>, <5, 4>)";
    
    nn_type a(4), b(5);
    list->insert(std::move(a));
    list->retreat();
    list->insert(std::move(b));
    
    list->reset();
    
    std::string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

@end
