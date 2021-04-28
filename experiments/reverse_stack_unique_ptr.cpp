//
//  selection_sort2.cpp
//  cleanpp-main
//
//  Created by Will Janning on 1/15/21.
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

/**
 * Reverses ("flips") {@code this}.
 * 
 *  @param s
 *              the stack
 * @updates s
 * @returns s
 * @ensures s = rev(#s)
 */
template<typename T>
std::unique_ptr<clean_stack<T>> flip(std::unique_ptr<clean_stack<T>> s){

    std::unique_ptr<clean_stack<T>> result = std::make_unique<linked_stack<T>>();
    
    while( !s->is_empty() ){

        result->push( s->pop() );

    }

    return result;
}


int main(int argc, const char* argv[]) {
    std::unique_ptr<clean_stack<stack_nn>> snn = std::make_unique<linked_stack<stack_nn>>();

    snn->push(stack_nn(2));
    snn->push(stack_nn(3));
    snn->push(stack_nn(4));
    snn->push(stack_nn(5));

    std::cout<<"Original stack: ";
    std::cout<<*snn<<std::endl;

    snn = flip<stack_nn>(std::move(snn));

    std::cout<<"Flipped stack: ";
    std::cout<<*snn<<std::endl;
    
 
}
