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
using namespace std;

typedef stack_nn nn_type;

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testInitializerDef {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<>, <>)";
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

- (void)testIsAtFrontEmpty {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    
    XCTAssert(list->is_at_front());
}

- (void)testIsAtEndEmpty {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    
    XCTAssert(list->is_at_end());
}

- (void)testIsAtFrontNonemptyTrue {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    
    nn_type a(1);
    list->insert(a);
    list->retreat();
    
    XCTAssert(list->is_at_front());
}

- (void)testIsAtFrontNonemptyFalse {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    
    nn_type a(1);
    list->insert(a);
    
    XCTAssert(!list->is_at_front());
}

- (void)testIsAtEndNonemptyTrue {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    
    nn_type a(1);
    list->insert(a);
    list->retreat();
    
    XCTAssert(!list->is_at_end());
}

- (void)testIsAtEndNonemptyFalse {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    
    nn_type a(1);
    list->insert(a);
    
    XCTAssert(list->is_at_end());
}

- (void)testInsertFromEmpty {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<1>, <>)";
    nn_type a_exp;
    
    nn_type a(1);
    
    list->insert(a);
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testInsertFromNonemptyAtEnd {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<1, 2>, <>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(a);
    
    list->insert(b);
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testInsertFromNonemptyAtFront {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<2>, <1>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(a);
    list->retreat();
    
    list->insert(b);
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testInsertNonemptyInMiddle {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<1, 3>, <2>)";
    nn_type a_exp, b_exp, c_exp;
    
    nn_type a(1), b(2), c(3);
    list->insert(a);
    list->insert(b);
    list->retreat();
    
    list->insert(c);
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
    XCTAssert(c == c_exp);
}

- (void)testRetreatFromEndToFront {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<>, <1>)";
    nn_type a_exp;
    
    nn_type a(1);
    list->insert(a);
    
    list->retreat();
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testRetreatFromMiddleToFront {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<>, <2, 1>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(a);
    list->retreat();
    list->insert(b);
    
    list->retreat();
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testRetreatFromEndToMiddle {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<1>, <2>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(a);
    list->insert(b);
    
    list->retreat();
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testRetreatMiddle {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<1>, <3, 2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list->insert(a);
    list->insert(b);
    list->retreat();
    list->insert(c);
    
    list->retreat();
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
    XCTAssert(c == c_exp);
}

- (void)testAdvanceFrontToEnd {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<1>, <>)";
    nn_type a_exp;
    
    nn_type a(1);
    list->insert(a);
    list->retreat();
    
    list->advance();
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
}

- (void)testAdvanceFromMiddleToEnd {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<2, 1>, <>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(a);
    list->retreat();
    list->insert(b);

    list->advance();
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testAdvanceFromFrontToMiddle {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<1>, <2>)";
    nn_type a_exp, b_exp;
    
    nn_type a(1), b(2);
    list->insert(a);
    list->insert(b);
    list->retreat();
    list->retreat();
    
    list->advance();
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
}

- (void)testAdvanceMiddle {
    unique_ptr<clean_list<nn_type>> list = make_unique<stack_based_list<nn_type>>();
    string expected = "(<1, 3>, <2>)";
    nn_type a_exp, b_exp, c_exp;

    nn_type a(1), b(2), c(3);
    list->insert(a);
    list->insert(b);
    list->retreat();
    list->insert(c);
    list->retreat();
    
    list->advance();
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
    XCTAssert(a == a_exp);
    XCTAssert(b == b_exp);
    XCTAssert(c == c_exp);
}


@end
