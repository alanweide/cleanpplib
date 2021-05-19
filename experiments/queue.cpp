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

using namespace cleanpp;


int main(){

	queue<natural_number> qnn;
	for(int i = 0; i < 55; i++){
		natural_number element(stack_nn{}, i);
		qnn.enqueue(std::move(element));
	}
	for(int i = 0; i < 33; i++){
		qnn.dequeue();
	}

	while(!qnn.is_empty()){
		natural_number element(qnn.dequeue());
		std::cout<<element<<std::endl;
	}
}