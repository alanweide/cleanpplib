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
