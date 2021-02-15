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


template <typename T>
int compare(T& nn1,
            T& nn2) {

  int rem1 = nn1.divide_by_radix();
  int rem2 = nn2.divide_by_radix();

  int result = 0;

  if (nn1.is_zero()) {
    if (nn2.is_zero()) {
      if (rem1 > rem2) {
        result = 1;
      } else if (rem1 == rem2) {
        result = 0;
      } else {
        result = -1;
      }
    } else {
      result = -1;
    }
  } else if (nn2.is_zero()) {
    result = 1;
  } else {
    int compareResult = compare(nn1, nn2);

    if (compareResult == 0) {
      if (rem1 > rem2) {
        result = 1;
      } else if (rem1 < rem2) {
        result = -1;
      } else {
        result = 0;
      }
    } else if (compareResult == -1) {
      result = -1;
    } else {
      result = 1;
    }
  }

  nn1.multiply_by_radix(std::move(rem1));
  nn2.multiply_by_radix(std::move(rem2));

  return result;
}

bool operator<(stack_nn& nn1, stack_nn& nn2){
  return compare(nn1, nn2) < 0;
}


//This function violates the Clean++ discipline rule that a function that updates a parameter must return said parameter. 
//The queue that is passed into the function is updated (the minimum value is removed), but not returned. 
//Instead, the minimum value of the queue is returned.

/**
 * Removes and returns the minimum value from {@code q}.
 * 
 * @param q
 *            the queue
 * @return the minimum value from {@code q}
 * @updates q
 * @requires <pre>
 * q /= empty_string
 * </pre>
 * @ensures <pre>
 * perms(q * <removeMin>, #q)  and
 *  for all x: template type
 *      where (x is in entries (q))
 *    ( <removeMin> <= x )
 * </pre>
 */
template<typename T>
T removeMin(flex_queue<T>& q) {

    T min = q.dequeue();
    flex_queue<T> temp( linked_queue<T>{} );
    
    while(!q.is_empty()){
      T element = q.dequeue();

      if(element < min){
        
        temp.enqueue(std::move(min));
        min = std::move(element);

      } else{
        temp.enqueue(std::move(element));
      }
    }
    
    q = std::move(temp);
    return std::move(min); 
}


/**
 * Sorts {@code q}.
 * 
 * @param q
 *            the queue
 * @updates q
 * @ensures q = [#q in nondecreasing order]
 */
template<typename T>
flex_queue<T> sort(flex_queue<T> q){
    flex_queue<T> result( linked_queue<T>{} );

    while(!q.is_empty()){
        
        result.enqueue(removeMin<T>(q));

    }
    
    return result;

}


int main(int argc, const char* argv[]) {

  flex_queue<stack_nn> qnn( linked_queue<stack_nn>{} );
  
  qnn.enqueue(stack_nn(2));
  qnn.enqueue(stack_nn(3));
  qnn.enqueue(stack_nn(4));
  qnn.enqueue(stack_nn(4));
  
  std::cout<<"Minimum element is: ";
  std::cout<<toInt(removeMin<stack_nn>(qnn))<<std::endl<<std::endl;
  
  qnn = sort<stack_nn>(std::move(qnn));

  std::cout<<"Sorted rest of queue: (left to right) "<<std::endl;
  
  while( !qnn.is_empty() ){
    std::cout<<toInt(qnn.dequeue())<<", ";
  }
  std::cout<<std::endl;

}
