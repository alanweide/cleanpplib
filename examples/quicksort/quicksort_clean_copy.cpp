//
//  selection_sort3.cpp
//  cleanpp-main
//
//  Created by Will Janning on 1/2/21.
//  Copyright © 2020 Alan Weide. All rights reserved.
//
#include <memory>
#include <iostream>
#include "bounded_nn.hpp"
#include "queue.hpp"
#include "linked_queue.hpp"
#include "array_queue.hpp"
#include "natural_number.hpp"
#include "bounded_nn.hpp"
#include "nn_impl.hpp"
#include "stack_nn.hpp"
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
        T element;
        std::tie(element, q) = std::move(q).dequeue(); //rref-qualified function 
        if(compare(partition, element) < 0){
            back = std::move(back).enqueue(std::move(element)); //rref-qualified function
        } else {
            front = std::move(front).enqueue(std::move(element)); //rref-qualified function
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

            T partitioner;
            std::tie(partitioner, q) = std::move(q).dequeue(); //rref-qualified function
            
            std::tie(partitioner, front, back) = partition(std::move(q), std::move(partitioner));
            
            front = quickSort(std::move(front));
            back = quickSort(std::move(back));
        
            front = std::move(front).enqueue(std::move(partitioner)); //rref-qualified function
            while( !back.is_empty() ){
                T backElement;
                std::tie(backElement, back) = std::move(back).dequeue(); //rref-qualified function
                front = std::move(front).enqueue(std::move(backElement)); //rref-qualified function

            }
            
            q = std::move(front);
        
        } else{
            q = std::move(q).enqueue(std::move(element)); //rref-qualified function
        }
    }
     
    return q;

}


int main(int argc, const char* argv[]) {

  queue<stack_nn> qnn( linked_queue<stack_nn>{} );
  
  qnn = std::move(qnn).enqueue(stack_nn(2)); //rref-qualified function
  qnn = std::move(qnn).enqueue(stack_nn(3)); //rref-qualified function
  qnn = std::move(qnn).enqueue(stack_nn(5)); //rref-qualified function
  qnn = std::move(qnn).enqueue(stack_nn(4)); //rref-qualified function


  qnn = quickSort<stack_nn>(std::move(qnn));

  std::cout<<"Sorted queue: "<<std::endl;
  std::cout<<qnn<<std::endl;
  
 

}

int compare(stack_nn& nn1,
            stack_nn& nn2) {

  //base cases
  bool isZero1, isZero2;
  std::tie(isZero1, nn1) = std::move(nn1).is_zero(); //rref-qualified function
  std::tie(isZero2, nn2) = std::move(nn2).is_zero(); //rref-qualified function

  if(isZero1 && isZero2){
      return 0;
  }
  if(isZero1){
      return -1;
  }
  if(isZero2){
      return 1;
  }

  //recursive cases
  std::tie(rem1, nn1) = std::move(nn1).divide_by_radix(); //rref-qualified function
  std::tie(rem2, nn2) = std::move(nn2).divide_by_radix(); //rref-qualified function

  int result;
  if(compare(nn1, nn2) == 0){
    result = rem1 - rem2;
  } else{
    result = compare(nn1, nn2);
  }

  nn1 = std::move(nn1).multiply_by_radix(std::move(rem1));
  nn2 = std::move(nn2).multiply_by_radix(std::move(rem2));

  return result;

}
