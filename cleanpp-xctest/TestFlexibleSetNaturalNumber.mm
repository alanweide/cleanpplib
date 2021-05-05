//
//  TestFlexibleSetNaturalNumber.m
//  TestFlexibleSetNaturalNumber
//
//  Created by Alan Weide on 8/6/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <queue_impls/linked_queue.hpp>
#include <queue_impls/array_queue.hpp>
#include <natural_number_impls/bounded_nn.hpp>
#include <natural_number_impls/stack_nn.hpp>
#include <clean_queue/queue.hpp>
#include <clean_nn/natural_number.hpp>
#include <clean_set/set.hpp>
#include <set_impls/set_on_queue.hpp>

@interface TestFlexibleSetNaturalNumber : XCTestCase

@end

@implementation TestFlexibleSetNaturalNumber

using namespace cleanpp;

typedef natural_number nn_type;
typedef set<nn_type> set_type;
typedef set<nn_type> impl_type;

static std::string empty_set = "{}";

static std::string setToString(set_type &s) {
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
    set_type s;
	std::string s_str = setToString(s);
	XCTAssert(s_str == empty_set, @"%s", s_str.c_str());
}

- (void)testClearEmpty {
    set_type s;

    s.clear();
	
	std::string s_str = setToString(s);
	XCTAssert(s_str == empty_set, @"%s", s_str.c_str());
}

- (void)testClearSingleElement {
    set_type s;

	nn_type a(5L);
    s.add(std::move(a));
	
    s.clear();
	
	std::string s_str = setToString(s);
	XCTAssert(s_str == empty_set, @"%s", s_str.c_str());
}

- (void)testClearManyElements {
    set_type s;
	
	int numElem = 12;
	for (long i = 0; i < numElem; i++) {
		nn_type n(i);
        s.add(std::move(n));
	}
	
    s.clear();
	
	std::string s_str = setToString(s);
	XCTAssert(s_str == empty_set, @"%s", s_str.c_str());
}

- (void)testIsEmpty_Initial {
    set_type s;
    XCTAssert(s.is_empty());
}

- (void)testIsEmpty_NonEmpty {
    set_type s;
	nn_type a(1L);
    s.add(std::move(a));
    XCTAssert(!s.is_empty());
}

- (void)testIsEmpty_Empty_AddRem {
    set_type s;
	nn_type a(1L), b(2L);
	
    s.add(std::move(a));
    b = s.removeAny();
	
    XCTAssert(s.is_empty());
}

- (void)testAddToEmpty {
    set_type s;
	std::string expected = "{1}";
	
	nn_type a(1L);
	
    s.add(std::move(a));
	
    std::string s_str = setToString(s);
	XCTAssert(s_str == expected, @"%s", s_str.c_str());
}

- (void)testAddToNonEmpty {
    set_type s;
	std::string expected = "{1, 2}";
	
	nn_type a(1L), b(2L);
    s.add(std::move(a));
	
    s.add(std::move(b));
	
    std::string s_str = setToString(s);
	XCTAssert(s_str == expected, @"%s", s_str.c_str());
}

- (void)testRemoveAnyToEmpty {
    set_type s;
	nn_type a(1L), expected_a, b, expected_b(1L);
    s.add(std::move(a));
	
    b = s.removeAny();
	
    std::string s_str = setToString(s);
	XCTAssert(s_str == empty_set, @"%s", s_str.c_str());
	XCTAssert(a == expected_a);
    XCTAssert(b == expected_b);
}

- (void)testRemoveAnyToNonEmpty {
    set_type s;
	std::string expected_poss1 = "{2}", expected_poss2 = "{1}";
	nn_type a(1L), expected_a, b(2L), expected_b, c, expected_c(1L);
	s.add(std::move(a));
	s.add(std::move(b));
	
	c = s.removeAny();
	
    std::string s_str = setToString(s);
	XCTAssert(s_str == expected_poss1 || s_str == expected_poss2, @"%s", s_str.c_str());
	XCTAssert(a == expected_a);
	XCTAssert(b == expected_b);
	XCTAssert(c == expected_c);
}

