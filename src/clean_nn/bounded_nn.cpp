//
//  bounded_nn.cpp
//  CleanppLibrary
//
//  Created by Alan Weide on 1/20/20.
//  Copyright © 2020 Alan Weide. All rights reserved.
//

#include <stdio.h>
#include <bounded_nn.hpp>

namespace cleanpp {
bounded_nn::bounded_nn(int n): n(n) {};

bounded_nn::bounded_nn(bounded_nn&& other): n(std::move(other.n)) {
    other.clear();
}

bounded_nn& bounded_nn::operator=(bounded_nn&& other) {
    if (&other == this) {
        return *this;
    }
    
    n = other.n;
    other.clear();
    return *this;
}

bool bounded_nn::operator==(const bounded_nn &other) {
    return this->n == other.n;
}

void bounded_nn::clear() {
    n = 0;
}
bool bounded_nn::is_zero() {
    return n == 0;
}
void bounded_nn::multiply_by_radix(int d) {
    n *= RADIX;
    n += d;
}
void bounded_nn::divide_by_radix(int &d) {
    d = n % RADIX;
    n /= RADIX;
}

void bounded_nn::increment() {
    this->n++;
}

void bounded_nn::decrement() {
    this->n--;
}

void bounded_nn::set_from_int(int n) {
    this->n = n;
}

}
