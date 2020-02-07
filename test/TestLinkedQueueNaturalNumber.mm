//
//  TestLinkedStackNaturalNumber.m
//  TestCleanpp
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <clean_queue/linked_queue.hpp>
#include <clean_nn/bounded_nn.hpp>
#include <clean_nn/stack_nn.hpp>

@interface TestLinkedQueueNaturalNumber : XCTestCase

@end

@implementation TestLinkedQueueNaturalNumber

using namespace cleanpp;

typedef stack_nn nn_type;
typedef linked_queue<nn_type> queue_nn_type;

static std::string queueNNToString(std::unique_ptr<queue<nn_type>> &s) {
    std::stringstream s_stm;
    s_stm << *s;
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
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    std::string empty_stack = "<>";
    std::string q_str = queueNNToString(q);
    XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testClearEmpty {
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    std::string empty_stack = "<>";
    
    q->clear();
    
    std::string q_str = queueNNToString(q);
    XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testClearSingleElement {
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    std::string empty_stack = "<>";
    
    nn_type a(5);
    q->enqueue(a);
    
    q->clear();
    
    std::string q_str = queueNNToString(q);
    XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testClearManyElements {
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    std::string empty_stack = "<>";
    
    int numElem = 12;
    for (int i = 0; i < numElem; i++) {
        nn_type n(i);
        q->enqueue(n);
    }
    
    q->clear();
    
    std::string q_str = queueNNToString(q);
    XCTAssert(q_str == empty_stack, @"%s", q_str.c_str());
}

- (void)testIsEmpty_Empty {
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    XCTAssert(q->is_empty());
}

- (void)testIsEmpty_NonEmpty {
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    nn_type a(1);
    q->enqueue(a);
    XCTAssert(!q->is_empty());
}

- (void)testIsEmpty_Empty_EnqDeq {
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    nn_type a(1), b(2);
    
    q->enqueue(a);
    q->dequeue(b);
    
    XCTAssert(q->is_empty());
}

- (void)testEnqueueToEmpty {
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    std::string expected = "<1>";
    
    nn_type a(1);
    
    q->enqueue(a);
    
    std::string q_str = queueNNToString(q);
    XCTAssert(q_str == expected, @"%s", q_str.c_str());
}

- (void)testEnqueueToNonEmpty {
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    std::string expected = "<1, 2>";
    
    nn_type a(1), b(2);
    q->enqueue(a);
    
    q->enqueue(b);
    
    std::string q_str = queueNNToString(q);
    XCTAssert(q_str == expected, @"%s", q_str.c_str());
}

- (void)testDequeueEmptyToEmpty {
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    std::string expected = "<>";
    nn_type expected_a(1);
    
    nn_type a(1);
    q->enqueue(a);
    
    q->dequeue(a);
    
    std::string q_str = queueNNToString(q);
    XCTAssert(q_str == expected, @"%s", q_str.c_str());
    XCTAssert(a == expected_a);
}

- (void)testDequeueNonEmptyToEmpty {
    std::unique_ptr<queue<nn_type>> q = std::make_unique<queue_nn_type>();
    std::string expected = "<>";
    nn_type expected_a(0), expected_b(1);
    
    nn_type a(1), b(2);
    q->enqueue(a);
    
    q->dequeue(b);
    
    std::string q_str = queueNNToString(q);
    XCTAssert(q_str == expected, @"%s", q_str.c_str());
    XCTAssert(a == expected_a);
    XCTAssert(b == expected_b);
}

@end
