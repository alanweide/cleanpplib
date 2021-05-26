#include <memory>
#include <iostream>
#include <sstream>
#include "bounded_nn.hpp"
#include "stack_nn.hpp"
#include "linked_queue.hpp"
#include "array_queue.hpp"
#include "natural_number.hpp"
#include "natural_number.cpp"
#include "queue.hpp"
#include "stack_nn.cpp"
#include "stack.hpp"
#include "set.hpp"
#include "map.hpp"

using namespace cleanpp;

static std::string setToString(set<stack_nn>& s) {
    std::stringstream s_stm;
    s_stm << s;
    std::string s_str = s_stm.str();
    return s_str;
}

int main(){

	stack<stack_nn> q, f;
	for(long i = 1; i < 4; i++){
		stack_nn elem(i), elem2(i);
		q.push(std::move(elem));
	}
	
	q.flip();
	
	std::cout<<q<<std::endl;

	


	
}