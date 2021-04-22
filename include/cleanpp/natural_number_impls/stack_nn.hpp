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
#include <stack_impls/linked_stack.hpp>
#include <stack_impls/array_stack.hpp>
#include <clean_stack/stack.hpp>
#include <natural_number_impls/natural_number_impl.hpp>

namespace cleanpp {

class stack_nn: public natural_number_impl {
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
    std::unique_ptr<natural_number_kernel_impl> new_instance() override;
private:
    stack<int> rep_;
};

}

#endif /* stack_nn_hpp */
