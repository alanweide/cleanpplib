#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <queue_impls/linked_queue.hpp>
#include <queue_impls/array_queue.hpp>
#include <natural_number_impls/bounded_nn.hpp>
#include <natural_number_impls/stack_nn.hpp>

using namespace cleanpp;

typedef stack_nn nn_type;
typedef array_queue<nn_type> queue_nn_type;

static std::string queueNNToString(std::unique_ptr<queue_impl<nn_type>> &s) {
	std::stringstream s_stm;
	s_stm << *s;
	std::string s_str = s_stm.str();
	return s_str;
}

TEST(ArrayQueueNaturalNumber, InitializerDefTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	std::string empty_stack = "<>";
	std::string q_str = queueNNToString(q);
	EXPECT_TRUE(q_str == empty_stack);
}

TEST(ArrayQueueNaturalNumber, ClearEmptyTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	std::string empty_stack = "<>";
	
	q->clear();
	
	std::string q_str = queueNNToString(q);
	EXPECT_TRUE(q_str == empty_stack);
}

TEST(ArrayQueueNaturalNumber, ClearSingleElementTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	std::string empty_stack = "<>";
	
	nn_type a(5);
	q->enqueue(std::move(a));
	
	q->clear();
	
	std::string q_str = queueNNToString(q);
	EXPECT_TRUE(q_str == empty_stack);
}

TEST(ArrayQueueNaturalNumber, ClearManyElementsTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	std::string empty_stack = "<>";
	
	int numElem = 12;
	for (int i = 0; i < numElem; i++) {
		nn_type n(i);
		q->enqueue(std::move(n));
	}
	
	q->clear();
	
	std::string q_str = queueNNToString(q);
	EXPECT_TRUE(q_str == empty_stack);
}

TEST(ArrayQueueNaturalNumber, IsEmpty_EmptyTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	EXPECT_TRUE(q->is_empty());
}

TEST(ArrayQueueNaturalNumber, IsEmpty_NonEmptyTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	nn_type a(1);
	q->enqueue(std::move(a));
	EXPECT_TRUE(!q->is_empty());
}

TEST(ArrayQueueNaturalNumber, IsEmpty_Empty_EnqDeqTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	nn_type a(1), b(2);
	
	q->enqueue(std::move(a));
	b = q->dequeue();
	
	EXPECT_TRUE(q->is_empty());
}

TEST(ArrayQueueNaturalNumber, EnqueueToEmptyTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	std::string expected = "<1>";
	
	nn_type a(1);
	
	q->enqueue(std::move(a));
	
	std::string q_str = queueNNToString(q);
	EXPECT_TRUE(q_str == expected);
}

TEST(ArrayQueueNaturalNumber, EnqueueToNonEmptyTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	std::string expected = "<1, 2>";
	
	nn_type a(1), b(2);
	q->enqueue(std::move(a));
	
	q->enqueue(std::move(b));
	
	std::string q_str = queueNNToString(q);
	EXPECT_TRUE(q_str == expected);
}

TEST(ArrayQueueNaturalNumber, DequeueEmptyToEmptyTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	std::string expected = "<>";
	nn_type expected_a(1);
	
	nn_type a(1);
	q->enqueue(std::move(a));
	
	a = q->dequeue();
	
	std::string q_str = queueNNToString(q);
	EXPECT_TRUE(q_str == expected);
	EXPECT_TRUE(a == expected_a);
}

TEST(ArrayQueueNaturalNumber, DequeueNonEmptyToEmptyTest) {
	std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
	std::string expected = "<>";
	nn_type expected_a(0), expected_b(1);
	
	nn_type a(1), b(2);
	q->enqueue(std::move(a));
	
	b = q->dequeue();
	
	std::string q_str = queueNNToString(q);
	EXPECT_TRUE(q_str == expected);
	EXPECT_TRUE(a == expected_a);
	EXPECT_TRUE(b == expected_b);
}

TEST(ArrayQueueNaturalNumber, DequeueNonEmptyToEmptyAfterNonEmptyTest) {
    std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
    std::string expected = "<>";
    nn_type expected_a(0), expected_b(1);
    
    nn_type a(1), b(2);
    q->enqueue(std::move(a));
    a = q->dequeue();
    q->enqueue(std::move(a));
    
    b = q->dequeue();
    
    std::string q_str = queueNNToString(q);
    EXPECT_TRUE(q_str == expected);
    EXPECT_TRUE(a == expected_a);
    EXPECT_TRUE(b == expected_b);
}

TEST(ArrayQueueNaturalNumber, DequeueFromLongTest) {
    std::unique_ptr<queue_impl<nn_type>> q = std::make_unique<queue_nn_type>();
    std::string empty_stack = "<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>";
    nn_type a, a_expected;
    
    int numElem = 12;
    for (int i = 0; i < numElem; i++) {
        nn_type n(i);
        q->enqueue(std::move(n));
    }
    
    a = q->dequeue();
    
    std::string q_str = queueNNToString(q);
    EXPECT_TRUE(q_str == empty_stack);
    EXPECT_TRUE(a == a_expected);
}
