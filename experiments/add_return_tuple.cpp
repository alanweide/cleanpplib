//
//  main.cpp
//  cleanpp-main
//
//  Created by Alan Weide on 10/2/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//
#include <memory>
#include <iostream>
#include "template_integer.hpp"
#include "flexible_integer.hpp"
#include "nn_integer.hpp"
#include "bounded_nn.hpp"
#include "vector_integer.hpp"
#include "template_queue.hpp"
#include "flexible_queue.hpp"
#include "linked_queue.hpp"
#include "array_queue.hpp"
#include "array_stack.hpp"
#include "template_list.hpp"
#include "flexible_list.hpp"
#include "stack_based_list.hpp"
#include "natural_number.hpp"

using namespace cleanpp;

template<typename T>
int toInt(T&& nn){

  int result = 0;

  if( !nn.is_zero() ){

    int onesPlace = nn.divide_by_radix();

    result = onesPlace + 10 * toInt(std::move(nn));

  }
  
  return result;

}

template<typename T>
int toInt(T& nn){

  int result = 0;

  if( !nn.is_zero() ){

    int onesPlace = nn.divide_by_radix();

    result = onesPlace + 10 * toInt(std::move(nn));

  }
  
  return result;

}

std::tuple<stack_nn, stack_nn> add(stack_nn x, stack_nn y){
    int x_low;
    x_low = x.divide_by_radix();
    int y_low;
    y_low = y.divide_by_radix();
    if (!y.is_zero()) {
        std::tie<stack_nn, stack_nn>(x, y) = add(std::move(x), std::move(y));
    }
    x_low += y_low;
    if (x_low >= clean_natural_number::RADIX) {
        x_low -= clean_natural_number::RADIX;
        x.increment();
    }
    x.multiply_by_radix(std::move(x_low));
    y.multiply_by_radix(std::move(y_low));
    std::tuple<stack_nn, stack_nn> result = std::make_tuple<stack_nn, stack_nn>(std::move(x), std::move(y));
    return result;
}

std::tuple<stack_nn, stack_nn> subtract(stack_nn x, stack_nn y){
    int x_low;
    x_low = x.divide_by_radix();
    int y_low;
    y_low = y.divide_by_radix();
    if (!y.is_zero()) {
        std::tie<stack_nn, stack_nn>(x, y) = subtract(std::move(x), std::move(y));
    }
    x_low -= y_low;
    if(x_low < 0){
        x_low += clean_natural_number::RADIX;
        x.decrement();
    }
    x.multiply_by_radix(x_low);
    y.multiply_by_radix(y_low);
    return std::make_tuple<stack_nn, stack_nn>(std::move(x), std::move(y));

}
int main(int argc, const char * argv[]) {
    // flex_natural_number x(stack_nn(5));
    // flex_natural_number y(stack_nn(6));
    stack_nn x(5);
    stack_nn y(6);


    std::tie<stack_nn, stack_nn>(x, y) = add(std::move(x), std::move(y));
    std::cout<<toInt<stack_nn>(std::move(x))<<std::endl;
    std::cout<<toInt<stack_nn>(std::move(y))<<std::endl;

    stack_nn x2(11);
    stack_nn y2(6);
    std::tie<stack_nn, stack_nn>(x2, y2) = subtract(std::move(x2), std::move(y2));
    std::cout<<toInt<stack_nn>(std::move(x2))<<std::endl;
    std::cout<<toInt<stack_nn>(std::move(y2))<<std::endl;

    

    
   
}
