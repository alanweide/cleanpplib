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
#include "natural_number.hpp"

using namespace cleanpp;


std::tuple<stack_nn, stack_nn> add(stack_nn x, stack_nn y){
    int x_low;
    x_low = x.divide_by_radix();
    int y_low;
    y_low = y.divide_by_radix();
    if (!y.is_zero()) {
        std::tie<stack_nn, stack_nn>(x, y) = add(std::move(x), std::move(y));
    }
    x_low += y_low;
    if (x_low >= clean_natural_number::RADIX) {
        x_low -= clean_natural_number::RADIX;
        x.increment();
    }
    x.multiply_by_radix(std::move(x_low));
    y.multiply_by_radix(std::move(y_low));
    std::tuple<stack_nn, stack_nn> result = std::make_tuple<stack_nn, stack_nn>(std::move(x), std::move(y));
    return result;
}

std::tuple<stack_nn, stack_nn> subtract(stack_nn x, stack_nn y){
    int x_low;
    x_low = x.divide_by_radix();
    int y_low;
    y_low = y.divide_by_radix();
    if (!y.is_zero()) {
        std::tie<stack_nn, stack_nn>(x, y) = subtract(std::move(x), std::move(y));
    }
    x_low -= y_low;
    if(x_low < 0){
        x_low += clean_natural_number::RADIX;
        x.decrement();
    }
    x.multiply_by_radix(x_low);
    y.multiply_by_radix(y_low);
    return std::make_tuple<stack_nn, stack_nn>(std::move(x), std::move(y));

}

int main(int argc, const char * argv[]) {

    stack_nn x(5);
    stack_nn y(6);

    std::tie<stack_nn, stack_nn>(x, y) = add(std::move(x), std::move(y));
    std::cout<<x<<std::endl;
    std::cout<<y<<std::endl;
    
    std::tie<stack_nn, stack_nn>(x, y) = subtract(std::move(x), std::move(y));
    std::cout<<x<<std::endl;
    std::cout<<y<<std::endl;
   
}
