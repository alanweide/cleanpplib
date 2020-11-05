//
//  main.cpp
//  cleanpp-main
//
//  Created by Alan Weide on 10/2/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//
#include <memory>
#include <assert.h>
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

std::unique_ptr<clean_natural_number>&& multiply_by_digit(std::unique_ptr<clean_natural_number> x, int d) {
    int last_dig = x->divide_by_radix();
    last_dig *= d;
    if (!x->is_zero()) {
        x = multiply_by_digit(std::move(x), d);
        x->multiply_by_radix(0);
    }
    std::unique_ptr<clean_natural_number> nn_last_dig(static_cast<clean_natural_number*>(x->new_instance().release()));
    nn_last_dig = add(std::move(nn_last_dig), x);
    nn_last_dig->set_from_long(last_dig);
    x = add(std::move(x), nn_last_dig);
    return std::move(x);
}

int main(int argc, const char * argv[]) {
    t_integer<nn_integer> x;
    x.increment();
    t_queue<array_queue, t_integer<nn_integer>> q;
    q.enqueue(std::move(x));
    std::cout << "Hello, World! " << q << "\n";
    
    std::unique_ptr<clean_natural_number> x1(new bounded_nn(5));
//    std::unique_ptr<clean_natural_number> x1 = std::make_unique<bounded_nn>(5));
    //std::cout<<*x1<<std::endl;
    std::unique_ptr<clean_natural_number> y(new bounded_nn(6));
//    std::unique_ptr<clean_natural_number> y = std::make_unique<bounded_nn>(6);
    //std::cout<<*y<<std::endl;
    

    if (y->is_zero()) {
            x1->clear();
    } else {
        int y_ones = y->divide_by_radix();
        
        std::unique_ptr<clean_natural_number> x_copy(static_cast<clean_natural_number*>(x1->new_instance().release()));
        
        std::cout<<*x_copy<<std::endl;
        x_copy = add(std::move(x_copy), x1);
        
        x_copy = multiply_by_digit(std::move(x_copy), y_ones);
        
        x1 = multiply(std::move(x1), y);
        x1->multiply_by_radix(0);
        x1 = add(std::move(x1), x_copy);
        y->multiply_by_radix(y_ones);
    }
    
    return 0;
}
