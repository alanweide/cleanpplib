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
#include "map_on_set.hpp"
#include "map_impl.hpp"
#include "map.hpp"
#include <queue>
#include <iostream>
#include <stdlib.h>

using namespace cleanpp;

int main(){

    map<stack_nn, stack_nn> cm;
    cm.add(stack_nn(5), stack_nn(3));
    cm.add(stack_nn(2), stack_nn(7));
    std::cout<<cm<<std::endl;
    std::cout<<cm.size()<<std::endl;
    std::cout<<cm.removeAny()<<std::endl;
    std::cout<<cm.remove(stack_nn(2))<<std::endl;
    cm.add(stack_nn(4), stack_nn(3));

    if(cm.hasKey(stack_nn(3))){
        std::cout<<"has pair with given key value"<<std::endl;

    } else{
        std::cout<<"doesn't have pair with given key value"<<std::endl;
    }

    
    
    

}