#include <memory>
#include <iostream>
#include "integer.hpp"
#include "nn_integer.hpp"
#include "bounded_nn.hpp"
#include "vector_integer.hpp"
#include "queue.hpp"
#include "linked_queue.hpp"
#include "array_queue.hpp"
#include "stack.hpp"
#include "array_stack.hpp"
#include "linked_stack.hpp"
#include "stack_impl.hpp"
#include "list.hpp"
#include "list_impl.hpp"
#include "stack_based_list.hpp"
#include "natural_number.hpp"
#include "bounded_nn.hpp"
#include "natural_number_impl.hpp"
#include "stack_nn.hpp"
#include "set_on_queue.hpp"
#include "set_impl.hpp"
#include "set.hpp"
#include <queue>
#include <iostream>
#include <stdlib.h>

using namespace cleanpp;

int main(){

    set_on_queue<stack_nn> cs;
    
    std::cout<<"5"<<std::endl;
    cs.add(stack_nn(5));
    
    cs.add(stack_nn(6));

    cs.add(stack_nn(7));

    stack_nn six(6);
    cs.remove(std::move(six));
    std::cout<<"6"<<std::endl;
    std::cout<<cs<<std::endl;
    

   


}