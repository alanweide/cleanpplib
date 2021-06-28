#include <memory>
#include <iostream>
#include "integer.hpp"
#include "integer_impl/nn_integer.hpp"
#include "nn_impl/bounded_nn.hpp"
#include "integer_impl/vector_integer.hpp"
#include "natural_number.hpp"
#include "nn_impl/bounded_nn.hpp"
#include "nn_impl/nn_impl.hpp"
#include "nn_impl/stack_nn.hpp"
#include <queue>
#include <iostream>
#include <stdlib.h>

using namespace cleanpp;

natural_number divideBy2(natural_number nn);

int compare(natural_number& nn1, natural_number& nn2);

natural_number power(natural_number nn, int p){
    
    int i = 0; 
    natural_number base(stack_nn{}, 0);
    std::tie(base, nn) = add(std::move(base), std::move(nn));
    
    while(i < p - 1){ 
        std::tie(base, nn) = multiply(std::move(base), std::move(nn));
        i++;
    }

    nn = std::move(base);
    return nn;
}



natural_number root(natural_number nn, int r){

    natural_number one(stack_nn{}, 1);

    if(compare(nn, one) != 0){
        natural_number lowEnough(stack_nn{}, 0);
        natural_number tooHigh(stack_nn{}, 0);
        std::tie(tooHigh, nn) = add(std::move(tooHigh), std::move(nn));
        lowEnough.increment();
        while(compare(tooHigh, lowEnough) > 0){
            lowEnough.decrement();

            natural_number root(stack_nn{}, 0);
            std::tie(root, lowEnough) = add(std::move(root), std::move(lowEnough));
            std::tie(root, tooHigh) = add(std::move(root), std::move(tooHigh));
            root.divide_by_two();
            natural_number powerResult(stack_nn{}, 0);
            std::tie(powerResult, root) = add(std::move(powerResult), std::move(root));
            powerResult = power(std::move(powerResult), r);

            if(compare(powerResult, nn) > 0){
                tooHigh = std::move(root);
            }
            else{
                lowEnough = std::move(root);
            }

            lowEnough.increment();
        }
        lowEnough.decrement();
        nn = std::move(lowEnough);
    }
    
    return nn;
}

int main(int argc, const char * argv[]) {

    long int input;
    int r;
    
    while(input != -1){
        std::cout<<"Please enter a number: ";
        std::cin>>input;
        std::cout<<"Please enter the root to take: ";
        std::cin>>r;

        natural_number x3(stack_nn{}, input);

        std::cout<<"result of root is: "<<std::endl;
        x3 = root(std::move(x3), r);
        std::cout<<x3<<std::endl;

    }   
}

int compare(natural_number& nn1, natural_number& nn2){

  //base cases
  if(nn1.is_zero() && nn2.is_zero()){
      return 0;
  }
  if(nn1.is_zero()){
      return -1;
  }
  if(nn2.is_zero()){
      return 1;
  }

  //recursive cases
  int rem1 = nn1.divide_by_radix(), rem2 = nn2.divide_by_radix();

  int result;
  if(compare(nn1, nn2) == 0){
    result = rem1 - rem2;
  } else{
    result = compare(nn1, nn2);
  }

  nn1.multiply_by_radix(std::move(rem1));
  nn2.multiply_by_radix(std::move(rem2));

  return result;

}

natural_number divideBy2(natural_number nn){

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
