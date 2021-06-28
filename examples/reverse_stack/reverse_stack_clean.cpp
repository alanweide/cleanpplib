//
//  selection_sort2.cpp
//  cleanpp-main
//
//  Created by Will Janning on 1/15/21.
//  Copyright © 2020 Alan Weide. All rights reserved.
//
#include <memory>
#include <iostream>
#include "integer.hpp"
#include "integer_impl/nn_integer.hpp"
#include "nn_impl/bounded_nn.hpp"
#include "integer_impl/vector_integer.hpp"
#include "stack.hpp"
#include "stack_impl/array_stack.hpp"
#include "stack_impl/linked_stack.hpp"
#include "stack_impl/stack_impl.hpp"
#include "list.hpp"
#include "list_impl/list_impl.hpp"
#include "list_impl/stack_based_list.hpp"
#include "natural_number.hpp"
#include "nn_impl/bounded_nn.hpp"
#include "nn_impl/nn_impl.hpp"
#include "nn_impl/stack_nn.hpp"
#include <queue>
#include <iostream>
#include <stdlib.h>

using namespace cleanpp;

template<typename T>
stack<T> flip(stack<T> s){

    stack<T> result( linked_stack<T>{} );
    
    while( !s.is_empty() ){

        result.push( s.pop() );

    }

    return result;
}


int main(int argc, const char* argv[]) {
    stack<stack_nn> snn( linked_stack<stack_nn>{} );

    snn.push(stack_nn(2));
    snn.push(stack_nn(3));
    snn.push(stack_nn(4));
    snn.push(stack_nn(5));

    std::cout<<"Original stack: "<<std::endl;
    std::cout<<snn<<std::endl;

    snn = flip<stack_nn>(std::move(snn));

    std::cout<<"Flipped stack: ";
    std::cout<<snn<<std::endl;
    
}
