//
//  selection_sort3.cpp
//  cleanpp-main
//
//  Created by Will Janning on 1/2/21.
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


int toInt(stack_nn nn){

  int result = 0;

  if( !nn.is_zero() ){

    int onesPlace = nn.divide_by_radix();

    result = onesPlace + 10 * toInt(std::move(nn));

  }
  
  return result;

}




int main(int argc, const char* argv[]) {

//   flex_queue<stack_nn> q( linked_queue<stack_nn>{} );

//   q.enqueue(stack_nn(2) );
//   q.enqueue(stack_nn(3) );
//   q.enqueue(stack_nn(4) );

//   while(!q.is_empty()){
//       std::cout<<toInt(q.dequeue())<<std::endl;
//   }
//   q.enqueue(stack_nn(3));
//   q.dequeue();

  std::unique_ptr<clean_queue<stack_nn>> qPtr = std::make_unique<linked_queue<stack_nn>>();

  qPtr->enqueue(stack_nn(2) );
  qPtr->enqueue(stack_nn(3) );
  qPtr->enqueue(stack_nn(4) );

  while(!qPtr->is_empty()){
      std::cout<<toInt(qPtr->dequeue())<<std::endl;
  }
  qPtr->enqueue(stack_nn(3));
  qPtr->dequeue();
}
