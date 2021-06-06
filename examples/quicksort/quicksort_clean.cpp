//
//  selection_sort3.cpp
//  cleanpp-main
//
//  Created by Will Janning on 1/2/21.
//  Copyright © 2020 Alan Weide. All rights reserved.
//
#include <memory>
#include <iostream>
#include "integer.hpp"
#include "integer_impl/nn_integer.hpp"
#include "nn_impl/bounded_nn.hpp"
#include "integer_impl/vector_integer.hpp"
#include "queue.hpp"
#include "queue_impl/linked_queue.hpp"
#include "queue_impl/array_queue.hpp"
#include "natural_number.hpp"
#include "nn_impl/bounded_nn.hpp"
#include "nn_impl/nn_impl.hpp"
#include "nn_impl/stack_nn.hpp"
#include <queue>
#include <iostream>
#include <stdlib.h>

using namespace cleanpp;

int compare(stack_nn& nn1,
            stack_nn& nn2);

bool operator<(stack_nn& nn1, stack_nn& nn2){
    return compare(nn1, nn2) < 0;   
}

template<typename T>
std::tuple<T, queue<T>, queue<T>> partition(queue<T> q, T partition){
    queue<T> front, back;
    while( !q.is_empty() ){
        T element = q.dequeue();
        if(compare(partition, element) < 0){
            back.enqueue(std::move(element));
        } else {
            front.enqueue(std::move(element));
        }
    }
    return std::make_tuple( std::move(partition), std::move(front), std::move(back) );
}

template<typename T>
queue<T> quickSort(queue<T> q){

    if(!q.is_empty() ){
        T element = q.dequeue();
        if( !q.is_empty() ){
            q.enqueue(std::move(element));
            queue<T> front, back;

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

  queue<stack_nn> qnn( linked_queue<stack_nn>{} );
  
  qnn.enqueue(stack_nn(2));
  qnn.enqueue(stack_nn(3));
  qnn.enqueue(stack_nn(5));
  qnn.enqueue(stack_nn(4));

  qnn = quickSort<stack_nn>(std::move(qnn));

  std::cout<<"Sorted queue: "<<std::endl;
  std::cout<<qnn<<std::endl;
  
 

}

int compare(stack_nn& nn1,
            stack_nn& nn2) {

  //base cases
  if(nn1.is_zero() && nn2.is_zero()){
      return 0;
  }
  if(nn1.is_zero()){
      return -1;
  }
  if(nn2.is_zero()){
      return 1;
  }

  //recursive cases
  int rem1 = nn1.divide_by_radix(), rem2 = nn2.divide_by_radix();

  int result;
  if(compare(nn1, nn2) == 0){
    result = rem1 - rem2;
  } else{
    result = compare(nn1, nn2);
  }

  nn1.multiply_by_radix(std::move(rem1));
  nn2.multiply_by_radix(std::move(rem2));

  return result;

}
