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

	set<stack_nn> set1, set2;
	for(long i = 1; i < 4; i++){
		stack_nn elem(i), elem2(i);
		set1.add(std::move(elem));
		set2.add(std::move(elem2));
	}
	
	set2 = set1.set_union(std::move(set2));
	
	std::cout<<set1<<std::endl;
	std::cout<<set2<<std::endl;

	


	
}