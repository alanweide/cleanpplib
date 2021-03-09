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
#include "linked_stack.hpp"
#include "array_stack.hpp"
#include "flexible_stack.hpp"
#include "natural_number.hpp"

namespace cleanpp {

class stack_nn: public clean_natural_number {
public:
    stack_nn(long n = 0);
    
    stack_nn(stack_nn const &other) = delete;
    stack_nn(stack_nn&& other);
    
    stack_nn& operator=(const stack_nn& other) = delete;
    stack_nn& operator=(stack_nn&& other);
    
    void clear() override;
    bool is_zero() const override;
    void multiply_by_radix(int d) override;
    int divide_by_radix() override;
    std::unique_ptr<clean_natural_number_kernel> new_instance() override;
private:
    flex_stack<int> rep_;
};

}

#endif /* stack_nn_hpp */
