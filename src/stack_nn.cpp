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

stack_nn::stack_nn(int n) {
    rep = std::make_unique<linked_stack<int>>();
    set_from_int(n);
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
}

void stack_nn::multiply_by_radix(int d) {
    assert(0 <= d && d < 10);
    if (!is_zero() || d != 0) {
        rep->push(d);
    }
}

void stack_nn::divide_by_radix(int &d) {
    if (is_zero()) {
        d = 0;
    } else {
        rep->pop(d);
    }
}

}
