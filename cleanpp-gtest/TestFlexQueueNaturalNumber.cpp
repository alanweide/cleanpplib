#include <gtest/gtest.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <queue_impl/linked_queue.hpp>
#include <queue_impl/array_queue.hpp>
#include <nn_impl/bounded_nn.hpp>
#include <nn_impl/stack_nn.hpp>
#include <queue.hpp>
#include <natural_number.hpp>
using namespace cleanpp;

typedef natural_number nn_type;
typedef queue<nn_type> queue_type;
//typedef array_queue<nn_type> impl_type;
typedef queue<nn_type> impl_type;

static std::string queueToString(queue_type& q) {
    std::stringstream s_stm;
    s_stm << q;
    std::string s_str = s_stm.str();
    return s_str;
}

TEST(FlexQueueNaturalNumber, InitializerDefTest) {
    queue_type q;
    std::string empty_stack = "<>";
    std::string q_str = queueToString(q);
    EXPECT_TRUE(q_str == empty_stack);
}

TEST(FlexQueueNaturalNumber, ClearEmptyTest) {
    queue_type q;
    std::string empty_stack = "<>";

    q.clear();

    std::string q_str = queueToString(q);
    EXPECT_TRUE(q_str == empty_stack);
}

TEST(FlexQueueNaturalNumber, ClearSingleElementTest) {
    queue_type q;
    std::string empty_stack = "<>";

    nn_type a(5L);
    q.enqueue(std::move(a));

    q.clear();

    std::string q_str = queueToString(q);
    EXPECT_TRUE(q_str == empty_stack);
}

TEST(FlexQueueNaturalNumber, ClearManyElementsTest) {
    queue_type q;
    std::string empty_stack = "<>";

    int numElem = 12;
    for (long i = 0; i < numElem; i++) {
        nn_type n(i);
        q.enqueue(std::move(n));
    }

    q.clear();

    std::string q_str = queueToString(q);
    EXPECT_TRUE(q_str == empty_stack);
}

TEST(FlexQueueNaturalNumber, IsEmpty_EmptyTest) {
    queue_type q;
    EXPECT_TRUE(q.is_empty());
}

TEST(FlexQueueNaturalNumber, IsEmpty_NonEmptyTest) {
    queue_type q;
    nn_type a(1L);
    q.enqueue(std::move(a));
    EXPECT_TRUE(!q.is_empty());
}

TEST(FlexQueueNaturalNumber, IsEmpty_Empty_EnqDeqTest) {
    queue_type q;
    nn_type a(1L), b(2L);

    q.enqueue(std::move(a));
    b = q.dequeue();

    EXPECT_TRUE(q.is_empty());
}

TEST(FlexQueueNaturalNumber, EnqueueToEmptyTest) {
    queue_type q;
    std::string expected = "<1>";

    nn_type a(1L);

    q.enqueue(std::move(a));

    std::string q_str = queueToString(q);
    EXPECT_TRUE(q_str == expected);
}

TEST(FlexQueueNaturalNumber, EnqueueToNonEmptyTest) {
    queue_type q;
    std::string expected = "<1, 2>";

    nn_type a(1L), b(2L);
    q.enqueue(std::move(a));

    q.enqueue(std::move(b));

    std::string q_str = queueToString(q);
    EXPECT_TRUE(q_str == expected);
}

TEST(FlexQueueNaturalNumber, DequeueToEmptyTest) {
    queue_type q;
    std::string expected = "<>";
    nn_type a(1L), expected_a, b, expected_b(1L);
    q.enqueue(std::move(a));

    b = q.dequeue();

    std::string q_str = queueToString(q);
    EXPECT_TRUE(q_str == expected);
    EXPECT_TRUE(a == expected_a);
}

