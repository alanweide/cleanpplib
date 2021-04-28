//
//  stack_nn.cpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//
#include <memory>
#include <assert.h>
#include <natural_number_impls/stack_nn.hpp>
#include <stack_impls/linked_stack.hpp>

namespace cleanpp {

stack_nn::stack_nn(long n): rep_() {
    set_from_long(n);
}

stack_nn::stack_nn(stack_nn&& other): rep_(std::move(other.rep_)) {
    other.clear();
}

stack_nn& stack_nn::operator=(stack_nn&& other) {
    if (&other == this) {
        return *this;
    }

    rep_ = std::move(other.rep_);
    other.clear();
    return *this;
}

void stack_nn::clear() {
    rep_.clear();
}

bool stack_nn::is_zero() const {
    return rep_.is_empty();
}

void stack_nn::multiply_by_radix(int d) {
    assert(0 <= d && d < RADIX);
    if (!is_zero() || d != 0) {
        rep_.push(std::move(d));
    }
}

int stack_nn::divide_by_radix() {
	int d = 0;
    if (!is_zero()) {
        d = rep_.pop();
    }
    assert(0 <= d && d < RADIX);
	return std::move(d);
}


std::unique_ptr<natural_number_kernel_impl> stack_nn::new_instance() {
    return std::make_unique<stack_nn>();
}

}
