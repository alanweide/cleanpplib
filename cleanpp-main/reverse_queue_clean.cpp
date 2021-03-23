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
#include "nn_integer.hpp"
#include "bounded_nn.hpp"
#include "vector_integer.hpp"
#include "queue.hpp"
#include "linked_queue.hpp"
#include "array_queue.hpp"
#include "stack.hpp"
#include "array_stack.hpp"
#include "linked_stack.hpp"
#include "stack_impl.hpp"
#include "list.hpp"
#include "list_impl.hpp"
#include "stack_based_list.hpp"
#include "natural_number.hpp"
#include "bounded_nn.hpp"
#include "natural_number_impl.hpp"
#include "stack_nn.hpp"
#include <queue>
#include <iostream>
#include <stdlib.h>

using namespace cleanpp;

/**
 * Reverses ("flips") input {@code Queue<T>} type
 *
 * @param q
 *            queue to flip
 * @updates q
 * @ensures q = rev(#q)
 */
template<typename T>
queue<T> flip(queue<T> q){
    if( !q.is_empty() ){
      T front = q.dequeue();
      q = flip<T>( std::move(q) );
      q.enqueue(std::move(front));
    }
    return q;
}


int main(int argc, const char* argv[]) {
    
    queue<stack_nn> qnn(linked_queue<stack_nn>{});
    qnn.enqueue(stack_nn(5));
    qnn.enqueue(stack_nn(3));
    qnn.enqueue(stack_nn(4));
    qnn.enqueue(stack_nn(2));

    std::cout<<"Original queue: ";
    std::cout<<qnn<<std::endl;

    qnn = flip<stack_nn>( std::move(qnn) );

    std::cout<<"Flipped queue: ";
    std::cout<<qnn<<std::endl;
    
}
