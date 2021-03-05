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

int compare(stack_nn& nn1,
            stack_nn& nn2) {

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

  nn1.multiply_by_radix(rem1);
  nn2.multiply_by_radix(rem2);

  return result;
}

bool operator<(stack_nn& nn1, stack_nn& nn2){
    return compare(nn1, nn2) < 0;   
}



template<typename T>
std::tuple<T, flex_queue<T>, flex_queue<T>> partition(flex_queue<T> q, T partition){
    flex_queue<T> front, back;
    while( !q.is_empty() ){
        T element = q.dequeue();
        if(partition < element){
            back.enqueue(std::move(element));
        } else {
            front.enqueue(std::move(element));
        }
    }
    return std::make_tuple( std::move(partition), std::move(front), std::move(back) );
}

template<typename T>
flex_queue<T> quickSort(flex_queue<T> q){
    T element;
    if(!q.is_empty() ){
        element = q.dequeue();

        if( !q.is_empty() ){

            q.enqueue(std::move(element));
            
            flex_queue<T> front, back;

            T partitioner = q.dequeue();
            

            std::tie(partitioner, front, back) = partition(std::move(q), std::move(partitioner));
            
            front = quickSort(std::move(front));
            back = quickSort(std::move(back));
        
            front.enqueue(std::move(partitioner));

            while( !back.is_empty() ){

                front.enqueue(back.dequeue());

            }
            
            q = std::move(front);
        
        } else{
            q.enqueue(std::move(element));
        }
    }
     
    return q;

}


int main(int argc, const char* argv[]) {

  flex_queue<stack_nn> qnn( linked_queue<stack_nn>{} );
  
  qnn.enqueue(stack_nn(2));
  qnn.enqueue(stack_nn(3));
  qnn.enqueue(stack_nn(5));
  qnn.enqueue(stack_nn(4));

  qnn = quickSort<stack_nn>(std::move(qnn));

  std::cout<<"Sorted queue: "<<std::endl;

  std::cout<<qnn<<std::endl;
  
 

}
