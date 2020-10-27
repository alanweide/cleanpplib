//
//  main.cpp
//  cleanpp-main
//
//  Created by Alan Weide on 10/2/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//
#include <memory>
#include <iostream>
#include "template_integer.hpp"
#include "flexible_integer.hpp"
#include "nn_integer.hpp"
#include "bounded_nn.hpp"
#include "vector_integer.hpp"
#include "template_queue.hpp"
#include "flexible_queue.hpp"
#include "linked_queue.hpp"
#include "array_queue.hpp"
#include "array_stack.hpp"
#include "template_list.hpp"
#include "flexible_list.hpp"
#include "stack_based_list.hpp"

using namespace cleanpp;

int main(int argc, const char * argv[]) {
    t_integer<nn_integer> x;
    x.increment();
    t_queue<array_queue, t_integer<nn_integer>> q;
    q.enqueue(std::move(x));
    std::cout << "Hello, World! " << q << "\n";
    return 0;
}