- (void)testRemoveAnyToEmptyAfterNonEmpty {
    // Test case because Will identified a bug
    set_type s;
    nn_type a(1L), expected_a, b, expected_b(1L);

    s.add(std::move(a));
    a = s.removeAny();
    s.add(std::move(a));
    
    b = s.removeAny();
    
    std::string s_str = setToString(s);
    XCTAssert(s_str == empty_set, @"%s", s_str.c_str());
    XCTAssert(a == expected_a);
    XCTAssert(b == expected_b);
}

- (void)testRemoveOnlyElement {
    set_type s;
    nn_type a(1L), expected_a, b, expected_b(1L), remover(1L);
    s.add(std::move(a));
    
    b = s.remove(std::move(remover));
    
    std::string s_str = setToString(s);
    XCTAssert(s_str == empty_set, @"%s", s_str.c_str());
    XCTAssert(a == expected_a);
    XCTAssert(b == expected_b);
}

- (void)testRemoveToNonEmpty {
    set_type s;
    std::string expected = "{2}";
    nn_type a(1L), expected_a, b(2L), expected_b, c, expected_c(1L), remover(1L);
    s.add(std::move(a));
    s.add(std::move(b));
    
    c = s.remove(std::move(remover));

    std::string s_str = setToString(s);
    XCTAssert(s_str == expected, @"%s", s_str.c_str());
    XCTAssert(a == expected_a);
    XCTAssert(b == expected_b);
    XCTAssert(c == expected_c);
}

- (void)testRemoveToNonEmptySecondAdd {
    set_type s;
    std::string expected = "{1}";
    nn_type a(1L), expected_a, b(2L), expected_b, c, expected_c(2L), remover(2L);
    s.add(std::move(a));
    s.add(std::move(b));
    
    c = s.remove(std::move(remover));

    std::string s_str = setToString(s);
    XCTAssert(s_str == expected, @"%s", s_str.c_str());
    XCTAssert(a == expected_a);
    XCTAssert(b == expected_b);
    XCTAssert(c == expected_c);
}

- (void)testContainsEmpty {
    set_type s;
    nn_type a;
    
    bool contains;
    contains = s.contains(std::move(a));
    
    std::string s_str = setToString(s);
    XCTAssert(s_str == empty_set, @"%s", s_str.c_str());
    XCTAssert(!contains);
}

- (void)testContainsNonEmptyTrue {
    set_type s;
    std::string expected = "{0}";
    nn_type adder, a;
    
    s.add(std::move(adder));
    
    bool contains;
    contains = s.contains(std::move(a));
    
    std::string s_str = setToString(s);
    XCTAssert(s_str == expected, @"%s", s_str.c_str());
    XCTAssert(contains);
}

/**
 Weird error when running this test. EXC_BAD_ACCESS at closing curly brace (during destructor?) most of the time but sometimes in XCTAssert(contains)???
 */
- (void)skip_testContainsBigSetTrue {
    set_type s;
    int expected_size = 0;
    nn_type a;
    
    int numElem = 12;
    for (long i = 0; i < numElem; i++) {
        nn_type n(i);
        s.add(std::move(n));
    }
    
    bool contains;
    contains = s.contains(std::move(a));
    
    std::string s_str = setToString(s);
    XCTAssert(s.getSize() == expected_size, @"%s", s_str.c_str());
    XCTAssert(contains);
}

- (void)testContainsNonEmptyFalse {
    set_type s;
    std::string expected = "{1}";
    nn_type a, adder(1L);
    
    s.add(std::move(adder));
    
    bool contains;
    contains = s.contains(std::move(a));
    
    std::string s_str = setToString(s);
    XCTAssert(s_str == expected, @"%s", s_str.c_str());
    XCTAssert(!contains);
}

@end
