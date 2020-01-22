//
//  stack_nn.hpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#ifndef stack_nn_h
#define stack_nn_h

#include <stdio.h>
#include <natural_number.hpp>
#include <clean_stack.hpp>

namespace cleanpp {
class stack_nn: public natural_number {
private:
    std::unique_ptr<clean_stack<int32_t>> rep;
public:
    stack_nn(int n = 0);
    
    stack_nn(stack_nn const &other) = delete;
    stack_nn(stack_nn&& other);
    
    stack_nn& operator=(const stack_nn& other) = delete;
    stack_nn& operator=(stack_nn&& other);
    
    void clear() override;
    bool is_zero() override;
    void multiply_by_radix(int d) override;
    void divide_by_radix(int &d) override;    
};
}

#endif /* stack_nn_hpp */
