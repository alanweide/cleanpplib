//
//  TestTemplateQueueNaturalNumber.m
//  TestTemplateQueueNaturalNumber
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

@interface TestFlexibleQueueNaturalNumber : XCTestCase

@end

@implementation TestFlexibleQueueNaturalNumber

using namespace cleanpp;

typedef natural_number nn_type;
typedef queue<nn_type> queue_type;
//typedef array_queue<nn_type> impl_type;
typedef queue<nn_type> impl_type;

static std::string queueToString(queue_type &q) {
	std::stringstream s_stm;
	s_stm << q;
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
    queue_type q;
	std::string empty_stack = "<>";
	std::string q_str = queueToString(q);
	XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testClearEmpty {
    queue_type q;
	std::string empty_stack = "<>";
	
    q.clear();
	
	std::string q_str = queueToString(q);
	XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testClearSingleElement {
    queue_type q;
	std::string empty_stack = "<>";
	
	nn_type a(5L);
    q.enqueue(std::move(a));
	
    q.clear();
	
	std::string q_str = queueToString(q);
	XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testClearManyElements {
    queue_type q;
	std::string empty_stack = "<>";
	
	int numElem = 12;
	for (long i = 0; i < numElem; i++) {
		nn_type n(i);
        q.enqueue(std::move(n));
	}
	
    q.clear();
	
	std::string q_str = queueToString(q);
	XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testIsEmpty_Empty {
    queue_type q;
    XCTAssert(q.is_empty());
}

- (void)testIsEmpty_NonEmpty {
    queue_type q;
	nn_type a(1L);
    q.enqueue(std::move(a));
    XCTAssert(!q.is_empty());
}

- (void)testIsEmpty_Empty_EnqDeq {
    queue_type q;
	nn_type a(1L), b(2L);
	
    q.enqueue(std::move(a));
    b = q.dequeue();
	
    XCTAssert(q.is_empty());
}

- (void)testEnqueueToEmpty {
    queue_type q;
	std::string expected = "<1>";
	
	nn_type a(1L);
	
    q.enqueue(std::move(a));
	
    std::string q_str = queueToString(q);
	XCTAssert(q_str == expected, @"%s", q_str.c_str());
}

- (void)testEnqueueToNonEmpty {
    queue_type q;
	std::string expected = "<1, 2>";
	
	nn_type a(1L), b(2L);
    q.enqueue(std::move(a));
	
    q.enqueue(std::move(b));
	
    std::string q_str = queueToString(q);
	XCTAssert(q_str == expected, @"%s", q_str.c_str());
}

- (void)testDequeueToEmpty {
    queue_type q;
	std::string expected = "<>";
	nn_type a(1L), expected_a, b, expected_b(1L);
    q.enqueue(std::move(a));
	
    b = q.dequeue();
	
    std::string q_str = queueToString(q);
	XCTAssert(q_str == expected, @"%s", q_str.c_str());
	XCTAssert(a == expected_a);
}

- (void)testDequeueNonEmptyToNonEmpty {
    queue_type q;
	std::string expected = "<2>";
	nn_type a(1L), expected_a, b(2L), expected_b, c, expected_c(1L);
	q.enqueue(std::move(a));
	q.enqueue(std::move(b));
	
	c = q.dequeue();
	
    std::string q_str = queueToString(q);
	XCTAssert(q_str == expected, @"%s", q_str.c_str());
	XCTAssert(a == expected_a);
	XCTAssert(b == expected_b);
	std::cout << "testDequeueNonEmptyToNonEmpty; c = " << c << "\n";
	XCTAssert(c == expected_c);
}

// Test case because Will identified a bug
- (void)testDequeueNonEmptyToEmptyAfterNonEmpty {
    queue_type q;
    std::string expected = "<>";
    nn_type a(1L), expected_a, b, expected_b(1L);

    q.enqueue(std::move(a));
    a = q.dequeue();
    q.enqueue(std::move(a));
    
    b = q.dequeue();
    
    std::string q_str = queueToString(q);
    XCTAssert(q_str == expected, @"%s", q_str.c_str());
    XCTAssert(a == expected_a);
    XCTAssert(b == expected_b);
}


- (void)testDequeueFromLong {
    queue_type q;
    std::string expected = "<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>";
    nn_type a, a_expected;
    
    int numElem = 12;
    for (long i = 0; i < numElem; i++) {
        nn_type n(i);
        q.enqueue(std::move(n));
    }
    
    a = q.dequeue();
    
    std::string q_str = queueToString(q);
    XCTAssert(q_str == expected, @"%s", q_str.c_str());
    XCTAssert(a == a_expected);
}

@end
