#include <memory>
#include <iostream>
#include "bounded_nn.hpp"
#include "stack_nn.hpp"
#include "linked_queue.hpp"
#include "array_queue.hpp"
#include "natural_number.hpp"
#include "natural_number.cpp"
#include "queue.hpp"
#include "stack_nn.cpp"
#include "stack.hpp"

using namespace cleanpp;


int main(){

	stack<int> q;
	for(int i = 0; i < 5; i++){
		q.push(std::move(i));
	}
	
	std::cout<<q<<std::endl;
	q.flip();
	// qNew.dequeue();
	std::cout<<q<<std::endl;
	
}