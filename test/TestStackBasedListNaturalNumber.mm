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

@interface TestStackBasedListNaturalNumber : XCTestCase

@end

@implementation TestStackBasedListNaturalNumber

using namespace cleanpp;
using namespace std;

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testInitializerDef {
    unique_ptr<clean_list<bounded_nn>> list = make_unique<stack_based_list<bounded_nn>>();
    string expected = "(<>, <>)";
    
    string list_str = list->to_str();
    XCTAssert(list_str == expected, @"%s", list_str.c_str());
}

@end
