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

template<typename T>
int toInt(T nn){

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

bool operator<(flex_natural_number& nn1, flex_natural_number& nn2){
  return compare(nn1, nn2) < 0;
}


template<typename T>
flex_queue<T> append(flex_queue<T> q1, flex_queue<T> q2){

    while(!q2.is_empty()){
        q1.enqueue(q2.dequeue());
    }

    return q1;
}


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
flex_queue<T> placeMinAtFront(flex_queue<T> q) {

    T min = q.dequeue();
    flex_queue<T> temp( linked_queue<T>{} );
    
    while(!q.is_empty()){
      T element = q.dequeue();
      

      if(compare<T>(element, min) < 0){
        
        temp.enqueue(std::move(min));
        min = std::move(element);

      } else{
        temp.enqueue(std::move(element));
      }
    }
    
    flex_queue<T> result( linked_queue<T>{} );
    result.enqueue(std::move(min));

    result = append<T>(std::move(result), std::move(temp));
    
    return result; 
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
        q = placeMinAtFront<T>(std::move(q));

       result.enqueue( q.dequeue() );

    }
    
    return result;

}


int main(int argc, const char* argv[]) {

  flex_queue<stack_nn> qnn( linked_queue<stack_nn>{} );
  
  qnn.enqueue(stack_nn(2));
  qnn.enqueue(stack_nn(1));
  qnn.enqueue(stack_nn(6));
  qnn.enqueue(stack_nn(4));
  
  
 
  qnn = placeMinAtFront<stack_nn>(std::move(qnn));
  
  std::cout<<"Minimum element is: ";
  std::cout<<toInt<stack_nn>(qnn.dequeue())<<std::endl;
  
  qnn = sort<stack_nn>(std::move(qnn));

  while( !qnn.is_empty() ){
        std::cout<<toInt<stack_nn>(qnn.dequeue())<<std::endl;
  }
    

}
