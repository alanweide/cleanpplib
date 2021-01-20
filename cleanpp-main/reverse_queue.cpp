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

template<typename T>
int toInt(T&& nn){

  int result = 0;

  if( !nn.is_zero() ){

    int onesPlace = nn.divide_by_radix();

    result = onesPlace + 10 * toInt(std::move(nn));

  }
  
  return result;

}

template<typename T>
int toInt(T& nn){

  int result = 0;

  if( !nn.is_zero() ){

    int onesPlace = nn.divide_by_radix();

    result = onesPlace + 10 * toInt(std::move(nn));

  }
  
  return result;

}

/**
 * Reverses ("flips") input {@code Queue<T>} type
 *
 * @param q
 *            queue to flip
 * @updates q
 * @ensures q = rev(#q)
 */
template<typename T>
std::unique_ptr<clean_queue<T>> flip(std::unique_ptr<clean_queue<T>> q){

    if( !q->is_empty() ){

      std::unique_ptr<T> front = std::make_unique<T>(  q->dequeue() );
      q = flip<stack_nn>( std::move(q) );
      q->enqueue( std::move(*front) );
      
        
    }

    return temp;
}


int main(int argc, const char* argv[]) {
    
    std::unique_ptr<clean_queue<stack_nn>> qnn = std::make_unique<linked_queue<stack_nn>>();

    qnn->enqueue(stack_nn(2));
    qnn->enqueue(stack_nn(3));
    qnn->enqueue(stack_nn(4));
    qnn->enqueue(stack_nn(5));

    qnn = flip<stack_nn>( std::move(qnn) );

    std::cout<<"Flipped queue (from left to right):"<<std::endl;

    while( !qnn->is_empty() ){
        std::cout<<toInt<stack_nn>(qnn->dequeue())<<std::endl;
    }
 
}
