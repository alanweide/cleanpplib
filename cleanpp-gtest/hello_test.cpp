//
//  hello_test.cpp
//  cleanpp-gtest
//
//  Created by Alan Weide on 4/20/21.
//  Copyright © 2021 Alan Weide. All rights reserved.
//

#include <stdio.h>
#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7*6, 42);
}
