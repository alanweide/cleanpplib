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
#include "set_impl/set_on_queue.hpp"
#include "set_impl/set_impl.hpp"
#include "set.hpp"
#include "map_impl/map_on_set.hpp"
#include "map_impl/map_impl.hpp"
#include "map.hpp"
#include <queue>
#include <iostream>
#include <stdlib.h>


using namespace cleanpp;

int main(){

    map<natural_number, natural_number> cm;
    cm.add(natural_number(stack_nn{}, 5), natural_number(stack_nn{}, 3));
    cm.add(natural_number(stack_nn{}, 2), natural_number(stack_nn{}, 7));
    std::cout<<cm<<std::endl;
    std::cout<<cm.size()<<std::endl;

    std::cout<<cm.remove(natural_number(stack_nn{}, 2))<<std::endl;
    std::cout<<cm.removeAny()<<std::endl;

    cm.add(natural_number(stack_nn{}, 4), natural_number(stack_nn{}, 3));

    if(cm.hasKey(natural_number(stack_nn{}, 3))){
        std::cout<<"has pair with given key value"<<std::endl;

    } else{
        std::cout<<"doesn't have pair with given key value"<<std::endl;
    }



    std::cout<<cm<<std::endl;







}
