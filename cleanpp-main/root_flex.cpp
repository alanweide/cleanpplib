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

flex_natural_number divideBy2(flex_natural_number nn){

    int rem = nn.divide_by_radix();

    if(!nn.is_zero() || rem != 0){
        
        int rem2 = nn.divide_by_radix();
    
        int tempRem2 = rem2;

        nn.multiply_by_radix(std::move(tempRem2));

        if(rem2 % 2 == 0){
            
            nn = divideBy2(std::move(nn));
            nn.multiply_by_radix(rem / 2);

        } else{
            
            nn = divideBy2(std::move(nn));
            nn.multiply_by_radix((rem / 2) + 5);
        }
        
    }
    return nn;
}

int compare(flex_natural_number& nn1, flex_natural_number& nn2){

    int rem1 = nn1.divide_by_radix();
    int rem2 = nn2.divide_by_radix();
    
    int result = 0;

    if(nn1.is_zero()){
        if(nn2.is_zero()){
            if(rem1 > rem2){
                result = 1;
            }
            else if(rem1 == rem2){
                result = 0;
            }
            else{
                result = -1;
            }
        }
        else{
            result = -1;
        }
    }
    else if(nn2.is_zero()){
        result = 1;
    }
    else{

        int compareResult = compare(nn1, nn2);

        if(compareResult == 0){
            if(rem1 > rem2){
                result = 1;
            }
            else if(rem1 < rem2){
                result = -1;
            }
            else{
                result = 0;
            }
        }
        else if(compareResult == -1){
            result = -1;
        }
        else{
            result = 1;
        }
    }

    nn1.multiply_by_radix(rem1 * 1);
    nn2.multiply_by_radix(rem2 * 1);

    return result;
}

flex_natural_number power(flex_natural_number nn, int p){
    
    int i = 0; 

    flex_natural_number base(stack_nn{}, 0);

    base = add(std::move(base), nn);
    
    while(i < p - 1){ 
        base = multiply(std::move(base), nn);
        i++;
    }

    nn = std::move(base);
    return nn;
}



flex_natural_number root(flex_natural_number nn, int r){

    flex_natural_number lowEnough(stack_nn{}, 0);
    flex_natural_number tooHigh(stack_nn{}, 0);
    
    tooHigh = add(std::move(tooHigh), nn);

    flex_natural_number one(stack_nn{}, 1);

    lowEnough.increment();
    while(compare(tooHigh, lowEnough) > 0){
        lowEnough.decrement();

        flex_natural_number root(stack_nn{}, 0);

        root = add(std::move(root), lowEnough);
        root = add(std::move(root), tooHigh);
        root.divide_by_two();

        flex_natural_number powerTemp(stack_nn{}, 0);
        powerTemp = add(std::move(powerTemp), root);
        powerTemp = power(std::move(powerTemp), r);

        if(compare(nn, powerTemp) == -1){
            tooHigh = std::move(root);
        }
        else{
            lowEnough = std::move(root);
        }

        lowEnough.increment();
    }
    if(compare(nn, one) != 0){
        lowEnough.decrement();
        nn = std::move(lowEnough);
    }
    
    return nn;
}

int main(int argc, const char * argv[]) {
    t_integer<nn_integer> x;
    x.increment();
    t_queue<array_queue, t_integer<nn_integer>> q;
    q.enqueue(std::move(x));
    std::cout << "Hello, World!" << q << "\n";
    
    long unsigned int input;
    int r;
    
    while(input != -1){
        std::cout<<"Please enter a number: ";
        std::cin>>input;
        std::cout<<"Please enter the root to take: ";
        std::cin>>r;

        flex_natural_number x3(stack_nn{}, input);

        std::cout<<"result of root is: "<<std::endl;
        x3 = root(std::move(x3), r);

        std::cout<<x3<<std::endl;

    }   
}
