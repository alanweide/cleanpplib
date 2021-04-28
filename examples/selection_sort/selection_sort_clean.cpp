#include <memory>
#include <iostream>
#include "nn_integer.hpp"
#include "bounded_nn.hpp"
#include "vector_integer.hpp"
#include "linked_queue.hpp"
#include "array_queue.hpp"
#include "array_stack.hpp"
#include "stack_based_list.hpp"
#include "natural_number.hpp"
#include "queue.hpp"

using namespace cleanpp;

int compare(stack_nn& nn1, stack_nn& nn2);

bool operator<(stack_nn& nn1, stack_nn& nn2){
    return compare(nn1, nn2) < 0;   
}

template<typename T>
std::tuple<T , queue<T>> removeMin(queue<T> q) {

    T min = q.dequeue();
    queue<T> temp( linked_queue<T>{} );
    
    while(!q.is_empty()){
      T element = q.dequeue();

      if(element < min){
        
        temp.enqueue(std::move(min));
        min = std::move(element);

      } else{
        temp.enqueue(std::move(element));
      }
    }
    
    return std::make_tuple(std::move(min), std::move(temp)); 
}

template<typename T>
queue<T> sort(queue<T> q){

    queue<T> result( linked_queue<T>{} );

    while(!q.is_empty()){
        
        T min;
        std::tie(min, q) = removeMin<T>(std::move(q));
        
        result.enqueue(std::move(min));

    }
    
    return result;

}


int main(int argc, const char* argv[]) {

  queue<stack_nn> qnn( linked_queue<stack_nn>{} );
  
  qnn.enqueue(stack_nn(2));
  qnn.enqueue(stack_nn(3));
  qnn.enqueue(stack_nn(5));
  qnn.enqueue(stack_nn(4));
  
  stack_nn min;
  std::tie(min, qnn) = removeMin<stack_nn>(std::move(qnn));
  
  std::cout<<"Minimum element is: ";
  std::cout<<min<<std::endl<<std::endl;
  
  qnn = sort<stack_nn>(std::move(qnn));

  std::cout<<"Sorted rest of queue: (left to right) "<<std::endl;
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
