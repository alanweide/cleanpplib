#include <gtest/gtest.h>

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

TEST(FlexSetNaturalNumber, InitializerDefTest) {
    set_type s;
	std::string s_str = setToString(s);
	EXPECT_TRUE(s_str == empty_set);
}

TEST(FlexSetNaturalNumber, ClearEmptyTest) {
    set_type s;

    s.clear();
	
	std::string s_str = setToString(s);
	EXPECT_TRUE(s_str == empty_set);
}

TEST(FlexSetNaturalNumber, ClearSingleElementTest) {
    set_type s;

	nn_type a(5L);
    s.add(std::move(a));
	
    s.clear();
	
	std::string s_str = setToString(s);
	EXPECT_TRUE(s_str == empty_set);
}

TEST(FlexSetNaturalNumber, ClearManyElementsTest) {
    set_type s;
	
	int numElem = 12;
	for (long i = 0; i < numElem; i++) {
		nn_type n(i);
        s.add(std::move(n));
	}
	
    s.clear();
	
	std::string s_str = setToString(s);
	EXPECT_TRUE(s_str == empty_set);
}

TEST(FlexSetNaturalNumber, IsEmpty_InitialTest) {
    set_type s;
    EXPECT_TRUE(s.is_empty());
}

TEST(FlexSetNaturalNumber, IsEmpty_NonEmptyTest) {
    set_type s;
	nn_type a(1L);
    s.add(std::move(a));
    EXPECT_TRUE(!s.is_empty());
}

TEST(FlexSetNaturalNumber, IsEmpty_Empty_AddRemTest) {
    set_type s;
	nn_type a(1L), b(2L);
	
    s.add(std::move(a));
    b = s.removeAny();
	
    EXPECT_TRUE(s.is_empty());
}

TEST(FlexSetNaturalNumber, AddToEmptyTest) {
    set_type s;
	std::string expected = "{1}";
	
	nn_type a(1L);
	
    s.add(std::move(a));
	
    std::string s_str = setToString(s);
	EXPECT_TRUE(s_str == expected);
}

TEST(FlexSetNaturalNumber, AddToNonEmptyTest) {
    set_type s;
	std::string expected = "{1, 2}";
	
	nn_type a(1L), b(2L);
    s.add(std::move(a));
	
    s.add(std::move(b));
	
    std::string s_str = setToString(s);
	EXPECT_TRUE(s_str == expected);
}

TEST(FlexSetNaturalNumber, RemoveAnyToEmptyTest) {
    set_type s;
	nn_type a(1L), expected_a, b, expected_b(1L);
    s.add(std::move(a));
	
    b = s.removeAny();
	
    std::string s_str = setToString(s);
	EXPECT_TRUE(s_str == empty_set);
	EXPECT_TRUE(a == expected_a);
    EXPECT_TRUE(b == expected_b);
}

TEST(FlexSetNaturalNumber, RemoveAnyToNonEmptyTest) {
    set_type s;
	std::string expected_poss1 = "{2}", expected_poss2 = "{1}";
	nn_type a(1L), expected_a, b(2L), expected_b, c, expected_c(1L);
	s.add(std::move(a));
	s.add(std::move(b));
	
	c = s.removeAny();
	
    std::string s_str = setToString(s);
	EXPECT_TRUE(s_str == expected_poss1 || s_str == expected_poss2);
	EXPECT_TRUE(a == expected_a);
	EXPECT_TRUE(b == expected_b);
	EXPECT_TRUE(c == expected_c);
}

TEST(FlexSetNaturalNumber, RemoveAnyToEmptyAfterNonEmptyTest) {
    // Test case because Will identified a bug
    set_type s;
    nn_type a(1L), expected_a, b, expected_b(1L);

    s.add(std::move(a));
    a = s.removeAny();
    s.add(std::move(a));
    
    b = s.removeAny();
    
    std::string s_str = setToString(s);
    EXPECT_TRUE(s_str == empty_set);
    EXPECT_TRUE(a == expected_a);
    EXPECT_TRUE(b == expected_b);
}

TEST(FlexSetNaturalNumber, RemoveOnlyElementTest) {
    set_type s;
    nn_type a(1L), expected_a, b, expected_b(1L), remover(1L);
    s.add(std::move(a));
    
    b = s.remove(std::move(remover));
    
    std::string s_str = setToString(s);
    EXPECT_TRUE(s_str == empty_set);
    EXPECT_TRUE(a == expected_a);
    EXPECT_TRUE(b == expected_b);
}

TEST(FlexSetNaturalNumber, RemoveToNonEmptyTest) {
    set_type s;
    std::string expected = "{2}";
    nn_type a(1L), expected_a, b(2L), expected_b, c, expected_c(1L), remover(1L);
    s.add(std::move(a));
    s.add(std::move(b));
    
    c = s.remove(std::move(remover));

    std::string s_str = setToString(s);
    EXPECT_TRUE(s_str == expected);
    EXPECT_TRUE(a == expected_a);
    EXPECT_TRUE(b == expected_b);
    EXPECT_TRUE(c == expected_c);
}

TEST(FlexSetNaturalNumber, RemoveToNonEmptySecondAddTest) {
    set_type s;
    std::string expected = "{1}";
    nn_type a(1L), expected_a, b(2L), expected_b, c, expected_c(2L), remover(2L);
    s.add(std::move(a));
    s.add(std::move(b));
    
    c = s.remove(std::move(remover));

    std::string s_str = setToString(s);
    EXPECT_TRUE(s_str == expected);
    EXPECT_TRUE(a == expected_a);
    EXPECT_TRUE(b == expected_b);
    EXPECT_TRUE(c == expected_c);
}

TEST(FlexSetNaturalNumber, ContainsEmptyTest) {
    set_type s;
    nn_type a;
    
    bool contains;
    contains = s.contains(std::move(a));
    
    std::string s_str = setToString(s);
    EXPECT_TRUE(s_str == empty_set);
    EXPECT_TRUE(!contains);
}

TEST(FlexSetNaturalNumber, ContainsNonEmptyTrueTest) {
    set_type s;
    std::string expected = "{0}";
    nn_type adder, a;
    
    s.add(std::move(adder));
    
    bool contains;
    contains = s.contains(std::move(a));
    
    std::string s_str = setToString(s);
    EXPECT_TRUE(s_str == expected);
    EXPECT_TRUE(contains);
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
    EXPECT_TRUE(s.getSize() == expected_size);
    EXPECT_TRUE(contains);
}

TEST(FlexSetNaturalNumber, ContainsNonEmptyFalseTest) {
    set_type s;
    std::string expected = "{1}";
    nn_type a, adder(1L);
    
    s.add(std::move(adder));
    
    bool contains;
    contains = s.contains(std::move(a));
    
    std::string s_str = setToString(s);
    EXPECT_TRUE(s_str == expected);
    EXPECT_TRUE(!contains);
}
