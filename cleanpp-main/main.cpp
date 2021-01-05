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

void divideBy2(bounded_nn& nn){
    int rem = nn.divide_by_radix();
    if(!nn.is_zero() || rem != 0){
        if(rem % 2 == 0){
            divideBy2(nn);
            nn.multiply_by_radix(rem / 2);
        } else {
            int rem2 = nn.divide_by_radix();
            nn.multiply_by_radix(rem2);
            if(rem2 % 2 == 0){
                divideBy2(nn);
                nn.multiply_by_radix(rem / 2);
            } else{
                divideBy2(nn);
                nn.multiply_by_radix((rem / 2) + 5);
            }
        }
    }
}

void power(bounded_nn nn, int p){
    int i = 0;
    std::unique_ptr<clean_natural_number> x(new bounded_nn(std::move(nn)));
    std::unique_ptr<clean_natural_number> y(new bounded_nn(std::move(p)));
    while(i < p - 1){
        multiply(std::move(x), y);
        i++;
    }
    std::cout<<nn<<std::endl;
}


std::unique_ptr<clean_natural_number> multiply_by_digit(std::unique_ptr<clean_natural_number> x, int d) {
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
    return x;
}


int main(int argc, const char * argv[]) {
    t_integer<nn_integer> x;
    x.increment();
    t_queue<array_queue, t_integer<nn_integer>> q;
    q.enqueue(std::move(x));
    std::cout << "Hello, World! " << q << "\n";
    
    bounded_nn nn(5);
    
    nn.multiply_by_radix(5);
    std::cout<<nn<<std::endl;
    divideBy2(nn);
    std::cout<<nn<<std::endl;
    bounded_nn nn2(4);
    
    std::cout<<nn2<<std::endl;
    
    int p = 44;
    
    
    //std::unique_ptr<natural_number_secondary> x1(new bounded_nn(5));
    std::unique_ptr<clean_natural_number> x1 = std::make_unique<bounded_nn>(5);
    //std::cout<<*x1<<std::endl;
    std::unique_ptr<clean_natural_number> y = std::make_unique<bounded_nn>(6);
    //std::cout<<*y<<std::endl;
    
    
    if (y->is_zero()) {
        x1->clear();
    } else {
        int y_ones = y->divide_by_radix();
        
        std::unique_ptr<clean_natural_number> x_copy(static_cast<clean_natural_number*>(x1->new_instance().release()));
        std::cout<<"yuh"<<std::endl;
        std::cout<<*x_copy<<std::endl;
        x_copy = add(std::move(x_copy), x1);
        std::cout<<*x_copy<<" 110"<<std::endl;
        x_copy = multiply_by_digit(std::move(x_copy), y_ones);
        std::cout<<*x_copy<<" 112"<<std::endl;
        x1 = multiply(std::move(x1), y);
        std::cout<<*x_copy<<"114"<<std::endl;
        x1->multiply_by_radix(0);
        x1 = add(std::move(x1), x_copy);
        y->multiply_by_radix(y_ones);
    }
    
    
    
    
    return 0;
}


/*int x_low;
 x_low = x1->divide_by_radix();
 int y_low;
 y_low = y->divide_by_radix();
 if (!y->is_zero()) {
 x1 = add(std::move(x1), y);
 }
 x_low += y_low;
 if (x_low >= natural_number_secondary::RADIX) {
 x_low -= natural_number_secondary::RADIX;
 x1->increment();
 }
 x1->multiply_by_radix(x_low);
 y->multiply_by_radix(y_low);
 std::unique_ptr<natural_number_secondary> x2(new bounded_nn(5));
 std::unique_ptr<natural_number_secondary> x3(new bounded_nn(6));
 add(std::move(x2), x3);
 */
