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

std::tuple<int, natural_number, natural_number> compare(natural_number nn1,
            natural_number nn2);


template<typename T>
std::tuple<T, queue<T>, queue<T>> partition(queue<T> q, T partition){
    queue<T> front, back;
    while( !q.is_empty() ){
        T element;
        std::tie(element, q) = std::move(q).dequeue(); //rref-qualified function 
        int comparison;
        std::tie(comparison, partition, element) = compare(std::move(partition), std::move(element));
        if(comparison < 0){
            back = std::move(back).enqueue(std::move(element)); //rref-qualified function
        } else {
            front = std::move(front).enqueue(std::move(element)); //rref-qualified function
        }
    }
    return std::make_tuple( std::move(partition), std::move(front), std::move(back) );
}

template<typename T>
queue<T> quickSort(queue<T> q){
    bool empty;
    std::tie(empty, q) = std::move(q).is_empty(); //rref-qualified function
    if(!empty ){
        T element;
        std::tie(element, q) = std::move(q).dequeue(); //rref-qualified function
        if( !q.is_empty() ){
            q = std::move(q).enqueue(std::move(element)); //rref-qualified function
            queue<T> front, back;

            T partitioner;
            std::tie(partitioner, q) = std::move(q).dequeue(); //rref-qualified function
            
            std::tie(partitioner, front, back) = partition(std::move(q), std::move(partitioner));
            
            front = quickSort(std::move(front));
            back = quickSort(std::move(back));
        
            front = std::move(front).enqueue(std::move(partitioner)); //rref-qualified function
            bool backEmpty;
            std::tie(backEmpty, back) = std::move(back).is_empty(); //rref-qualified function
            while( backEmpty ){
                T backElement;
                std::tie(backElement, back) = std::move(back).dequeue(); //rref-qualified function
                front = std::move(front).enqueue(std::move(backElement)); //rref-qualified function
                std::tie(backEmpty, back) = std::move(back).is_empty(); //rref-qualified function
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

std::tuple<int, natural_number, natural_number> compare(natural_number nn1,
            natural_number nn2) {

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
  int comparison;
  std::tie(comparison, nn1, nn2) = compare(std::move(nn1), std::move(nn2));
  if(comparison == 0){
    result = rem1 - rem2;
  } else{
    std::tie(result, nn1, nn2) = compare(std::move(nn1), std::move(nn2));
  }

  nn1 = std::move(nn1).multiply_by_radix(std::move(rem1));
  nn2 = std::move(nn2).multiply_by_radix(std::move(rem2));

  return std::make_tuple(result, std::move(nn1), std::move(nn2));

}
