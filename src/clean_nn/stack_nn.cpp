//
//  stack_nn.cpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <stack_nn.hpp>
#include <clean_stack/linked_stack.hpp>

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
        rep_.push(d);
    }
}

void stack_nn::divide_by_radix(int &d) {
    if (is_zero()) {
        d = 0;
    } else {
        rep_.pop(d);
    }
    assert(0 <= d && d < RADIX);
}

}
