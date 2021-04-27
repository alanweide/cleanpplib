//
//  hello_test.cpp
//  cleanpp-gtest
//
//  Created by Alan Weide on 4/20/21.
//  Copyright © 2021 Alan Weide. All rights reserved.
//

#include <stdio.h>
#include <gtest/gtest.h>
#include <clean_nn/natural_number.hpp>
#include <natural_number_impls/bounded_nn.hpp>

using namespace cleanpp;

TEST(HelloTest, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7*6, 42);
    natural_number n1{bounded_nn{}, 12};
    natural_number n2{bounded_nn{}, 12};
    EXPECT_TRUE(n1 == n2);
}
