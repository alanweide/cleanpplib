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

	set<stack_nn> q, f;
	for(long i = 1; i < 4; i++){
		stack_nn elem(i), elem2(i);
		q.add(std::move(elem));
	}
	for(long i = 4; i < 7; i++){
		stack_nn elem(i);
		f.add(std::move(elem));
	}
	
	std::cout<<"q:"<<std::endl;
	std::cout<<q<<std::endl;
	
	std::cout<<"f:"<<std::endl;
	std::cout<<f<<std::endl;
	
	// qNew.dequeue();
	q.set_union(std::move(f));
	std::cout<<"union of f and q:"<<std::endl;
	std::cout<<q<<std::endl;
	std::string q_str = setToString(q);
	std::string expected_q = "{1, 2, 3, 4, 5, 6}";
	std::cout<<(q_str == expected_q)<<std::endl;


	
}