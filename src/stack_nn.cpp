//
//  stack_nn.cpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/22/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <stack_nn.hpp>
#include <linked_stack.hpp>

namespace cleanpp {

stack_nn::stack_nn(int n) {
    rep = std::make_unique<linked_stack<int32_t>>();
    this->set_from_int(n);
};

stack_nn::stack_nn(stack_nn&& other): rep(std::move(other.rep)) {
    other.clear();
}

stack_nn& stack_nn::operator=(stack_nn&& other) {
    if (&other == this) {
        return *this;
    }

    rep = std::move(other.rep);
    other.clear();
    return *this;
}

void stack_nn::clear() {
    rep->clear();
}

bool stack_nn::is_zero() {
    return rep->is_empty();
//    return true;
}

void stack_nn::multiply_by_radix(int d) {
    rep->push(d);
}

void stack_nn::divide_by_radix(int &d) {
    if (rep->is_empty()) {
        d = 0;
    } else {
        rep->pop(d);
    }
}

}
