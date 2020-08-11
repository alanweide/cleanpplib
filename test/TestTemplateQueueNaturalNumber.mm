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
#include <clean_queue/linked_queue.hpp>
#include <clean_queue/array_queue.hpp>
#include <clean_nn/bounded_nn.hpp>
#include <clean_nn/stack_nn.hpp>
#include <template_queue/template_queue.hpp>
#include <template_nn/template_nn.hpp>

@interface TestTemplateQueueNaturalNumber : XCTestCase

@end

@implementation TestTemplateQueueNaturalNumber

using namespace cleanpp;

typedef t_natural_number_secondary<stack_nn> nn_type;
typedef array_queue<nn_type> queue_nn_type;
typedef t_queue<linked_queue, nn_type> template_q;

template<template<typename> class I, typename Item>
static std::string queueToString(t_queue<I, Item> &q) {
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
    template_q q;
	std::string empty_stack = "<>";
	std::string q_str = queueToString(q);
	XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testClearEmpty {
    template_q q;
	std::string empty_stack = "<>";
	
    q.clear();
	
	std::string q_str = queueToString(q);
	XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testClearSingleElement {
    template_q q;
	std::string empty_stack = "<>";
	
	nn_type a(5);
    q.enqueue(std::move(a));
	
    q.clear();
	
	std::string q_str = queueToString(q);
	XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testClearManyElements {
    template_q q;
	std::string empty_stack = "<>";
	
	int numElem = 12;
	for (int i = 0; i < numElem; i++) {
		nn_type n(i);
        q.enqueue(std::move(n));
	}
	
    q.clear();
	
	std::string q_str = queueToString(q);
	XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testIsEmpty_Empty {
    template_q q;
    XCTAssert(q.is_empty());
}

- (void)testIsEmpty_NonEmpty {
    template_q q;
	nn_type a(1);
    q.enqueue(std::move(a));
    XCTAssert(!q.is_empty());
}

- (void)testIsEmpty_Empty_EnqDeq {
    template_q q;
	nn_type a(1), b(2);
	
    q.enqueue(std::move(a));
    b = q.dequeue();
	
    XCTAssert(q.is_empty());
}

- (void)testEnqueueToEmpty {
    template_q q;
	std::string expected = "<1>";
	
	nn_type a(1);
	
    q.enqueue(std::move(a));
	
    std::string q_str = queueToString(q);
	XCTAssert(q_str == expected, @"%s", q_str.c_str());
}

- (void)testEnqueueToNonEmpty {
    template_q q;
	std::string expected = "<1, 2>";
	
	nn_type a(1), b(2);
    q.enqueue(std::move(a));
	
    q.enqueue(std::move(b));
	
    std::string q_str = queueToString(q);
	XCTAssert(q_str == expected, @"%s", q_str.c_str());
}

- (void)testDequeueToEmpty {
    template_q q;
	std::string expected = "<>";
	nn_type expected_a(0), expected_b(1);
	
	nn_type a(1), b(0);
    q.enqueue(std::move(a));
	
    b = q.dequeue();
	
    std::string q_str = queueToString(q);
	XCTAssert(q_str == expected, @"%s", q_str.c_str());
	XCTAssert(a == expected_a);
}

- (void)testDequeueNonEmptyToNonEmpty {
    template_q q;
	std::string expected = "<2>";
	nn_type expected_a(0), expected_b(0), expected_c(1);
	
	nn_type a(1), b(2);
    q.enqueue(std::move(a));
	q.enqueue(std::move(b));
	
    nn_type c = (q.dequeue());
	
    std::string q_str = queueToString(q);
	XCTAssert(q_str == expected, @"%s", q_str.c_str());
	XCTAssert(a == expected_a);
	XCTAssert(b == expected_b);
	XCTAssert(c == expected_c);
}

@end