TEST(FlexQueueNaturalNumber, DequeueNonEmptyToNonEmptyTest) {
    queue_type q;
    std::string expected = "<2>";
    nn_type a(1L), expected_a, b(2L), expected_b, c, expected_c(1L);
    q.enqueue(std::move(a));
    q.enqueue(std::move(b));

    c = q.dequeue();

    std::string q_str = queueToString(q);
    EXPECT_TRUE(q_str == expected);
    EXPECT_TRUE(a == expected_a);
    EXPECT_TRUE(b == expected_b);
    std::cout << "testDequeueNonEmptyToNonEmpty; c = " << c << "\n";
    EXPECT_TRUE(c == expected_c);
}

// Test case because Will identified a bug
TEST(FlexQueueNaturalNumber, DequeueNonEmptyToEmptyAfterNonEmptyTest) {
    queue_type q;
    std::string expected = "<>";
    nn_type a(1L), expected_a, b, expected_b(1L);

    q.enqueue(std::move(a));
    a = q.dequeue();
    q.enqueue(std::move(a));

    b = q.dequeue();

    std::string q_str = queueToString(q);
    EXPECT_TRUE(q_str == expected);
    EXPECT_TRUE(a == expected_a);
    EXPECT_TRUE(b == expected_b);
}


TEST(FlexQueueNaturalNumber, DequeueFromLongTest) {
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
    EXPECT_TRUE(q_str == expected);
    EXPECT_TRUE(a == a_expected);
}

/*
    secondary methods tests
*/
TEST(FlexQueueNaturalNumber, AppendNonEmptyToEmpty) {
    queue_type receiver_q, transmitter_q;
    std::string expected_receiver = "<0, 1, 2, 3, 4>",
        expected_transmitter = "<>";

    int numElem = 5;
    for(long i = 0; i < numElem; i++){
        nn_type n(i);
        transmitter_q.enqueue(std::move(n));
    }

    receiver_q.append(std::move(transmitter_q));

    std::string receiver_str = queueToString(receiver_q);
    std::string transmitter_str = queueToString(transmitter_q);
    EXPECT_TRUE(receiver_str == expected_receiver);
    EXPECT_TRUE(transmitter_str == expected_transmitter);

}

TEST(FlexQueueNaturalNumber, AppendEmptyToNonEmpty) {
    queue_type receiver_q, transmitter_q;
    std::string expected_receiver = "<0, 1, 2, 3, 4>",
        expected_transmitter = "<>";

    int numElem = 5;
    for(long i = 0; i < numElem; i++){
        nn_type n(i);
        receiver_q.enqueue(std::move(n));
    }

    receiver_q.append(std::move(transmitter_q));

    std::string receiver_str = queueToString(receiver_q);
    std::string transmitter_str = queueToString(transmitter_q);
    EXPECT_TRUE(receiver_str == expected_receiver);
    EXPECT_TRUE(transmitter_str == expected_transmitter);
}

TEST(FlexQueueNaturalNumber, AppendEmptyToEmpty) {
    queue_type receiver_q, transmitter_q;
    std::string expected_receiver = "<>",
        expected_transmitter = "<>";

    receiver_q.append(std::move(transmitter_q));

    std::string receiver_str = queueToString(receiver_q);
    std::string transmitter_str = queueToString(transmitter_q);
    EXPECT_TRUE(receiver_str == expected_receiver);
    EXPECT_TRUE(transmitter_str == expected_transmitter);
}

TEST(FlexQueueNaturalNumber, AppendNonEmptyToNonEmpty) {
    queue_type receiver_q, transmitter_q;
    std::string expected_receiver = "<0, 1, 2, 3>",
        expected_transmitter = "<>";

    int numElem = 2;
    for(long i = 0; i < numElem; i++){
        nn_type n(i), n2(i + 2);
        receiver_q.enqueue(std::move(n));
        transmitter_q.enqueue(std::move(n2));
    }

    receiver_q.append(std::move(transmitter_q));

    std::string receiver_str = queueToString(receiver_q);
    std::string transmitter_str = queueToString(transmitter_q);
    EXPECT_TRUE(receiver_str == expected_receiver);
    EXPECT_TRUE(transmitter_str == expected_transmitter);
}


